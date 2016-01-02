
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 512


char *basename (char *__filename);


int main (int argc, char *argv[]) {
	int fn = 0;
	char name[1024];
	printf("/*\n");
	fprintf(stderr, "#define FONT_MAX %i\n", argc - 1);
	fprintf(stderr, "char *fontnames[FONT_MAX] = {\n");
	for (fn = 0; fn < argc - 1; fn++) {
		strcpy(name, basename(argv[fn + 1]));
		printf("	%s\n", name);

		fprintf(stderr, "	\"%s\",\n", name);
	}
	fprintf(stderr, "};\n", name);
	printf("*/\n");
	printf("\n");

	printf("int fontdata[%i][96][%i] = {\n", argc - 1, MAX + 2);


	for (fn = 0; fn < argc - 1; fn++) {
		strcpy(name, basename(argv[fn + 1]));

		char line[1024];
		char ch[10240];
		int cn = 32;

		FILE *fd = fopen(argv[fn + 1], "r");

		printf("	{ // %s\n", name);

		while (fgets(line, 1000, fd) != NULL) {
			int n = 0;
			int m = 0;
			int u = 0;
			int len = 0;

			int x1 = 0;
			int y1 = 0;
			int x2 = 0;
			int y2 = 0;

			if (line[7] == ' ') {
				len = atoi(line + 7);
			} else {
				len = atoi(line + 6);
			}

			ch[0] = 0;

			while (line[10 + n] != '\n') {
				char c1 = line[10 + n];
				char c2 = line[10 + n + 1];
				if (c1 == ' ' && c2 == 'R') {
	//				printf("##\n");
	//				printf(",-1,-1");
					sprintf(ch + strlen(ch), ", -1,-1");
					u = 0;
				} else {
					x2 = c1 - 'R' + 16;
					y2 = 32 - (c2 - 'R');
					if (m < y2) {
						m = y2;
					}
					sprintf(ch + strlen(ch), ", %2i,%2i", x2, y2);
	//				printf(",%i,%i", x2, y2);
	//				if (u != 0) {
	//					printf("%i,%i -> %i,%i \n", x1, y1, x2, y2);
	//				}
					u = 1;
					x1 = x2;
					y1 = y2;
				}
				if (!((n + 2) % 16)) {
					sprintf(ch + strlen(ch), "\n		");
				}
				n += 2;
			}
			if (n > MAX) {
				fprintf(stderr, "#### too big: %i ####\n", n);
				exit(1);
			}
			int l = n / 2;
			while (n < MAX) {
	//			printf(",-1");
				sprintf(ch + strlen(ch), ", -1,-1");
				if (!((n + 2) % 16)) {
					sprintf(ch + strlen(ch), "\n		");
				}
				n += 2;
			}
			printf("		{ %i,%i // Ascii %i (%c)\n", l, m, cn, cn);
			printf("		%s\n", ch);
			printf("		},\n");
			cn++;
			if (cn > 127) {
				break;
			}
		}

		printf("	},\n");
		fclose(fd);
	}
	printf("};\n");
	return 0;
}

