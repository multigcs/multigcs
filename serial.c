
#include <all.h>

#ifndef WINDOWS
#ifndef ANDROID
#include <libudev.h>
#endif
#endif


typedef struct {
	char name[1024];
	char device[1024];
	int fd;
} SerialLockFile;

SerialLockFile locks[100];


typedef struct {
	char device[1024];
	char deviceid[1024];
} SerialInfo;

SerialInfo info[100];


#ifdef ANDROID
extern ssize_t bt_read(int fd, void *data, size_t len);
#endif

#ifndef WINDOWS
struct termios oldtio, newtio;
#else
HANDLE hSerial[10] = {INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE};
#endif

SDL_Thread *thread_sermon = NULL;
uint8_t thread_sermon_running = 0;

int serial_info_get (char *device, char *deviceid) {
	int n = 0;
#ifndef WINDOWS
	if (device[0] != '/') {
		return -1;
	}
#endif
	deviceid[0] = 0;
	for (n = 0; n < 100; n++) {
		if (strcmp(info[n].device, device) == 0) {
			strcpy(deviceid, info[n].deviceid);
			return 0;
		}
	}
	return -1;
}

int serial_get_device_by_id (char *deviceid, char *device) {
	int n = 0;
	if (deviceid[0] == 0) {
		return -1;
	}
	device[0] = 0;
	for (n = 0; n < 100; n++) {
		if (strcmp(info[n].deviceid, deviceid) == 0) {
			strcpy(device, info[n].device);
			return 0;
		}
	}
	return -1;
}

void serial_info_update (void) {
#ifndef WINDOWS
#ifndef ANDROID
	struct udev *udev;
	struct udev_enumerate *enumerate;
	struct udev_list_entry *devices, *dev_list_entry;
	struct udev_device *dev;
	struct udev_device *dev2;
   	struct udev_monitor *mon;
	char tmp_str[1024];
	int n = 0;
	int n2 = 0;
	int fd;
	for (n = 0; n < 100; n++) {
		info[n].device[0] = 0;
		info[n].deviceid[0] = 0;
	}
	n = 0;
	udev = udev_new();
	if (!udev) {
		printf("Can't create udev\n");
		return;
	}
	mon = udev_monitor_new_from_netlink(udev, "udev");
	udev_monitor_filter_add_match_subsystem_devtype(mon, "tty", NULL);
	udev_monitor_enable_receiving(mon);
	fd = udev_monitor_get_fd(mon);
	enumerate = udev_enumerate_new(udev);
	udev_enumerate_add_match_subsystem(enumerate, "tty");
	udev_enumerate_scan_devices(enumerate);
	devices = udev_enumerate_get_list_entry(enumerate);
	udev_list_entry_foreach(dev_list_entry, devices) {
		const char *path;
		path = udev_list_entry_get_name(dev_list_entry);
		dev = udev_device_new_from_syspath(udev, path);
		dev2 = udev_device_get_parent_with_subsystem_devtype(dev, "usb", "usb_device");
		if (dev2) {
			strcpy(info[n].device, udev_device_get_devnode(dev));
			sprintf(tmp_str, "%s", udev_device_get_sysattr_value(dev2,"manufacturer"));
			strcat(info[n].deviceid, tmp_str);
			sprintf(tmp_str, "%s", udev_device_get_sysattr_value(dev2,"product"));
			strcat(info[n].deviceid, tmp_str);
			if (udev_device_get_sysattr_value(dev2,"serial") != NULL) {
				sprintf(tmp_str, "%s", udev_device_get_sysattr_value(dev2,"serial"));
				strcat(info[n].deviceid, tmp_str);
			}
			for (n2 = 0; n2 < strlen(info[n].deviceid); n2++) {
				if (info[n].deviceid[n2] == ' ') {
					info[n].deviceid[n2] = '_';
				}
			}
			SDL_Log("sermon: %s: %s\n", info[n].device, info[n].deviceid);
			udev_device_unref(dev2);
			n++;
		}
	}
	udev_enumerate_unref(enumerate);
	udev_device_unref(dev);
	udev_unref(udev);
#endif
#endif
}

int serial_monitor (void *data) {
#ifndef WINDOWS
#ifndef ANDROID
	char tmp_str[1024];
	struct udev *udev;
	struct udev_device *dev;
   	struct udev_monitor *mon;
	int n = 0;
	int fd;
	udev = udev_new();
	if (!udev) {
		printf("Can't create udev\n");
		return 1;
	}
	mon = udev_monitor_new_from_netlink(udev, "udev");
	udev_monitor_filter_add_match_subsystem_devtype(mon, "tty", NULL);
	udev_monitor_enable_receiving(mon);
	fd = udev_monitor_get_fd(mon);
	while (thread_sermon_running == 1) {
		fd_set fds;
		struct timeval tv;
		int ret;
		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		ret = select(fd+1, &fds, NULL, NULL, &tv);
		if (ret > 0 && FD_ISSET(fd, &fds)) {
			dev = udev_monitor_receive_device(mon);
			if (dev) {
				serial_info_update();
				printf("serialmon: Device changed\n");
				printf("   Node: %s\n", udev_device_get_devnode(dev));
				printf("   Subsystem: %s\n", udev_device_get_subsystem(dev));
				printf("   Action: %s\n", udev_device_get_action(dev));
				if (strcmp((char *)udev_device_get_action(dev), "remove") == 0) {
					serial_close_by_device((char *)udev_device_get_devnode(dev));
				} else if (strcmp((char *)udev_device_get_action(dev), "add") == 0) {
					for (n = 0; n < MODELS_MAX; n++) {
						if (ModelData[n].use_deviceid == 1) {
							serial_info_get((char *)udev_device_get_devnode(dev), tmp_str);
							if (strcmp(ModelData[n].deviceid, tmp_str) == 0) {
									serial_get_device_by_id(ModelData[n].deviceid, ModelData[n].telemetry_port);
									reset_telemetry(n);
									break;
							}
						} else {
							if (strcmp(ModelData[n].telemetry_port, (char *)udev_device_get_devnode(dev)) == 0) {
								reset_telemetry(n);
								break;
							}
						}
					}
				}
				udev_device_unref(dev);
			}					
		}
		usleep(250*1000);
		fflush(stdout);
	}
	udev_unref(udev);
#endif
#endif
	return 0;
}

void serial_monitor_init (void) {
	serial_info_update();
	SDL_Log("sermon: init thread\n");
	thread_sermon_running = 1;
#ifdef SDL2
	thread_sermon = SDL_CreateThread(serial_monitor, NULL, NULL);
#else
	thread_sermon = SDL_CreateThread(serial_monitor, NULL);
#endif
	if (thread_sermon == NULL) {
		fprintf(stderr, "sermon: Thread konnte nicht gestartet werden: %s\n", SDL_GetError());
	}
}

void serial_monitor_exit (void) {
	thread_sermon_running = 0;
	SDL_Log("sermon: wait thread\n");
	SDL_WaitThread(thread_sermon, NULL);
	thread_sermon = NULL;
}


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

int serial_check (int fd) {
#ifndef WINDOWS
	int n = 0;
	for (n = 0; n < 100; n++) {
		if (locks[n].name[0] != 0 && locks[n].fd == fd) {
			return fd;
		}
	}
	return -1;
#else
	return fd;
#endif
}

int serial_close_by_device (char *device) {
#ifndef WINDOWS
	int n = 0;
	for (n = 0; n < 100; n++) {
		if (locks[n].name[0] != 0 && strcmp(locks[n].device, device) == 0) {
			SDL_Log("closing serial fd %s (%i)\n", device, locks[n].fd);
			close(locks[n].fd);
			SDL_Log("	removing Lockfile: %s\n", locks[n].name);
			remove(locks[n].name);
			locks[n].name[0] = 0;
			locks[n].device[0] = 0;
			locks[n].fd = -1;
		}
	}
#endif
	return 0;
}

int serial_close (int fd) {
#ifndef WINDOWS
	SDL_Log("closing serial fd (%i)\n", fd);
	if (fd >= 0) {
		int n = 0;
		for (n = 0; n < 100; n++) {
			if (locks[n].name[0] != 0 && locks[n].fd == fd) {
				SDL_Log("	removing Lockfile: %s\n", locks[n].name);
				remove(locks[n].name);
				locks[n].device[0] = 0;
				locks[n].name[0] = 0;
				locks[n].fd = -1;
			}
		}
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
#ifndef WINDOWS
	if (mdevice[0] != '/') {
		return -1;
	}
#endif
#ifdef ANDROID
	return 1;
#endif
#ifndef WINDOWS
	char mdevice_name[1024];
	FILE *lock_fd = NULL;
	int fd = -1;
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
	sprintf(mdevice_name, "/var/lock/LCK..%s", basename(mdevice));
	if (file_exists(mdevice_name) != 0) {
		SDL_Log("..Failed (Lockfile allready exist: %s)\n", mdevice_name);
		return -1;
	}
	if ((lock_fd = fopen(mdevice_name, "w")) == NULL) {
		SDL_Log("..Failed (can not create Lockfile: %s)\n", mdevice_name);
		return -1;
	} else {
		fprintf(lock_fd, "%i\n", getpid());
		fclose(lock_fd);
	}
	if ((fd = open(mdevice, O_RDWR | O_NOCTTY )) >= 0) {
		int n = 0;
		for (n = 0; n < 100; n++) {
			if (locks[n].name[0] == 0) {
				strcpy(locks[n].name, mdevice_name);
				strcpy(locks[n].device, mdevice);
				locks[n].fd = fd;
				break;
			}
		}
		tcgetattr(fd, &newtio);
		memset(&newtio, 0, sizeof(newtio));  /* clear the new struct */
		newtio.c_cflag = baudr | CS8 | CLOCAL | CREAD;
		newtio.c_iflag = IGNPAR;
		newtio.c_oflag = 0;
		newtio.c_lflag = 0;
		newtio.c_cc[VMIN] = 0;      /* block untill n bytes are received */
		newtio.c_cc[VTIME] = 0;     /* block untill a timer expires (n * 100 mSec.) */
		tcsetattr(fd, TCSANOW, &newtio);
		SDL_Log("..Ok (%i / %s)\n", fd, mdevice_name);
		return fd;
	}
	remove(mdevice_name);
	SDL_Log("..Failed\n");
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
		SDL_Log("..Ok\n");
		return fd;
	}
	SDL_Log("..Failed\n");
#endif

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
		SDL_Log("..Failed (INVALID_HANDLE_VALUE: %i)\n", (int)GetLastError());
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

