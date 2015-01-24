
uint8_t openpilot_init (char *port, uint32_t baud);
void openpilot_exit (void);
void openpilot_update (void);
uint8_t openpilot_connection_status (void);
void openpilot_xml_load (xmlDocPtr doc, xmlNodePtr cur);
void openpilot_xml_save (FILE *fr);

void uavtalk_decode (uint32_t obj_id, uint8_t *buf);

void openpilot_write (uint8_t *data, int len);
void uavtalk_send (uint8_t *buf, uint32_t obj_id, uint8_t command, uint16_t len);
uint16_t openpilot_add_4byte (uint8_t *buf, uint16_t pos, uint32_t value);
uint16_t openpilot_add_2byte (uint8_t *buf, uint16_t pos, uint16_t value);
uint16_t openpilot_add_1byte (uint8_t *buf, uint16_t pos, uint8_t value);
void uavtalk_request (uint32_t obj_id);
void uavtalk_send_ack (uint32_t obj_id);


extern void openpilot_defaults_StabilizationSettings (UAVT_StabilizationSettingsData *data);
extern uint8_t openpilot_get;
extern uint8_t openpilot_set;
extern uint8_t openpilot_save;
extern void openpilot_save_to_flash (void);
extern void openpilot_defaults_StabilizationSettings (UAVT_StabilizationSettingsData *data);
extern void openpilot_defaults_HwSettings (UAVT_HwSettingsData *data);
extern void openpilot_defaults_SystemSettings (UAVT_SystemSettingsData *data);
extern void openpilot_request_SystemSettings (void);

extern UAVT_StabilizationSettingsData OpenpilotStabilizationSettings;
extern UAVT_HwSettingsData OpenpilotHwSettings;
extern UAVT_SystemSettingsData OpenpilotSystemSettings;




