
void serial_monitor_init (void);
void serial_monitor_exit (void);
int serial_open(char *mdevice, uint32_t baud);
int serial_open9b (char *mdevice, uint32_t baud);
int serial_check (int fd);
int serial_close(int fd);
int serial_close_by_device (char *name);
void serial_write (int fd, void *data, int len);
void serial_info_update (void);
int serial_info_get (char *device, char *deviceid);
int serial_get_device_by_id (char *deviceid, char *device);
ssize_t serial_read(int fd, void *data, size_t len);

