
extern uint8_t clientmode;
extern char clientmode_server[1024];
extern uint16_t clientmode_port;

void webclient_update(char *server, uint16_t port);
void webclient_send_value(char *server, uint16_t port, char *name, float value, int type);
