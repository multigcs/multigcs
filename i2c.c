
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <i2c.h>

static uint8_t i2c_startup = 0;
static uint16_t i2c_timeout_cnt = 0;
int i2c_fd = -1;
uint8_t i2c_address = 2;
uint8_t i2c_address_mpu6050 = 0x68;
uint8_t i2c_address_hmc5843 = 0x1e;
char *i2c_fileName = "/dev/i2c-1";

int i2c_diff1 = 0;
int i2c_button1 = 0;
int i2c_diff2 = 0;
int i2c_button2 = 0;
int i2c_button3 = 0;
int i2c_adc1 = 0;
int i2c_adc2 = 0;
int i2c_adc3 = 0;
int i2c_adc4 = 0;

float i2c_Axz = 0.0;
float i2c_Ayz = 0.0;

float i2c_mg_Axz = 0.0;
float i2c_mg_Ayz = 0.0;
float i2c_mg_Az = 0.0;

int i2c_read (void) {
	unsigned char buf[100];
	if (i2c_timeout_cnt > 200) {
		return 1;
	}
	if (i2c_startup == 0) {
		if (i2c_init() == 1) {
			return 1;
		}
	}
/*
	if (ioctl(i2c_fd, I2C_SLAVE, i2c_address) < 0) {
		printf("ERROR: Can not get bus access to talk to slave\n");
		return 1;
	}
*/
	int size = 2;
/*	strcpy(buf, "RA");
	if ((write(i2c_fd, buf, size)) != size) {
//		printf("ERROR: Can not write to i2c slave\n");
		return 1;
	}
	usleep(500);
	char cc = 0;
	buf[0] = 0;
	size = 20;
	if (read(i2c_fd, buf, size) != size) {
//		printf("ERROR: Can not read from slave\n");
		return 1;
	} else {
		buf[size] = 0;
//		printf("%s\n", buf);
		sscanf(buf, "%c %i %i %i %i", &cc, &i2c_adc1, &i2c_adc2, &i2c_adc3, &i2c_adc4);
	}
	usleep(500);

	size = 2;
	strcpy(buf, "RD");
	if ((write(i2c_fd, buf, size)) != size) {
		printf("ERROR: Can not write to i2c slave\n");
		return 1;
	}
	usleep(500);
*/
/*
	buf[0] = 0;
	size = 14;
	if (read(i2c_fd, buf, size) != size) {
//		printf("ERROR: Can not read from slave\n");
		return 1;
	} else {
		buf[size] = 0;
//printf("%s\n", buf);
		sscanf(buf, "%i %i %i %i %i", &i2c_diff1, &i2c_button1, &i2c_diff2, &i2c_button2, &i2c_button3);
	}
*/

	if (ioctl(i2c_fd, I2C_SLAVE, i2c_address_mpu6050) < 0) {
		printf("ERROR: Can not get bus access to talk to slave\n");
		return 1;
	}

	// init MPU6050
	buf[0] = 0x6B;
	buf[1] = 0;
	if ((write(i2c_fd, buf, 2)) != 2) {								// Send the register to read from
		printf("Error writing to i2c slave\n");
		return 1;
	}
//	usleep(50000);												// This sleep waits for the ping to come back

	// enable bypas for I2C-Aux
	buf[0] = 0x6A;
	buf[1] = 0;
	if ((write(i2c_fd, buf, 2)) != 2) {								// Send the register to read from
		printf("Error writing to i2c slave\n");
		return 1;
	}
//	usleep(50000);												// This sleep waits for the ping to come back
	buf[0] = 0x37;
	buf[1] = 0x02;
	if ((write(i2c_fd, buf, 2)) != 2) {								// Send the register to read from
		printf("Error writing to i2c slave\n");
		return 1;
	}
//	usleep(50000);												// This sleep waits for the ping to come back


	// read X,Y,Z
	buf[0] = 0x3B;
	if ((write(i2c_fd, buf, 1)) != 1) {								// Send the register to read from
		printf("Error writing to i2c slave\n");
		return 1;
	}
//	usleep(50000);												// This sleep waits for the ping to come back
	buf[0] = 0;
	size = 6;

	float Axz = 0.0;
	float Ayz = 0.0;

	if (read(i2c_fd, buf, size) != size) {
		printf("ERROR: Can not read from slave\n");
		return 1;
	} else {
		int16_t tmp = (buf[0] <<8) + buf[1];
		float acX = tmp;
		tmp = (buf[2] <<8) + buf[3];
		float acY = tmp;
		tmp = (buf[4] <<8) + buf[5];
		float acZ = tmp;
		Axz = atan2(acX, acZ);
		Ayz = atan2(acY, acZ);

		i2c_Axz = Axz * 180.0 / PI;;
		i2c_Ayz = Ayz * 180.0 / PI;;

//		printf("%0.1f, %0.1f\n", i2c_Axz, i2c_Ayz);

	}







/*

	if (ioctl(i2c_fd, I2C_SLAVE, i2c_address_hmc5843) < 0) {
		printf("ERROR: Can not get bus access to talk to slave (hmc5843)\n");
		return 1;
	}

	// init HMC5843
	buf[0] = 0x02;
	buf[1] = 0x00;
	if ((write(i2c_fd, buf, 2)) != 2) {								// Send the register to read from
		printf("Error writing to i2c slave\n");
		return 1;
	}
//	usleep(50000);												// This sleep waits for the ping to come back


	buf[0] = 0x03;
	if ((write(i2c_fd, buf, 1)) != 1) {								// Send the register to read from
		printf("Error writing to i2c slave\n");
		return 1;
	}
//	usleep(50000);												// This sleep waits for the ping to come back


	// read X,Y,Z
	buf[0] = 0;
	size = 6;
	if (read(i2c_fd, buf, size) != size) {
		printf("ERROR: Can not read from slave\n");
		return 1;
	} else {
		int16_t tmp = (buf[0] <<8) + buf[1];
		float mgX = tmp;
		tmp = (buf[4] <<8) + buf[5];
		float mgY = tmp;
		tmp = (buf[2] <<8) + buf[3];
		float mgZ = tmp;


		float heading1 = (atan2(mgY, mgX) + PI) * 180.0 / PI;


		float norm = sqrt( sq(mgX) + sq(mgY) + sq(mgZ));

		mgX /= norm;
		mgY /= norm;
		mgZ /= norm;

		float mYaw = atan2( (mgY * cos(Axz) + mgZ * sin(Axz) ) , mgX * cos(Ayz) + mgZ * sin(Ayz) * sin(Axz) + mgZ * sin(Ayz) * cos(Axz)) * 180 / PI;
		float mYawU = atan2(mgY, mgX) * 180 / PI;


		printf("%0.1f, %0.1f, %0.1f, %0.1f, %0.1f, %0.1f\n", mgX, mgY, mgZ, heading1, mYaw, mYawU);

	}

*/


//	usleep(500);
	return 0;
}

int i2c_init (void) {
	if (i2c_timeout_cnt < 200) {
		i2c_timeout_cnt++;
//		printf("I2C-Init (%i/200)..\n", i2c_timeout_cnt);
		if ((i2c_fd = open(i2c_fileName, O_RDWR)) < 0) {
//			printf("Failed to open i2c port\n");
			return 1;
		}
		i2c_startup = 1;
	} else if (i2c_timeout_cnt == 200) {
		i2c_timeout_cnt++;
		printf("Disable I2C!\n");
	}
	return 0;
}

/*
int main(int argc, char **argv) {
	int n = 0;
	for (n = 0; n < 1000; n++) {
		i2c_read();
		printf("%i, %i\n", i2c_diff1, i2c_diff2);
	}
	return 0;
}
*/

