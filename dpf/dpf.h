/** libdpf header file

    (c) 2010, 2011 <hackfin@section5.ch>

*/

#include <usb.h>

#define ADDR unsigned int

#define MODE_USB 0x00  ///< libusb operation mode (hacked)
#define MODE_SG  0x01  ///< generic device mode (original)

enum {
	DEVERR_FILE = -16,
	DEVERR_OPEN,
	DEVERR_HEX,
	DEVERR_CHK,
	DEVERR_IO,
	DEVERR_MALLOC,
	DEVERR_TIMEOUT,
};

/** The DPF context structure */

typedef
struct dpf_context {
	unsigned char mode;
	union {
		usb_dev_handle *udev;
		int fd;
	} dev;
	unsigned int width;
	unsigned int height;
	int bpp;
	int proto;
	char *buff;
	unsigned char *oldpix;
	int offx;
	int offy;
} DPFContext;

#define DPFHANDLE struct dpf_context *

/**
    Opens the DPF device. if dev is not NULL, open device, otherwise, look for
    USB device.
*/
int dpf_open(const char *dev, DPFHANDLE *h);

/** Close DPF device */
void dpf_close(DPFHANDLE h);

/*
*/
void dpf_writefb(DPFHANDLE h, unsigned char *fb);

int dpf_screen_blit(DPFHANDLE h, const unsigned char *buf, short rect[4]);

/*
    Turn the backlight on or off
*/
void dpf_backlight(DPFHANDLE h, int on);

/* USB raw */

int emulate_scsi(usb_dev_handle *d, unsigned char *cmd, int cmdlen, char out,
				 unsigned char *data, unsigned long block_len);

const char *dev_errstr(int err);

// Private stuff:
usb_dev_handle *dpf_usb_open(void);
int sgdev_open(const char *portname, int *fd);

////////////////////////////////////////////////////////////////////////////
// FLASH stuff

// Maximum size for flash_read
#define MAX_CHUNKSIZE 0x10000

int read_mem(DPFHANDLE h, unsigned char *buf, ADDR offset, int len);
int write_mem(DPFHANDLE h, const char *hexfile);
int code_go(DPFHANDLE h, ADDR start);

int flash_cmd(DPFHANDLE h, int command, int cmdlen, ADDR addr);
int flash_probe(DPFContext *h, unsigned char *id);
int flash_erase(DPFHANDLE h, ADDR offset);
int flash_write(DPFHANDLE h, const unsigned char *buf, ADDR offset, int len);
int flash_read(DPFHANDLE h, unsigned char *buf, ADDR offset, int len);

int load_ihx(const char *fname, unsigned char *data,
			 unsigned int *buflen, unsigned int reloc);

int patch_sector(DPFHANDLE h,
				 ADDR reloc, unsigned long addr, const char *hexfile);

////////////////////////////////////////////////////////////////////////////
/* DPF specific stuff: */

#define RGB565_0(r, g, b) \
	(( ((r) & 0xf8)		 ) | (((g) & 0xe0) >> 5))
#define RGB565_1(r, g, b) \
	(( ((g) & 0x1c) << 3 ) | (((b) & 0xf8) >> 3))

#define RGB565(r, g, b) { RGB565_0(r, g, b), RGB565_1(r, g, b) }

int dpf_copy(ADDR dst, unsigned char *src, unsigned short n);

int set_screen(DPFHANDLE h, const unsigned char *col);
int write_screen(DPFHANDLE h, const unsigned char *buf, unsigned int len);


// Some internal address offsets. They may change, but so far all types
// seem to have the same
//
// w: word, <n>: length, [LE, BE]
//
// FIXME: Use packed struct later.

#define OFFSET_RESOLUTION 0x23   ///< w[2]:LE : Resolution X, Y
