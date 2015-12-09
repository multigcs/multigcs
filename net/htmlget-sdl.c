
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL_net.h>

int htmlget(char *url, char *file) {
	IPaddress ip;		/* Server address */
	TCPsocket sd;		/* Socket descriptor */
	int len;
	char buffer[100000];
	char host[1024];
	char page[1024];
	sscanf(url, "http://%[a-zA-Z0-9-_.]/%s", host, page);
	if (SDLNet_Init() < 0) {
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		//		return -1;
	}
	if (SDLNet_ResolveHost(&ip, host, 80) < 0) {
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		return -1;
	}
	if (!(sd = SDLNet_TCP_Open(&ip))) {
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		return -1;
	}
	sprintf(buffer, "GET /%s HTTP/1.1\r\nHost: %s\r\nUser-Agent: wget 0.1\r\nConnection: close\r\n\r\n", page, host);
	len = strlen(buffer) + 1;
	if (SDLNet_TCP_Send(sd, (void *)buffer, len) < len) {
		fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
		return -1;
	}
	char *cl;
	char *cl2;
	int maxlen = 0;
	len = SDLNet_TCP_Recv(sd, buffer, 100000 - 1);
	buffer[len] = 0;
	if ((cl = strstr(buffer, "Content-Length: ")) != NULL) {
		if ((cl2 = strstr(buffer, "\r\n\r\n")) != NULL) {
			len -= (cl2 + 4) - buffer;
			maxlen = atoi(cl + 16);
			FILE *fd = NULL;
			fd = fopen(file, "wb");
			if (fd == NULL) {
				printf("Error open file to write: %s\n", file);
				return -1;
			}
			fwrite(cl2 + 4, 1, len, fd);
			while (len < maxlen) {
				int gmlen = maxlen - len;
				if (gmlen > 1024) {
					gmlen = 1024;
				}
				int glen = SDLNet_TCP_Recv(sd, buffer, gmlen);
				if (glen > 0) {
					len += glen;
					fwrite(buffer, 1, glen, fd);
				}
			}
			fclose(fd);
		}
	}
	SDLNet_TCP_Close(sd);
	SDLNet_Quit();
	return 0;
}

/*
    void main () {
	htmlget("http://maps.google.com/mapfiles/kml/pal3/icon21.png", "/tmp/test.png");
    }
*/
