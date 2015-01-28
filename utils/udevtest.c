
#include <libudev.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>

int main (void) {
	struct udev *udev;
	struct udev_enumerate *enumerate;
	struct udev_list_entry *devices, *dev_list_entry;
	struct udev_device *dev;
	struct udev_device *dev2;
   	struct udev_monitor *mon;
	int fd;
	udev = udev_new();
	if (!udev) {
		printf("Can't create udev\n");
		exit(1);
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
			printf("Device Node Path: %s\n", udev_device_get_devnode(dev));
			printf("  VID/PID: %s %s\n", udev_device_get_sysattr_value(dev2,"idVendor"), udev_device_get_sysattr_value(dev, "idProduct"));
			printf("  %s\n  %s\n", udev_device_get_sysattr_value(dev2,"manufacturer"), udev_device_get_sysattr_value(dev2,"product"));
			printf("  serial: %s\n", udev_device_get_sysattr_value(dev2, "serial"));
			udev_device_unref(dev2);
		}
	}
	udev_enumerate_unref(enumerate);
	

	while (1) {
		fd_set fds;
		struct timeval tv;
		int ret;
		
		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		
		ret = select(fd+1, &fds, NULL, NULL, &tv);
		
		/* Check if our file descriptor has received data. */
		if (ret > 0 && FD_ISSET(fd, &fds)) {
			printf("\nselect() says there should be data\n");
			
			/* Make the call to receive the device.
			   select() ensured that this will not block. */
			dev = udev_monitor_receive_device(mon);
			if (dev) {
				printf("Got Device\n");
				printf("   Node: %s\n", udev_device_get_devnode(dev));
				printf("   Subsystem: %s\n", udev_device_get_subsystem(dev));
				printf("   Devtype: %s\n", udev_device_get_devtype(dev));

				printf("   Action: %s\n", udev_device_get_action(dev));
				udev_device_unref(dev);
			}
			else {
				printf("No Device from receive_device(). An error occured.\n");
			}					
		}
		usleep(250*1000);
		printf(".");
		fflush(stdout);
	}


	udev_unref(udev);

	return 0;       
}

