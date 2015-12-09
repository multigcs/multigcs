
#include <all.h>

#if defined USE_OPENCV
#if defined USE_QUIRC

static void rgb32_to_luma(const uint8_t *src, int src_pitch, int w, int h, uint8_t *dst, int dst_pitch) {
	int i = 0;
	int y = 0;
	for (y = 0; y < h; y++) {
		const uint8_t *rgb32 = src + src_pitch * y;
		uint8_t *gray = dst + y * dst_pitch;
		for (i = 0; i < w; i++) {
			int r = (int)rgb32[2];
			int g = (int)rgb32[1];
			int b = (int)rgb32[0];
			int sum = r * 59 + g * 150 + b * 29;
			*(gray++) = sum >> 8;
			rgb32 += 4;
		}
	}
}

void qrcode_check(SDL_Surface *screen, char *payload) {
	struct quirc *qr;
	int count = 0;
	int i = 0;
	qr = quirc_new();
	if (!qr) {
		perror("couldn't allocate QR decoder");
		return;
	}
	if (quirc_resize(qr, screen->w, screen->h) < 0) {
		perror("couldn't allocate QR buffer");
		return;
	}
	rgb32_to_luma(screen->pixels, screen->pitch, screen->w, screen->h, quirc_begin(qr, NULL, NULL), screen->w);
	quirc_end(qr);
	count = quirc_count(qr);
	for (i = 0; i < count; i++) {
		struct quirc_code code;
		struct quirc_data data;
		quirc_decode_error_t err;
		quirc_extract(qr, i, &code);
		err = quirc_decode(&code, &data);
		if (! err) {
			strcpy(payload, (char *)data.payload);
		}
	}
	quirc_destroy(qr);
}

#endif
#endif
