
uint8_t openpilot_init(uint8_t modelid, char *port, uint32_t baud);
void openpilot_exit(uint8_t modelid);
void openpilot_update(uint8_t modelid);
uint8_t openpilot_connection_status(uint8_t modelid);
void openpilot_xml_load(xmlDocPtr doc, xmlNodePtr cur);
void openpilot_xml_save(FILE *fr);

void uavtalk_decode(uint32_t obj_id, uint8_t *buf);

void openpilot_write(uint8_t modelid, uint8_t *data, int len);
void uavtalk_send(uint8_t modelid, uint8_t *buf, uint32_t obj_id, uint8_t command, uint16_t len);
uint16_t openpilot_add_4byte(uint8_t *buf, uint16_t pos, uint32_t value);
uint16_t openpilot_add_2byte(uint8_t *buf, uint16_t pos, uint16_t value);
uint16_t openpilot_add_1byte(uint8_t *buf, uint16_t pos, uint8_t value);
void uavtalk_request(uint8_t modelid, uint32_t obj_id);
void uavtalk_send_ack(uint8_t modelid, uint32_t obj_id);


extern uint8_t openpilot_get[MODELS_MAX];
extern uint8_t openpilot_set[MODELS_MAX];
extern uint8_t openpilot_save[MODELS_MAX];
extern void openpilot_save_to_flash(uint8_t modelid);
extern void openpilot_request_SystemSettings(uint8_t modelid);

void openpilot_init_tcp(void);
void openpilot_exit_tcp(void);
int openpilot_tcp_send(uint8_t modelid, uint8_t *buf, uint16_t len);


