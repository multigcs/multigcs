
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <time.h>
#include <arpa/inet.h>
#include <stdio.h>

int main ( int argc, char *argv[] ) {
	int16_t values[8];
	int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	struct sockaddr_in gcAddr; 
	int i = 0;
	memset(&gcAddr, 0, sizeof(gcAddr));
	gcAddr.sin_family = AF_INET;
	gcAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	gcAddr.sin_port = htons(5501);
	for (i = 0; i < 8; ++i) {
		values[i] = 1500;
	}
	sendto(sock, values, 16, 0, (struct sockaddr*)&gcAddr, sizeof(struct sockaddr_in));
	return 0;
}

