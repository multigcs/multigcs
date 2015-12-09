
#include <stdio.h>
#include <dpf.h>

int demo(DPFHANDLE h) {
	static unsigned char image[2 * 320 * 240];
	int x, y;
	int i;
	for (i = 0; i < 255; i += 15) {
		printf("%i/255\n", i);
		unsigned char *b = image;
		for (y = 0; y < 240; y++) {
			for (x = 0; x < 320; x++) {
				*b++ = RGB565_0(i, 255 - i, y);
				*b++ = RGB565_1(i, 255 - i, y);
			}
		}
		write_screen(h, image, sizeof(image));
	}
	return 0;
}

int main(int argc, char **argv) {
	int ret;
	DPFHANDLE h;
	ret = dpf_open(NULL, &h);
	if (ret < 0) {
		perror("opening DPF device:");
		return ret;
	}
	demo(h);
	dpf_close(h);
	return ret;
}
