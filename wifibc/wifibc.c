/*
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; version 2.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License along
 *   with this program; if not, write to the Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  (c)2015 befinitiv
 *
 */

#include <all.h>

#if defined USE_WIFIBC

//#define USE_FIFO

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <fec.h>
#include <lib.h>
#include <wifibroadcast.h>
#include <radiotap.h>

#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55, 28, 1)
#define av_frame_alloc avcodec_alloc_frame
#define av_frame_free avcodec_free_frame
#endif

#define MAX_PACKET_LENGTH 4192
#define MAX_USER_PACKET_LENGTH 1450
#define MAX_DATA_OR_FEC_PACKETS_PER_BLOCK 32

#define DEBUG 0
#define debug_print(fmt, ...) do { if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

static SDL_mutex *wifibc_mutex = NULL;
static SDL_Surface *wifibc_bg = NULL;
static SDL_Surface *wifibc_surface = NULL;
static SDL_Thread *wifibc_thread_stream = NULL;
static SDL_Thread *wifibc_thread_video = NULL;
static uint8_t wifibc_running = 0;
static uint8_t wifibc_running2 = 0;

typedef struct  {
	int m_nChannel;
	int m_nChannelFlags;
	int m_nRate;
	int m_nAntenna;
	int m_nRadiotapFlags;
} __attribute__((packed)) PENUMBRA_RADIOTAP_DATA;

int flagHelp = 0;
int param_port = 0;
int param_data_packets_per_block = 8;
int param_fec_packets_per_block = 4;
int param_block_buffers = 1;
int param_packet_length = 1024;
wifibroadcast_rx_status_t *rx_status = NULL;
int max_block_num = -1;

typedef struct {
	pcap_t *ppcap;
	int selectable_fd;
	int n80211HeaderLength;
} monitor_interface_t;

typedef struct {
	int block_num;
	packet_buffer_t *packet_buffer_list;
} block_buffer_t;

#ifdef USE_FIFO
static FILE *infd = NULL;
static FILE *wifibc_fr = NULL;
#else
#define QUEUE_ELEMENTS (1024 * 100)
#define QUEUE_SIZE (QUEUE_ELEMENTS + 1)
static uint8_t Queue[QUEUE_SIZE];
static uint64_t QueueIn = 0;
static uint64_t QueueOut = 0;

inline static uint8_t QueuePut(uint8_t new) {
	while (wifibc_running == 1 && QueueIn == (( QueueOut - 1 + QUEUE_SIZE) % QUEUE_SIZE)) {
		SDL_Delay(1);
	}
	Queue[QueueIn] = new;
	QueueIn = (QueueIn + 1) % QUEUE_SIZE;
	return 0; // No errors
}

inline static uint8_t QueueGet(uint8_t *old) {
	while (wifibc_running == 1 && QueueIn == QueueOut) {
		SDL_Delay(1);
	}
	*old = Queue[QueueOut];
	QueueOut = (QueueOut + 1) % QUEUE_SIZE;
	return 0; // No errors
}
#endif

int open_and_configure_interface(const char *name, int port, monitor_interface_t *interface) {
	struct bpf_program bpfprogram;
	char szProgram[512];
	char szErrbuf[PCAP_ERRBUF_SIZE];
	szErrbuf[0] = '\0';
	interface->ppcap = pcap_open_live(name, 2048, 1, -1, szErrbuf);
	if (interface->ppcap == NULL) {
		fprintf(stderr, "Unable to open interface %s in pcap: %s\n", name, szErrbuf);
		return 1;
	}
	if (pcap_setnonblock(interface->ppcap, 1, szErrbuf) < 0) {
		fprintf(stderr, "Error setting %s to nonblocking mode: %s\n", name, szErrbuf);
	}
	int nLinkEncap = pcap_datalink(interface->ppcap);
	switch (nLinkEncap) {
		case DLT_PRISM_HEADER:
			fprintf(stderr, "DLT_PRISM_HEADER Encap\n");
			interface->n80211HeaderLength = 0x20; // ieee80211 comes after this
			sprintf(szProgram, "radio[0x4a:4]==0x13223344 && radio[0x4e:2] == 0x55%.2x", port);
			break;
		case DLT_IEEE802_11_RADIO:
			fprintf(stderr, "DLT_IEEE802_11_RADIO Encap\n");
			interface->n80211HeaderLength = 0x18; // ieee80211 comes after this
			sprintf(szProgram, "ether[0x0a:4]==0x13223344 && ether[0x0e:2] == 0x55%.2x", port);
			break;
		default:
			fprintf(stderr, "!!! unknown encapsulation on %s !\n", name);
			return 1;
	}
	if (pcap_compile(interface->ppcap, &bpfprogram, szProgram, 1, 0) == -1) {
		puts(szProgram);
		puts(pcap_geterr(interface->ppcap));
		return 1;
	} else {
		if (pcap_setfilter(interface->ppcap, &bpfprogram) == -1) {
			fprintf(stderr, "%s\n", szProgram);
			fprintf(stderr, "%s\n", pcap_geterr(interface->ppcap));
		} else {
		}
		pcap_freecode(&bpfprogram);
	}
	interface->selectable_fd = pcap_get_selectable_fd(interface->ppcap);
	return 0;
}

void block_buffer_list_reset(block_buffer_t *block_buffer_list, size_t block_buffer_list_len, int block_buffer_len) {
	int i;
	block_buffer_t *rb = block_buffer_list;
	for (i = 0; i < block_buffer_list_len; ++i) {
		rb->block_num = -1;
		int j;
		packet_buffer_t *p = rb->packet_buffer_list;
		for (j = 0; j < param_data_packets_per_block+param_fec_packets_per_block; ++j) {
			p->valid = 0;
			p->crc_correct = 0;
			p->len = 0;
			p++;
		}
		rb++;
	}
}

void process_payload(uint8_t *data, size_t data_len, int crc_correct, block_buffer_t *block_buffer_list, int adapter_no) {
	wifi_packet_header_t *wph;
	int block_num;
	int packet_num;
	int i;
	wph = (wifi_packet_header_t*)data;
	data += sizeof(wifi_packet_header_t);
	data_len -= sizeof(wifi_packet_header_t);
	block_num = wph->sequence_number / (param_data_packets_per_block + param_fec_packets_per_block);
	int tx_restart = (block_num + 128 * param_block_buffers < max_block_num);
	if ((block_num > max_block_num || tx_restart) && crc_correct) {
		if (tx_restart) {
			rx_status->tx_restart_cnt++;
			fprintf(stderr,
					"TX RESTART: Detected blk %x that lies outside of the current retr block buffer window (max_block_num = %x) (if there was no tx restart, increase window size via -d)\n",
					block_num, max_block_num);
			block_buffer_list_reset(block_buffer_list, param_block_buffers, param_data_packets_per_block + param_fec_packets_per_block);
		}
		//first, find the minimum block num in the buffers list. this will be the block that we replace
		int min_block_num = INT_MAX;
		int min_block_num_idx;
		for (i = 0; i < param_block_buffers; ++i) {
			if (block_buffer_list[i].block_num < min_block_num) {
				min_block_num = block_buffer_list[i].block_num;
				min_block_num_idx = i;
			}
		}
		packet_buffer_t *packet_buffer_list = block_buffer_list[min_block_num_idx].packet_buffer_list;
		int last_block_num = block_buffer_list[min_block_num_idx].block_num;
		if (last_block_num != -1) {
			rx_status->received_block_cnt++;
			//we have both pointers to the packet buffers (to get information about crc and vadility) and raw data pointers for fec_decode
			packet_buffer_t *data_pkgs[MAX_DATA_OR_FEC_PACKETS_PER_BLOCK];
			packet_buffer_t *fec_pkgs[MAX_DATA_OR_FEC_PACKETS_PER_BLOCK];
			uint8_t *data_blocks[MAX_DATA_OR_FEC_PACKETS_PER_BLOCK];
			uint8_t *fec_blocks[MAX_DATA_OR_FEC_PACKETS_PER_BLOCK];
			int datas_missing = 0, datas_corrupt = 0, fecs_missing = 0, fecs_corrupt = 0;
			int di = 0, fi = 0;
			//first, split the received packets into DATA a FEC packets and count the damaged packets
			i = 0;
			while (di < param_data_packets_per_block || fi < param_fec_packets_per_block) {
				if (di < param_data_packets_per_block) {
					data_pkgs[di] = packet_buffer_list + i++;
					data_blocks[di] = data_pkgs[di]->data;
					if (!data_pkgs[di]->valid) {
						datas_missing++;
					}
					if (data_pkgs[di]->valid && !data_pkgs[di]->crc_correct) {
						datas_corrupt++;
					}
					di++;
				}
				if (fi < param_fec_packets_per_block) {
					fec_pkgs[fi] = packet_buffer_list + i++;
					if (!fec_pkgs[fi]->valid) {
						fecs_missing++;
					}
					if (fec_pkgs[fi]->valid && !fec_pkgs[fi]->crc_correct) {
						fecs_corrupt++;
					}
					fi++;
				}
			}
			const int good_fecs_c = param_fec_packets_per_block - fecs_missing - fecs_corrupt;
			const int datas_missing_c = datas_missing;
			const int datas_corrupt_c = datas_corrupt;
			const int fecs_missing_c = fecs_missing;
			const int fecs_corrupt_c = fecs_corrupt;
			int good_fecs = good_fecs_c;
			//the following three fields are infos for fec_decode
			unsigned int fec_block_nos[MAX_DATA_OR_FEC_PACKETS_PER_BLOCK];
			unsigned int erased_blocks[MAX_DATA_OR_FEC_PACKETS_PER_BLOCK];
			unsigned int nr_fec_blocks = 0;
			fi = 0;
			di = 0;
			//look for missing DATA and replace them with good FECs
			while (di < param_data_packets_per_block && fi < param_fec_packets_per_block) {
				//if this data is fine we go to the next
				if (data_pkgs[di]->valid && data_pkgs[di]->crc_correct) {
					di++;
					continue;
				}
				//if this DATA is corrupt and there are less good fecs than missing datas we cannot do anything for this data
				if (data_pkgs[di]->valid && !data_pkgs[di]->crc_correct && good_fecs <= datas_missing) {
					di++;
					continue;
				}
				//if this FEC is not received we go on to the next
				if (!fec_pkgs[fi]->valid) {
					fi++;
					continue;
				}
				//if this FEC is corrupted and there are more lost packages than good fecs we should replace this DATA even with this corrupted FEC
				if (!fec_pkgs[fi]->crc_correct && datas_missing > good_fecs) {
					fi++;
					continue;
				}
				if (!data_pkgs[di]->valid) {
					datas_missing--;
				} else if (!data_pkgs[di]->crc_correct) {
					datas_corrupt--;
				}
				if (fec_pkgs[fi]->crc_correct) {
					good_fecs--;
				}
				//at this point, data is invalid and fec is good -> replace data with fec
				erased_blocks[nr_fec_blocks] = di;
				fec_block_nos[nr_fec_blocks] = fi;
				fec_blocks[nr_fec_blocks] = fec_pkgs[fi]->data;
				di++;
				fi++;
				nr_fec_blocks++;
			}
			int reconstruction_failed = datas_missing_c + datas_corrupt_c > good_fecs_c;
			if (reconstruction_failed) {
				//we did not have enough FEC packets to repair this block
				rx_status->damaged_block_cnt++;
				fprintf(stderr, "Could not fully reconstruct block %x! Damage rate: %f (%d / %d blocks)\n", last_block_num,
						1.0 * rx_status->damaged_block_cnt / rx_status->received_block_cnt, rx_status->damaged_block_cnt, rx_status->received_block_cnt);
				debug_print("Data mis: %d\tData corr: %d\tFEC mis: %d\tFEC corr: %d\n", datas_missing_c, datas_corrupt_c, fecs_missing_c, fecs_corrupt_c);
			}
			//decode data and write it to STDOUT
			fec_decode((unsigned int) param_packet_length, data_blocks, param_data_packets_per_block, fec_blocks, fec_block_nos, erased_blocks, nr_fec_blocks);
			for (i = 0; i < param_data_packets_per_block; ++i) {
				payload_header_t *ph = (payload_header_t*)data_blocks[i];
				if (!reconstruction_failed || data_pkgs[i]->valid) {
					//if reconstruction did fail, the data_length value is undefined. better limit it to some sensible value
					if (ph->data_length > param_packet_length) {
						ph->data_length = param_packet_length;
					}

#ifdef USE_FIFO
					fwrite(data_blocks[i] + sizeof(payload_header_t), ph->data_length, 1, wifibc_fr);
#else
					int n = 0;
					for (n = 0; n < ph->data_length; n++) {
						uint8_t *bit = data_blocks[i] + sizeof(payload_header_t) + n;
						//						BufferIn(bit[0]);
						QueuePut(bit[0]);
					}
#endif
				}
			}
			//reset buffers
			for (i = 0; i < param_data_packets_per_block + param_fec_packets_per_block; ++i) {
				packet_buffer_t *p = packet_buffer_list + i;
				p->valid = 0;
				p->crc_correct = 0;
				p->len = 0;
			}
		}
		block_buffer_list[min_block_num_idx].block_num = block_num;
		max_block_num = block_num;
	}
	//find the buffer into which we have to write this packet
	block_buffer_t *rbb = block_buffer_list;
	for (i = 0; i < param_block_buffers; ++i) {
		if (rbb->block_num == block_num) {
			break;
		}
		rbb++;
	}
	//check if we have actually found the corresponding block. this could not be the case due to a corrupt packet
	if (i != param_block_buffers) {
		packet_buffer_t *packet_buffer_list = rbb->packet_buffer_list;
		packet_num = wph->sequence_number % (param_data_packets_per_block + param_fec_packets_per_block);
		//only overwrite packets where the checksum is not yet correct. otherwise the packets are already received correctly
		if (packet_buffer_list[packet_num].crc_correct == 0) {
			memcpy(packet_buffer_list[packet_num].data, data, data_len);
			packet_buffer_list[packet_num].len = data_len;
			packet_buffer_list[packet_num].valid = 1;
			packet_buffer_list[packet_num].crc_correct = crc_correct;
		}
	}
}

void process_packet(monitor_interface_t *interface, block_buffer_t *block_buffer_list, int adapter_no) {
	struct pcap_pkthdr * ppcapPacketHeader = NULL;
	struct ieee80211_radiotap_iterator rti;
	PENUMBRA_RADIOTAP_DATA prd;
	u8 payloadBuffer[MAX_PACKET_LENGTH];
	u8 *pu8Payload = payloadBuffer;
	int bytes;
	int n;
	int retval;
	int u16HeaderLen;
	retval = pcap_next_ex(interface->ppcap, &ppcapPacketHeader, (const u_char**)&pu8Payload);
	if (retval < 0) {
		fprintf(stderr, "Socket broken\n");
		fprintf(stderr, "%s\n", pcap_geterr(interface->ppcap));
		return;
	}
	if (retval != 1) {
		return;
	}
	u16HeaderLen = (pu8Payload[2] + (pu8Payload[3] << 8));
	if (ppcapPacketHeader->len < (u16HeaderLen + interface->n80211HeaderLength)) {
		return;
	}
	bytes = ppcapPacketHeader->len - (u16HeaderLen + interface->n80211HeaderLength);
	if (bytes < 0) {
		return;
	}
	if (ieee80211_radiotap_iterator_init(&rti, (struct ieee80211_radiotap_header *)pu8Payload, ppcapPacketHeader->len) < 0) {
		return;
	}
	while ((n = ieee80211_radiotap_iterator_next(&rti)) == 0) {
		switch (rti.this_arg_index) {
			case IEEE80211_RADIOTAP_RATE:
				prd.m_nRate = (*rti.this_arg);
				break;
			case IEEE80211_RADIOTAP_CHANNEL:
				prd.m_nChannel = le16_to_cpu(*((u16 *)rti.this_arg));
				prd.m_nChannelFlags = le16_to_cpu(*((u16 *)(rti.this_arg + 2)));
				break;
			case IEEE80211_RADIOTAP_ANTENNA:
				prd.m_nAntenna = (*rti.this_arg) + 1;
				break;
			case IEEE80211_RADIOTAP_FLAGS:
				prd.m_nRadiotapFlags = *rti.this_arg;
				break;
			case IEEE80211_RADIOTAP_DBM_ANTSIGNAL:
				rx_status->adapter[adapter_no].current_signal_dbm = (int8_t)(*rti.this_arg);
				GroundData.wifibc_rssi[adapter_no] = (int8_t)(*rti.this_arg);
				break;
		}
	}
	pu8Payload += u16HeaderLen + interface->n80211HeaderLength;
	if (prd.m_nRadiotapFlags & IEEE80211_RADIOTAP_F_FCS) {
		bytes -= 4;
	}
	int checksum_correct = (prd.m_nRadiotapFlags & 0x40) == 0;
	if (!checksum_correct) {
		rx_status->adapter[adapter_no].wrong_crc_cnt++;
	}
	rx_status->adapter[adapter_no].received_packet_cnt++;
	rx_status->last_update = time(NULL);
	process_payload(pu8Payload, bytes, checksum_correct, block_buffer_list, adapter_no);
}

void status_memory_init(wifibroadcast_rx_status_t *s) {
	s->received_block_cnt = 0;
	s->damaged_block_cnt = 0;
	s->tx_restart_cnt = 0;
	s->wifi_adapter_cnt = 0;

	int i = 0;
	for (i = 0; i < MAX_PENUMBRA_INTERFACES; ++i) {
		s->adapter[i].received_packet_cnt = 0;
		s->adapter[i].wrong_crc_cnt = 0;
		s->adapter[i].current_signal_dbm = 0;
	}
}

wifibroadcast_rx_status_t *status_memory_open(void) {
	char buf[128];
	int fd;
	sprintf(buf, "/wifibroadcast_rx_status_%d", param_port);
	fd = shm_open(buf, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd < 0) {
		perror("shm_open");
		return NULL;
	}
	if (ftruncate(fd, sizeof(wifibroadcast_rx_status_t)) == -1) {
		perror("ftruncate");
		return NULL;
	}
	void *retval = mmap(NULL, sizeof(wifibroadcast_rx_status_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (retval == MAP_FAILED) {
		perror("mmap");
		return NULL;
	}
	wifibroadcast_rx_status_t *tretval = (wifibroadcast_rx_status_t*)retval;
	status_memory_init(tretval);
	return tretval;
}

int readFunction (void *opaque, uint8_t *buf, int buf_size) {
#ifdef USE_FIFO
	int numBytes = fread((char*)buf, 1, buf_size, infd);
#else
	int n = 0;
	for (n = 0; n < buf_size; n++) {
		//		BufferOut(buf + n);

		QueueGet(buf + n);
	}
	int numBytes = buf_size;
#endif
	return numBytes;
}

int wifibc_update_video (void *data) {
	AVFormatContext *pFormatCtx = NULL;
	int             i = 0;
	int             videoStream = -1;
	AVCodecContext  *pCodecCtxOrig = NULL;
	AVCodecContext  *pCodecCtx = NULL;
	AVCodec         *pCodec = NULL;
	AVFrame         *pFrame = NULL;
	AVFrame         *pFrameRGB = NULL;
	AVPacket        packet;
	int             frameFinished;
	struct SwsContext *sws_ctx = NULL;
	AVIOContext       *avioContext = NULL;
	unsigned char     *ioBuffer = NULL;
	const int         ioBufferSize = 32768;
	int               numBytes;
	uint8_t           *buffer = NULL;

	av_register_all();
	ioBuffer = (unsigned char *)av_malloc(ioBufferSize + FF_INPUT_BUFFER_PADDING_SIZE);
#ifdef USE_FIFO
	if ((infd = fopen("/tmp/fifo.avi", "rb")) == NULL) {
		fprintf(stderr, "error reading fifo: /tmp/fifo.avi\n");
	}
	avioContext = avio_alloc_context(ioBuffer, ioBufferSize, 0, (void*)(&infd), &readFunction, NULL, NULL);
#else
	avioContext = avio_alloc_context(ioBuffer, ioBufferSize, 0, NULL, &readFunction, NULL, NULL);
#endif
	pFormatCtx = avformat_alloc_context();
	pFormatCtx->pb = avioContext;
	if (avformat_open_input(&pFormatCtx, "wifibc", NULL, NULL)!=0) {
		return -1;
	}
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
		return -1;
	}
	for (i = 0; i < pFormatCtx->nb_streams; i++)
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoStream = i;
			break;
		}
	if (videoStream == -1) {
		return -1;
	}
	pCodecCtxOrig = pFormatCtx->streams[videoStream]->codec;
	pCodec = avcodec_find_decoder(pCodecCtxOrig->codec_id);
	if (pCodec == NULL) {
		fprintf(stderr, "Unsupported codec!\n");
		return -1;
	}
	pCodecCtx = avcodec_alloc_context3(pCodec);
	if (avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0) {
		fprintf(stderr, "Couldn't copy codec context");
		return -1;
	}
	if (avcodec_open2(pCodecCtx, pCodec, NULL)<0) {
		return -1;
	}
	pFrame = av_frame_alloc();
	if (pFrame == NULL) {
		return -1;
	}
	pFrameRGB = av_frame_alloc();
	if (pFrameRGB == NULL) {
		return -1;
	}
	wifibc_surface = SDL_CreateRGBSurface(0, pCodecCtx->width, pCodecCtx->height, 24, 0x0000ff, 0x00ff00, 0xff0000, 0);
	wifibc_bg = SDL_CreateRGBSurface(0, pCodecCtx->width, pCodecCtx->height, 24, 0x0000ff, 0x00ff00, 0xff0000, 0);
	numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
	buffer = (uint8_t *)av_malloc(numBytes*sizeof(uint8_t));
	avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
	sws_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, PIX_FMT_RGB24,
							 SWS_BICUBIC, NULL, NULL, NULL);
	while (av_read_frame(pFormatCtx, &packet) >= 0 && wifibc_running2 == 1) {
		if (packet.stream_index == videoStream) {
			avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
			if (frameFinished) {
				sws_scale(sws_ctx, (uint8_t const * const *)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
				SDL_Surface *image = SDL_CreateRGBSurfaceFrom(
										 pFrameRGB->data[0],
										 pCodecCtx->width, pCodecCtx->height,
										 24,
										 pCodecCtx->width * 3,
										 0x0000ff, 0x00ff00, 0xff0000, 0
									 );
				SDL_LockMutex(wifibc_mutex);
				SDL_BlitSurface(image, NULL, wifibc_bg, NULL);
				SDL_UnlockMutex(wifibc_mutex);
				SDL_FreeSurface(image);
			}
		}
		av_free_packet(&packet);
	}
	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	avcodec_close(pCodecCtxOrig);
	avformat_close_input(&pFormatCtx);
	return 0;
}

int wifibc_update_stream (void *data) {
	monitor_interface_t interfaces[MAX_PENUMBRA_INTERFACES];
	int num_interfaces = 0;
	int i;
	block_buffer_t *block_buffer_list;
	param_port = setup.wifibc_port;
	param_data_packets_per_block = setup.wifibc_blocksize;
	//	param_fec_packets_per_block = atoi(optarg);
	//	param_block_buffers = atoi(optarg);
	//	param_packet_length = atoi(optarg);
	if (param_packet_length > MAX_USER_PACKET_LENGTH) {
		SDL_Log("wifibc: Packet length is limited to %d bytes (you requested %d bytes)\n", MAX_USER_PACKET_LENGTH, param_packet_length);
		return (1);
	}
	fec_init();
	int x = optind;
	if (open_and_configure_interface("wlan1", param_port, interfaces + num_interfaces) != 0) {
		SDL_Log("wifibc: faild open wifi: %s\n", "wlan1");
		return 1;
	}
	++num_interfaces;
	++x;
#ifdef USE_FIFO
	wifibc_fr = fopen("/tmp/fifo.avi", "wb");
#endif
	//block buffers contain both the block_num as well as packet buffers for a block.
	block_buffer_list = malloc(sizeof(block_buffer_t) * param_block_buffers);
	for (i = 0; i < param_block_buffers; ++i) {
		block_buffer_list[i].block_num = -1;
		block_buffer_list[i].packet_buffer_list = lib_alloc_packet_buffer_list(param_data_packets_per_block+param_fec_packets_per_block,
				MAX_PACKET_LENGTH);
	}
	rx_status = status_memory_open();
	rx_status->wifi_adapter_cnt = num_interfaces;
	SDL_Log("wifibc: start stream\n");
	while (wifibc_running == 1) {
		fd_set readset;
		struct timeval to;
		to.tv_sec = 0;
		to.tv_usec = 1e5;
		FD_ZERO(&readset);
		for (i = 0; i < num_interfaces; ++i) {
			FD_SET(interfaces[i].selectable_fd, &readset);
		}
		int n = select(30, &readset, NULL, NULL, &to);
		for (i = 0; i < num_interfaces; ++i) {
			if (n == 0) {
				break;
			}
			if (FD_ISSET(interfaces[i].selectable_fd, &readset)) {
				process_packet(interfaces + i, block_buffer_list, i);
			}
		}
	}
#ifdef USE_FIFO
	fclose(wifibc_fr);
#endif
	wifibc_running2 = 0;
	return (0);
}

void wifibc_init (void) {
	char cmd_str[1024];
	SDL_Log("wifibc: init\n");
#ifdef USE_FIFO
	system("rm -rf /tmp/fifo.avi");
	system("mkfifo /tmp/fifo.avi");
#endif
	sprintf(cmd_str, "ifconfig %s down", setup.wifibc_device);
	system(cmd_str);
	sprintf(cmd_str, "iw dev %s set monitor otherbss fcsfail", setup.wifibc_device);
	system(cmd_str);
	sprintf(cmd_str, "ifconfig %s up", setup.wifibc_device);
	system(cmd_str);
	sprintf(cmd_str, "iwconfig %s channel %i", setup.wifibc_device, setup.wifibc_channel);
	system(cmd_str);
	wifibc_running = 1;
	wifibc_running2 = 1;
#ifdef SDL2
	wifibc_thread_stream = SDL_CreateThread(wifibc_update_stream, NULL, NULL);
	wifibc_thread_video = SDL_CreateThread(wifibc_update_video, NULL, NULL);
#else
	wifibc_thread_stream = SDL_CreateThread(wifibc_update_stream, NULL);
	wifibc_thread_video = SDL_CreateThread(wifibc_update_video, NULL);
#endif
}

void wifibc_exit (void) {
	wifibc_running = 0;
	SDL_WaitThread(wifibc_thread_stream, NULL);
	SDL_WaitThread(wifibc_thread_video, NULL);
}

SDL_Surface *wifibc_get (void) {
	SDL_LockMutex(wifibc_mutex);
	if (wifibc_bg != NULL) {
		SDL_BlitSurface(wifibc_bg, NULL, wifibc_surface, NULL);
		SDL_UnlockMutex(wifibc_mutex);


/*
static IplImage *gray = NULL;
static IplImage *edge = NULL;
static IplImage *cv_image = NULL;
static CvMemStorage *storage = NULL;
int edge_thresh = 1;
int i = 0;

if (cv_image == NULL) {
	cv_image = cvCreateImageHeader(cvSize(wifibc_surface->w, wifibc_surface->h), IPL_DEPTH_8U, 3);
}
if (gray == NULL) {
	gray = cvCreateImage(cvGetSize(cv_image), cv_image->depth, 1);
}
if (edge == NULL) {
	edge = cvCreateImage(cvSize(cv_image->width, cv_image->height), 8, 1);
}
if (storage == NULL) {
	storage = cvCreateMemStorage(0);
}
cvSetData(cv_image, wifibc_surface->pixels, cv_image->widthStep);
cvCvtColor(cv_image, gray, CV_BGR2GRAY);
cvThreshold(gray, gray, CV_GAUSSIAN, 9, 9);
cvSmooth(gray, gray, CV_GAUSSIAN, 11, 11, 0, 0); 
cvCanny(gray, edge, (float)edge_thresh, (float)edge_thresh * 3, 5);
CvSeq* circles = cvHoughCircles(edge, storage, CV_HOUGH_GRADIENT, 2, gray->height / 2, 200, 100, 200, 0);
for (i = 0; i < circles->total; i++) {
	float* p = (float*)cvGetSeqElem(circles, i);
	cvCircle(cv_image, cvPoint(cvRound(p[0]),cvRound(p[1])), 3, CV_RGB(0,255,0), -1, 8, 0 );
	cvCircle(cv_image, cvPoint(cvRound(p[0]),cvRound(p[1])), cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0 );
}

//cvSaveImage("/tmp/foo.png", cv_image, NULL);

*/

		return wifibc_surface;
	}
	SDL_UnlockMutex(wifibc_mutex);
	return NULL;
}

#endif

