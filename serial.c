
#include <all.h>

#ifdef ANDROID
extern ssize_t bt_read(int fd, void *data, size_t len);
#endif

#ifndef WINDOWS
struct termios oldtio, newtio;
#else
HANDLE hSerial[10] = {INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE};
#endif

void serial_write (int fd, void *data, int len) {
#ifndef WINDOWS
#ifdef ANDROID
	int n = 0;
	for (n = 0; n < len; n++) {
		uint8_t *udata = (uint8_t *)data;
		Android_JNI_SendSerial(udata[n]);
	}
#else
	write(fd, data, len);
#endif
#else
	DWORD dwBytesWritten = 0;
	WriteFile(hSerial[fd], data, len, &dwBytesWritten, NULL);
	//SDL_Log("## serial set: %i/%i \n", dwBytesWritten, len);
#endif
}

ssize_t serial_read(int fd, void *data, size_t len) {
#ifndef WINDOWS
#ifdef ANDROID
	return bt_read(fd, data, len);
#else
	return read(fd, data, len);
#endif
#else
	DWORD dwBytesRead = 0;
	ReadFile(hSerial[fd], data, len, &dwBytesRead, 0);
	//SDL_Log("## serial get: %i/%i \n", dwBytesRead, len);
	return dwBytesRead;
#endif
}

int serial_close (int fd) {
#ifndef WINDOWS
	if (fd >= 0) {
		close(fd);
		fd = -1;
	}
#else
	if (fd >= 0) {
		CloseHandle(hSerial[fd]);
		hSerial[fd] = INVALID_HANDLE_VALUE;
		fd = -1;
	}
#endif
	return 0;
}

int serial_open (char *mdevice, uint32_t baud) {
	int fd = -1;
#ifdef ANDROID
	return 1;
#endif
#ifndef WINDOWS
#ifndef OSX
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
		default      : SDL_Log("invalid baudrate\n");
                   return(1);
                   break;
	}
	SDL_Log("	Try to open Serial-Port: %s (%i)...", mdevice, baud);
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
#else
	SDL_Log("	Try to open Serial-Port: %s (%i)...", mdevice, baud);
	if ((fd = open(mdevice, O_RDWR | O_NOCTTY | O_NONBLOCK )) >= 0) {
		struct termios theTermios;
		memset(&theTermios, 0, sizeof(struct termios));
		cfmakeraw(&theTermios);
		cfsetspeed(&theTermios, baud);
		theTermios.c_cflag = CS8 | CREAD | CLOCAL;
		theTermios.c_cc[VMIN] = 0;
		theTermios.c_cc[VTIME] = 0;
		ioctl(fd, TIOCEXCL);
		ioctl(fd, TIOCSETA, &theTermios);
#endif
		SDL_Log("..Ok\n");
		return fd;
	}
	SDL_Log("..Failed\n");

#else

	SDL_Log("	Try to open Serial-Port: %s (%i)...", mdevice, baud);

	DCB dcbSerialParams = {0};
	COMMTIMEOUTS timeouts = {0};
	int n = 0;
	int free_port = -1;
	for (n = 0; n < 10; n++) {
		if (hSerial[n] == INVALID_HANDLE_VALUE) {
			free_port = n;
		}
	}
	if (free_port == -1) {
		SDL_Log("..Failed (no usable ports found)\n");
		return -1;
	}

	hSerial[free_port] = CreateFile(mdevice, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hSerial[free_port] == INVALID_HANDLE_VALUE) {
		SDL_Log("..Failed (INVALID_HANDLE_VALUE: %i)\n", GetLastError());
		return -1;
	}
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (GetCommState(hSerial[free_port], &dcbSerialParams) == 0) {
		SDL_Log("..Failed (Error getting device state)\n");
		CloseHandle(hSerial[free_port]);
		hSerial[free_port] = INVALID_HANDLE_VALUE;
		return -1;
	}
	switch(baud) {
		case    1200 : dcbSerialParams.BaudRate = CBR_1200;
                   break;
		case    2400 : dcbSerialParams.BaudRate = CBR_2400;
                   break;
		case    4800 : dcbSerialParams.BaudRate = CBR_4800;
                   break;
		case    9600 : dcbSerialParams.BaudRate = CBR_9600;
                   break;
		case   19200 : dcbSerialParams.BaudRate = CBR_19200;
                   break;
		case   38400 : dcbSerialParams.BaudRate = CBR_38400;
                   break;
		case   57600 : dcbSerialParams.BaudRate = CBR_57600;
                   break;
		case  115200 : dcbSerialParams.BaudRate = CBR_115200;
                   break;
		default      : SDL_Log("invalid baudrate\n");
                   return(1);
                   break;
	}
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	dcbSerialParams.fOutxCtsFlow = FALSE;
	dcbSerialParams.fOutxDsrFlow = FALSE;
	dcbSerialParams.fDtrControl = DTR_CONTROL_DISABLE;
	dcbSerialParams.fRtsControl = RTS_CONTROL_DISABLE;
	dcbSerialParams.fDsrSensitivity = FALSE;
	dcbSerialParams.fTXContinueOnXoff = FALSE;
	dcbSerialParams.fOutX = FALSE;
	dcbSerialParams.fInX = FALSE;
	dcbSerialParams.fErrorChar = FALSE;
	dcbSerialParams.fNull = FALSE;
	dcbSerialParams.fAbortOnError = FALSE;

	if(SetCommState(hSerial[free_port], &dcbSerialParams) == 0) {
		SDL_Log("..Failed (Error setting device parameters\n");
		CloseHandle(hSerial[free_port]);
		hSerial[free_port] = INVALID_HANDLE_VALUE;
		return -1;
	}

	timeouts.ReadIntervalTimeout = 0;
	timeouts.ReadTotalTimeoutConstant = 1;
	timeouts.ReadTotalTimeoutMultiplier = 0;

	timeouts.WriteTotalTimeoutConstant = 1;
	timeouts.WriteTotalTimeoutMultiplier = 1;
	if(SetCommTimeouts(hSerial[free_port], &timeouts) == 0) {
		SDL_Log("..Failed (Error setting timeouts)\n");
		CloseHandle(hSerial[free_port]);
		hSerial[free_port] = INVALID_HANDLE_VALUE;
		return -1;
	}
 	SDL_Log("..Ok\n");
	return free_port;
#endif
	return -1;
}

int serial_open9b (char *mdevice, uint32_t baud) {
#ifndef WINDOWS
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
		default      : SDL_Log("invalid baudrate\n");
                   return(1);
                   break;
	}
	SDL_Log("	Try to open Serial-Port: %s (%i)...", mdevice, baud);
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
		SDL_Log("..Ok\n");
		return fd;
	}
#endif
	SDL_Log("..Failed\n");
	return -1;
}

