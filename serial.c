
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>

struct termios oldtio, newtio;

int serial_close (int fd) {
	if (fd >= 0) {
		close(fd);
		fd = -1;
	}
	return 0;
}

int serial_open (char *mdevice, uint32_t baud) {
	int fd = -1;
	int baudr = 9600;
	switch(baud) {
		case      50 : baudr = B50;
                   break;
		case      75 : baudr = B75;
                   break;
		case     110 : baudr = B110;
                   break;
		case     134 : baudr = B134;
                   break;
		case     150 : baudr = B150;
                   break;
		case     200 : baudr = B200;
                   break;
		case     300 : baudr = B300;
                   break;
		case     600 : baudr = B600;
                   break;
		case    1200 : baudr = B1200;
                   break;
		case    1800 : baudr = B1800;
                   break;
		case    2400 : baudr = B2400;
                   break;
		case    4800 : baudr = B4800;
                   break;
		case    9600 : baudr = B9600;
                   break;
		case   19200 : baudr = B19200;
                   break;
		case   38400 : baudr = B38400;
                   break;
		case   57600 : baudr = B57600;
                   break;
		case  115200 : baudr = B115200;
                   break;
#ifndef OSX
		case  230400 : baudr = B230400;
                   break;
		case  460800 : baudr = B460800;
                   break;
		case  500000 : baudr = B500000;
                   break;
		case  576000 : baudr = B576000;
                   break;
		case  921600 : baudr = B921600;
                   break;
		case 1000000 : baudr = B1000000;
                   break;
#endif
		default      : printf("invalid baudrate\n");
                   return(1);
                   break;
	}
	printf("	Try to open Serial-Port: %s (%i)...", mdevice, baud);
	if ((fd = open(mdevice, O_RDWR | O_NOCTTY )) >= 0) {

#ifdef OSX
		struct termios theTermios;
		memset(&theTermios, 0, sizeof(struct termios));
		cfmakeraw(&theTermios);
		cfsetspeed(&theTermios, 115200);
		theTermios.c_cflag = CREAD | CLOCAL;     // turn on READ
		theTermios.c_cflag |= CS8;
		theTermios.c_cc[VMIN] = 0;
		theTermios.c_cc[VTIME] = 10;     // 1 sec timeout
		ioctl(fd, TIOCSETA, &theTermios);
#else
		tcgetattr(fd, &newtio);
		memset(&newtio, 0, sizeof(newtio));  /* clear the new struct */
		newtio.c_cflag = baudr | CS8 | CLOCAL | CREAD;
		newtio.c_iflag = IGNPAR;
		newtio.c_oflag = 0;
		newtio.c_lflag = 0;
		newtio.c_cc[VMIN] = 0;      /* block untill n bytes are received */
		newtio.c_cc[VTIME] = 0;     /* block untill a timer expires (n * 100 mSec.) */
		tcsetattr(fd, TCSANOW, &newtio);
endif
		printf("..Ok\n");
		return fd;
	}
	printf("..Failed\n");
	return -1;
}

int serial_open9b (char *mdevice, uint32_t baud) {
	int fd = -1;
	int baudr = 9600;
	switch(baud) {
		case      50 : baudr = B50;
                   break;
		case      75 : baudr = B75;
                   break;
		case     110 : baudr = B110;
                   break;
		case     134 : baudr = B134;
                   break;
		case     150 : baudr = B150;
                   break;
		case     200 : baudr = B200;
                   break;
		case     300 : baudr = B300;
                   break;
		case     600 : baudr = B600;
                   break;
		case    1200 : baudr = B1200;
                   break;
		case    1800 : baudr = B1800;
                   break;
		case    2400 : baudr = B2400;
                   break;
		case    4800 : baudr = B4800;
                   break;
		case    9600 : baudr = B9600;
                   break;
		case   19200 : baudr = B19200;
                   break;
		case   38400 : baudr = B38400;
                   break;
		case   57600 : baudr = B57600;
                   break;
		case  115200 : baudr = B115200;
                   break;
#ifndef OSX
		case  230400 : baudr = B230400;
                   break;
		case  460800 : baudr = B460800;
                   break;
		case  500000 : baudr = B500000;
                   break;
		case  576000 : baudr = B576000;
                   break;
		case  921600 : baudr = B921600;
                   break;
		case 1000000 : baudr = B1000000;
                   break;
#endif
		default      : printf("invalid baudrate\n");
                   return(1);
                   break;
	}
	printf("	Try to open Serial-Port: %s (%i)...", mdevice, baud);
	if ((fd = open(mdevice, O_RDWR | O_NOCTTY )) >= 0) {
		tcgetattr(fd, &newtio);
		memset(&newtio, 0, sizeof(newtio));  /* clear the new struct */
		newtio.c_cflag = baudr | CS8 | CLOCAL | CREAD;
		newtio.c_iflag = IGNPAR;
		newtio.c_oflag = 0;
		newtio.c_lflag = 0;
		newtio.c_cc[VMIN] = 0;      /* block untill n bytes are received */
		newtio.c_cc[VTIME] = 0;     /* block untill a timer expires (n * 100 mSec.) */
		tcsetattr(fd, TCSANOW, &newtio);
		printf("..Ok\n");
		return fd;
	}
	printf("..Failed\n");
	return -1;
}

