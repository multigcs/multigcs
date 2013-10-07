

int serial_open(char *mdevice, uint32_t baud);
int serial_open9b (char *mdevice, uint32_t baud);
int serial_close(int fd);
void serial_write (int fd, uint8_t *data, int len);
ssize_t serial_read(int fd, void *data, size_t len);

