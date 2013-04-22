

#define sq(a) (a * a)
#define PI 3.14159265

extern int i2c_fd;
extern uint8_t i2c_address;
extern uint8_t i2c_address_mpu6050;
extern uint8_t i2c_address_hmc5843;
extern char *i2c_fileName;

extern int i2c_diff1;
extern int i2c_button1;
extern int i2c_diff2;
extern int i2c_button2;
extern int i2c_button3;
extern int i2c_adc1;
extern int i2c_adc2;
extern int i2c_adc3;
extern int i2c_adc4;
extern float i2c_Axz;
extern float i2c_Ayz;
extern float i2c_mg_Axz;
extern float i2c_mg_Ayz;
extern float i2c_mg_Az;

int i2c_read (void);
int i2c_init (void);

