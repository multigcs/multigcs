
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
#include <SDL/SDL.h>

int main ( int argc, char *argv[] ) {
	int16_t values[8];
	int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	struct sockaddr_in gcAddr; 
	int i = 0;
	if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0) {
		fprintf(stderr, "Unable to initialize Joystick: %s\n", SDL_GetError());
		return -1;
	}
	fprintf(stderr, "%i joysticks found\n", SDL_NumJoysticks());
	if (SDL_NumJoysticks() <= 0) {
		return -1;
	}
	SDL_Joystick* joy1 = SDL_JoystickOpen(0);
	if (joy1 == NULL) {
		fprintf(stderr, "could not open joystick\n");
		return -1;
	}
	SDL_JoystickEventState(SDL_QUERY);
	memset(&gcAddr, 0, sizeof(gcAddr));
	gcAddr.sin_family = AF_INET;
	gcAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	gcAddr.sin_port = htons(5501);
	for (i = 0; i < 8; ++i) {
		values[i] = 1500;
	}
	sendto(sock, values, 16, 0, (struct sockaddr*)&gcAddr, sizeof(struct sockaddr_in));
	while (1) {
		SDL_JoystickUpdate();
		for (i = 0; i < SDL_JoystickNumAxes(joy1) && i < 8; ++i) {
			int16_t value = SDL_JoystickGetAxis(joy1, i);
			values[i] = value / 66 + 1500;
			fprintf(stderr, "%i ", values[i]);
		}
		fprintf(stderr, "\r");
		sendto(sock, values, 16, 0, (struct sockaddr*)&gcAddr, sizeof(struct sockaddr_in));
		SDL_Delay(20);
	}
	fprintf(stderr, "\n");
	return 0;
}

