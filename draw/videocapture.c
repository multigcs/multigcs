/* 
 * Copyright (C) 2012 by Tomasz Moń <desowin@gmail.com>
 *
 * Based on V4L2 video capture example
 *
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software for any purpose
 * with or without fee is hereby granted, provided that the above copyright
 * notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 * OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of a copyright holder shall not
 * be used in advertising or otherwise to promote the sale, use or other dealings
 * in this Software without prior written authorization of the copyright holder.
 */

#include <all.h>

#if defined USE_V4L

#if !defined WINDOWS && !defined OSX

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_video.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>             /* getopt_long() */
#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h>          /* for videodev2.h */
#include <linux/videodev2.h>
#include <videocapture.h>

#define CLEAR(x) memset (&(x), 0, sizeof (x))
#define mask32(BYTE) (*(uint32_t *)(uint8_t [4]){ [BYTE] = 0xff })
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a > b ? b : a)
#define DEFAULT_WIDTH 640;
#define DEFAULT_HEIGHT 480;
#define COLOR_GET_RED(color)   ((color >> 16) & 0xFF)
#define COLOR_GET_GREEN(color) ((color >> 8) & 0xFF)
#define COLOR_GET_BLUE(color)  (color & 0xFF)

static uint8_t pixeltype = 0;

typedef enum {
    IO_METHOD_READ,
    IO_METHOD_MMAP,
    IO_METHOD_USERPTR,
} io_method;

struct buffer {
    void *start;
    size_t length;
};

static char dev_name[1024];
static io_method io = IO_METHOD_MMAP;
static int fd = -1;
struct buffer *buffers = NULL;
static unsigned int n_buffers = 0;
static size_t WIDTH = DEFAULT_WIDTH;
static size_t HEIGHT = DEFAULT_HEIGHT;
static uint8_t *buffer_sdl;
uint8_t video_ok = 1;
SDL_Surface *data_sf = NULL;
uint32_t YCbCr_to_RGB[256][256][256];

static void errno_exit(const char *s) {
	fprintf(stderr, "videocapture: * %s error %d, %s\n", s, errno, strerror(errno));
	video_ok = 0;
}

static int xioctl(int fd, int request, void *arg) {
	int r;
	do {
		r = ioctl(fd, request, arg);
	} while (-1 == r && EINTR == errno);
	return r;
}

void YCbCrToRGB(int y, int cb, int cr, uint8_t * r, uint8_t * g, uint8_t * b) {
	double Y = (double)y;
	double Cb = (double)cb;
	double Cr = (double)cr;
	int R = (int)(Y + 1.40200 * (Cr - 0x80));
	int G = (int)(Y - 0.34414 * (Cb - 0x80) - 0.71414 * (Cr - 0x80));
	int B = (int)(Y + 1.77200 * (Cb - 0x80));
	*r = max(0, min(255, R));
	*g = max(0, min(255, G));
	*b = max(0, min(255, B));
}

static void generate_YCbCr_to_RGB_lookup() {
    int y;
    int cb;
    int cr;

    for (y = 0; y < 256; y++) {
        for (cb = 0; cb < 256; cb++) {
            for (cr = 0; cr < 256; cr++) {
                double Y = (double)y;
                double Cb = (double)cb;
                double Cr = (double)cr;
                int R = (int)(Y+1.40200*(Cr - 0x80));
                int G = (int)(Y-0.34414*(Cb - 0x80)-0.71414*(Cr - 0x80));
                int B = (int)(Y+1.77200*(Cb - 0x80));
                R = max(0, min(255, R));
                G = max(0, min(255, G));
                B = max(0, min(255, B));
                YCbCr_to_RGB[y][cb][cr] = R << 16 | G << 8 | B;
            }
        }
    }
}

static void inline YUV422_to_RGB(uint8_t * output, const uint8_t * input) {
    uint8_t y0 = input[0];
    uint8_t cb = input[1];
    uint8_t y1 = input[2];
    uint8_t cr = input[3];

    uint32_t rgb = YCbCr_to_RGB[y0][cb][cr];
    output[0] = COLOR_GET_RED(rgb);
    output[1] = COLOR_GET_GREEN(rgb);
    output[2] = COLOR_GET_BLUE(rgb);

    rgb = YCbCr_to_RGB[y1][cb][cr];
    output[3] = COLOR_GET_RED(rgb);
    output[4] = COLOR_GET_GREEN(rgb);
    output[5] = COLOR_GET_BLUE(rgb);
}

static void process_image(const void *p) {
	const uint8_t *buffer_yuv = p;
	size_t x;
	size_t y;
	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x += 2) {
			YUV422_to_RGB(buffer_sdl + (y * WIDTH + x) * 3, buffer_yuv + (y * WIDTH + x) * 2);
		}
	}
}

SDL_Surface *load_image (char * buff, int size) {
	SDL_RWops *rw = SDL_RWFromMem(buff,size );
	SDL_Surface *temp = IMG_Load_RW(rw, 1);
	if (temp == NULL) {
		SDL_Log("IMG_Load_RW: %s\n", IMG_GetError());
		return NULL;
	}
	return temp;
} 

static int read_frame(void) {
    struct v4l2_buffer buf;
    unsigned int i;
    switch (io) {
    case IO_METHOD_READ:
        if (-1 == read(fd, buffers[0].start, buffers[0].length)) {
            switch (errno)
            {
            case EAGAIN:
                return 0;

            case EIO:
                /* Could ignore EIO, see spec. */

                /* fall through */

            default:
                errno_exit("read");
            }
        }
        process_image(buffers[0].start);
        break;
    case IO_METHOD_MMAP:
        CLEAR(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf)) {
            switch (errno) {
            case EAGAIN:
                return 0;
            case EIO:
                /* Could ignore EIO, see spec. */
                /* fall through */
            default:
                errno_exit("VIDIOC_DQBUF");
            }
        }
	assert(buf.index < n_buffers);

	if (pixeltype == 2) {
		if (data_sf != NULL) {
			SDL_FreeSurface(data_sf);
			data_sf = NULL;
		}
		data_sf = load_image(buffers[buf.index].start, buf.bytesused);
	} else {
		process_image(buffers[buf.index].start);
	}

	if (-1 == xioctl(fd, VIDIOC_QBUF, &buf)) {
		errno_exit("VIDIOC_QBUF");
	}
	break;
    case IO_METHOD_USERPTR:
        CLEAR(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_USERPTR;
        if (-1 == xioctl(fd, VIDIOC_DQBUF, &buf)) {
            switch (errno) {
            case EAGAIN:
                return 0;
            case EIO:
                /* Could ignore EIO, see spec. */
                /* fall through */
            default:
                errno_exit("VIDIOC_DQBUF");
            }
        }
        for (i = 0; i < n_buffers; ++i) {
            if (buf.m.userptr == (unsigned long)buffers[i].start && buf.length == buffers[i].length) {
                break;
            }
        }
        assert(i < n_buffers);
        process_image((void *)buf.m.userptr);
        if (-1 == xioctl(fd, VIDIOC_QBUF, &buf)) {
            errno_exit("VIDIOC_QBUF");
        }
        break;
    }
    return 1;
}

SDL_Surface *videodev_loop (void) {
	if (video_ok == 0) {
		return 0;
	}
        for (;;) {
            fd_set fds;
            struct timeval tv;
            int r;
            FD_ZERO(&fds);
            FD_SET(fd, &fds);
            /* Timeout. */
            tv.tv_sec = 2;
            tv.tv_usec = 0;
            r = select(fd + 1, &fds, NULL, NULL, &tv);
            if (-1 == r) {
                if (EINTR == errno) {
                    continue;
                }
                errno_exit("select");
                return NULL;
            }
            if (0 == r) {
                fprintf(stderr, "videocapture: select timeout\n");
                return NULL;
            }
            if (read_frame()) {
                break;
            }
        }
	return data_sf;
}

static void stop_capturing(void) {
    enum v4l2_buf_type type;
    switch (io) {
    case IO_METHOD_READ:
        /* Nothing to do. */
        break;
    case IO_METHOD_MMAP:
    case IO_METHOD_USERPTR:
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (-1 == xioctl(fd, VIDIOC_STREAMOFF, &type)) {
//            errno_exit("VIDIOC_STREAMOFF");
        }
        break;
    }
}

static void start_capturing(void) {
    unsigned int i;
    enum v4l2_buf_type type;
    switch (io) {
    case IO_METHOD_READ:
        break;
    case IO_METHOD_MMAP:
        for (i = 0; i < n_buffers; ++i) {
            struct v4l2_buffer buf;
            CLEAR(buf);
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index = i;
            if (-1 == xioctl(fd, VIDIOC_QBUF, &buf)) {
                errno_exit("VIDIOC_QBUF");
	    }
        }
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (-1 == xioctl(fd, VIDIOC_STREAMON, &type)) {
            errno_exit("VIDIOC_STREAMON");
	}
        break;
    case IO_METHOD_USERPTR:
        for (i = 0; i < n_buffers; ++i) {
            struct v4l2_buffer buf;
            CLEAR(buf);
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_USERPTR;
            buf.index = i;
            buf.m.userptr = (unsigned long)buffers[i].start;
            buf.length = buffers[i].length;
            if (-1 == xioctl(fd, VIDIOC_QBUF, &buf)) {
                errno_exit("VIDIOC_QBUF");
	    }
        }
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (-1 == xioctl(fd, VIDIOC_STREAMON, &type)) {
            errno_exit("VIDIOC_STREAMON");
	}
        break;
    }
}

static void uninit_device(void) {
	unsigned int i;
	switch (io) {
		case IO_METHOD_READ:
			free(buffers[0].start);
		break;
		case IO_METHOD_MMAP:
			for (i = 0; i < n_buffers; ++i) {
				if (-1 == munmap(buffers[i].start, buffers[i].length)) {
					errno_exit("munmap");
				}
			}
		break;
		case IO_METHOD_USERPTR:
			for (i = 0; i < n_buffers; ++i) {
				free(buffers[i].start);
			}
		break;
	}
	free(buffers);
}

static void init_read(unsigned int buffer_size) {
    buffers = calloc(1, sizeof(*buffers));
    if (!buffers) {
        fprintf(stderr, "videocapture: Out of memory\n");
        exit(EXIT_FAILURE);
    }
    buffers[0].length = buffer_size;
    buffers[0].start = malloc(buffer_size);
    if (!buffers[0].start) {
        fprintf(stderr, "videocapture: Out of memory\n");
        exit(EXIT_FAILURE);
    }
}

static void init_mmap(void) {
    struct v4l2_requestbuffers req;
    CLEAR(req);
    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            fprintf(stderr, "videocapture: %s does not support memory mapping\n", dev_name);
            return;
        } else {
            errno_exit("VIDIOC_REQBUFS");
            return;
        }
    }
    if (req.count < 2) {
        fprintf(stderr, "videocapture: Insufficient buffer memory on %s\n", dev_name);
        return;
    }
    buffers = calloc(req.count, sizeof(*buffers));
    if (!buffers) {
        fprintf(stderr, "videocapture: Out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
        struct v4l2_buffer buf;
        CLEAR(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = n_buffers;
        if (-1 == xioctl(fd, VIDIOC_QUERYBUF, &buf)) {
            errno_exit("VIDIOC_QUERYBUF");
            return;
	}
        buffers[n_buffers].length = buf.length;
        buffers[n_buffers].start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
        if (MAP_FAILED == buffers[n_buffers].start) {
            errno_exit("mmap");
	}
    }
}

static void init_userp(unsigned int buffer_size) {
    struct v4l2_requestbuffers req;
    unsigned int page_size;
    page_size = getpagesize();
    buffer_size = (buffer_size + page_size - 1) & ~(page_size - 1);
    CLEAR(req);
    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_USERPTR;
    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            fprintf(stderr, "videocapture: %s does not support "
                    "user pointer i/o\n", dev_name);
            exit(EXIT_FAILURE);
        } else {
            errno_exit("VIDIOC_REQBUFS");
        }
    }
    buffers = calloc(4, sizeof(*buffers));
    if (!buffers) {
        fprintf(stderr, "videocapture: Out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (n_buffers = 0; n_buffers < 4; ++n_buffers) {
        buffers[n_buffers].length = buffer_size;
        buffers[n_buffers].start = memalign(page_size, buffer_size);
        if (!buffers[n_buffers].start) {
            fprintf(stderr, "videocapture: Out of memory\n");
            exit(EXIT_FAILURE);
        }
    }
}

static void init_device(void) {
    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    unsigned int min;
    if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &cap)) {
        if (EINVAL == errno) {
            fprintf(stderr, "videocapture: %s is no V4L2 device\n", dev_name);
            return;
        } else {
            return;
        }
    }
    SDL_Log("videocapture: driver  : %s\n", cap.driver);
    SDL_Log("videocapture: card    : %s\n", cap.card);
    SDL_Log("videocapture: bus_info: %s\n", cap.bus_info);
    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
        fprintf(stderr, "videocapture: %s is no video capture device\n", dev_name);
        return;
    }
    switch (io) {
    case IO_METHOD_READ:
        if (!(cap.capabilities & V4L2_CAP_READWRITE)) {
            fprintf(stderr, "videocapture: %s does not support read i/o\n", dev_name);
            exit(EXIT_FAILURE);
        }
        break;
    case IO_METHOD_MMAP:
    case IO_METHOD_USERPTR:
        if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
            fprintf(stderr, "videocapture: %s does not support streaming i/o\n", dev_name);
            exit(EXIT_FAILURE);
        }
        break;
    }
    CLEAR(cropcap);
    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (0 == xioctl(fd, VIDIOC_CROPCAP, &cropcap)) {
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect;   /* reset to default */
        if (-1 == xioctl(fd, VIDIOC_S_CROP, &crop)) {
            switch (errno) {
            case EINVAL:
                break;
            default:
                break;
            }
        }
    }
    CLEAR(fmt);
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = WIDTH;
    fmt.fmt.pix.height = HEIGHT;
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
    if (pixeltype == 2) {
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    } else {
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    }
    if (pixeltype == 0) {
        pixeltype = 1;
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;

        if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt)) {
            pixeltype = 2;
            fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
            if (-1 == xioctl(fd, VIDIOC_S_FMT, &fmt)) {
                errno_exit("VIDIOC_S_FMT");
            }
        }
    }
    min = fmt.fmt.pix.width * 2;
    if (fmt.fmt.pix.bytesperline < min)
        fmt.fmt.pix.bytesperline = min;
    min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    if (fmt.fmt.pix.sizeimage < min)
        fmt.fmt.pix.sizeimage = min;
    if (fmt.fmt.pix.width != WIDTH)
        WIDTH = fmt.fmt.pix.width;
    if (fmt.fmt.pix.height != HEIGHT)
        HEIGHT = fmt.fmt.pix.height;
    switch (io) {
    case IO_METHOD_READ:
        init_read(fmt.fmt.pix.sizeimage);
        break;
    case IO_METHOD_MMAP:
        init_mmap();
        break;
    case IO_METHOD_USERPTR:
        init_userp(fmt.fmt.pix.sizeimage);
        break;
    }
}

static void close_device(void) {
	if (fd != -1) {
		if (-1 == close(fd)) {
			errno_exit("close");
		}
		fd = -1;
	}
}

static void open_device(void) {
	struct stat st;
	if (-1 == stat(dev_name, &st)) {
		fprintf(stderr, "videocapture: Cannot identify '%s': %d, %s\n", dev_name, errno, strerror(errno));
		return;
	}
	if (!S_ISCHR(st.st_mode)) {
		fprintf(stderr, "videocapture: %s is no device\n", dev_name);
		return;
	}
	fd = open(dev_name, O_RDWR /* required */  | O_NONBLOCK, 0);
	if (-1 == fd) {
		fprintf(stderr, "videocapture: Cannot open '%s': %d, %s\n", dev_name, errno, strerror(errno));
		return;
	}
}

int videodev_stop (void) {
	SDL_Log("videocapture: exit\n");
	stop_capturing();
	close_device();
	uninit_device();
	if (data_sf != NULL) {
		SDL_FreeSurface(data_sf);
		data_sf = NULL;
	}
	free(buffer_sdl);
	return 0;
}

int videodev_start (char *device, uint16_t width, uint16_t height) {
	WIDTH = width;
	HEIGHT = height;
	SDL_Log("videocapture: init\n");
	strcpy(dev_name, device);
	generate_YCbCr_to_RGB_lookup();
	open_device();
	if (video_ok == 0) {
		SDL_Log("videocapture: open_device failed\n");
		return 0;
	}
	init_device();
	if (video_ok == 0) {
		SDL_Log("video: init_device failed\n");
		return 0;
	}
	buffer_sdl = (uint8_t*)malloc(WIDTH*HEIGHT*3);
	if (data_sf != NULL) {
		SDL_FreeSurface(data_sf);
		data_sf = NULL;
	}
	data_sf = SDL_CreateRGBSurfaceFrom(buffer_sdl, WIDTH, HEIGHT, 24, WIDTH * 3, mask32(0), mask32(1), mask32(2), 0);
	start_capturing();
	return 0;
}

#else

#include <SDL.h>

int videodev_stop (void) {
	return -1;
}

int videodev_start (char *device, uint16_t width, uint16_t height) {
	return -1;
}

SDL_Surface *videodev_loop (void) {
	return NULL;
}

#endif
#endif
