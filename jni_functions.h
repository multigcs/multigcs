
extern SDL_bool Android_JNI_GetAccelerometerValues(float values[3]);
extern void jni_gpsGetPosition(float *lat, float *lon, float *alt, float *speed);
extern void jni_attitudeGetPosition(float *pitch, float *roll, float *yaw);
extern void Android_JNI_SendSerial(uint8_t c);
extern void Android_JNI_ConnectSerial(char *name);
extern int Android_JNI_ReadSerial(uint8_t *data, int len);
extern void Android_JNI_SayText(const char *text);
