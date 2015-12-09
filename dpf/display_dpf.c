
#include <stdio.h>
#include <dpf.h>
#include <fonts.h>

#define DISPLAY_W 320
#define DISPLAY_H 240

static DPFHANDLE h;
static uint8_t image[2 * DISPLAY_W *DISPLAY_H];
static uint8_t fscale = 3;

void dpf_set(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);

uint16_t dpf_draw_char(uint16_t x, uint16_t y, uint16_t ch, uint8_t r, uint8_t g, uint8_t b) {
	uint16_t n = 0;
	uint16_t n2 = 0;
	uint8_t ret = 0;
	uint16_t y_offset = 8 - 8;
	if (x + 7 < DISPLAY_W) {
		if (ch >= 32) {
			ch -= 32;
			for (n = 0; n < 7; n++) {
				for (n2 = 0; n2 < 8; n2++) {
					if (au8FontSystem7x8[ch * 7 + n] & (1 << (n2 + y_offset))) {
						ret = n * fscale;
						uint8_t sx = 0;
						uint8_t sy = 0;
						for (sx = 0; sx < fscale; sx++) {
							for (sy = 0; sy < fscale; sy++) {
								dpf_set(x + sx + n * fscale, y + sy + n2 * fscale, r, g, b);
							}
						}
					}
				}
			}
		}
	}
	return ret;
}

uint16_t dpf_draw_string(uint16_t x, uint16_t y, char *string, uint8_t r, uint8_t g, uint8_t b) {
	uint16_t xn = x;
	while (*string) {
		r = 255 - xn;
		g = 255 - y;
		b = y + xn;
		if (xn > 320 - 8 * fscale || (*string) == ' ' || (*string) == ',') {
			xn = x;
			y += 9 * fscale;
		}
		xn += dpf_draw_char(xn, y, (*string++), r, g, b) + 2 * fscale;
	}
	if (fscale++ > 2) {
		fscale = 1;
	}
	return xn;
}




void dpf_init(void) {
	if (dpf_open(NULL, &h) < 0) {
		printf("dpf: error opening DPF device\n");
	}
}

void dpf_fill(uint8_t r, uint8_t g, uint8_t b) {
	uint16_t x;
	uint16_t y;
	uint8_t *bytes = image;
	for (y = 0; y < DISPLAY_H; y++) {
		for (x = 0; x < DISPLAY_W; x++) {
			*bytes++ = RGB565_0(r, g, b + y / 2);
			*bytes++ = RGB565_1(r, g, b + y / 2);
		}
	}
}

void dpf_set(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b) {
	image[2 * (y * DISPLAY_W + x) + 0] = RGB565_0(r, g, b);
	image[2 * (y * DISPLAY_W + x) + 1] = RGB565_1(r, g, b);
}

void dpf_update(void) {
	write_screen(h, image, sizeof(image));
}

void dpf_exit(void) {
	dpf_close(h);
}

