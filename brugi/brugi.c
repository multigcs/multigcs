
#include <all.h>

int brugi_serial_fd = -1;
uint8_t brugi_serial_buf[255];
static uint32_t last_connection = 1;
static uint8_t info_num = 0;
BrugiSetup brugi_setup;


void brugi_send_cmd (char *cmd) {
	if (brugi_serial_fd >= 0) {
		serial_write(brugi_serial_fd, cmd, strlen(cmd));
	}
}

void brugi_set_value (char *var, float val) {
	char cmd[100];
	sprintf(cmd, "par %s %f\n", var, val);
	printf("brugi: %s", cmd);
	brugi_send_cmd(cmd);
}

uint8_t brugi_connection_status (void) {
	if (brugi_serial_fd == -1) {
		return 0;
	}
	return last_connection;
}

void brugi_init (char *port, uint32_t baud) {
	brugi_setup.vers.scale = 100.0;
	brugi_setup.vers.offset = 0;

	brugi_setup.gyroPitchKp.min = 0;
	brugi_setup.gyroPitchKp.max = 100;
	brugi_setup.gyroPitchKp.scale = 1000.0;
	brugi_setup.gyroPitchKp.offset = 0;
	brugi_setup.gyroPitchKp.step = 0.001;
	brugi_setup.gyroPitchKp.type = 1;
	brugi_setup.gyroPitchKi.min = 0;
	brugi_setup.gyroPitchKi.max = 100;
	brugi_setup.gyroPitchKi.scale = 1000.0;
	brugi_setup.gyroPitchKi.offset = 0;
	brugi_setup.gyroPitchKi.step = 0.001;
	brugi_setup.gyroPitchKi.type = 1;
	brugi_setup.gyroPitchKd.min = 0;
	brugi_setup.gyroPitchKd.max = 100;
	brugi_setup.gyroPitchKd.scale = 1000.0;
	brugi_setup.gyroPitchKd.offset = 0;
	brugi_setup.gyroPitchKd.step = 0.001;
	brugi_setup.gyroPitchKd.type = 1;
	brugi_setup.gyroRollKp.min = 0;
	brugi_setup.gyroRollKp.max = 100;
	brugi_setup.gyroRollKp.scale = 1000.0;
	brugi_setup.gyroRollKp.offset = 0;
	brugi_setup.gyroRollKp.step = 0.001;
	brugi_setup.gyroRollKp.type = 1;
	brugi_setup.gyroRollKi.min = 0;
	brugi_setup.gyroRollKi.max = 100;
	brugi_setup.gyroRollKi.scale = 1000.0;
	brugi_setup.gyroRollKi.offset = 0;
	brugi_setup.gyroRollKi.step = 0.001;
	brugi_setup.gyroRollKi.type = 1;
	brugi_setup.gyroRollKd.min = 0;
	brugi_setup.gyroRollKd.max = 100;
	brugi_setup.gyroRollKd.scale = 1000.0;
	brugi_setup.gyroRollKd.offset = 0;
	brugi_setup.gyroRollKd.step = 0.001;
	brugi_setup.gyroRollKd.type = 1;
	brugi_setup.accTimeConstant.min = 1;
	brugi_setup.accTimeConstant.max = 20;
	brugi_setup.accTimeConstant.scale = 1;
	brugi_setup.accTimeConstant.offset = 0;
	brugi_setup.accTimeConstant.step = 1;
	brugi_setup.accTimeConstant.type = 0;
	brugi_setup.mpuLPF.min = 0;
	brugi_setup.mpuLPF.max = 6;
	brugi_setup.mpuLPF.scale = 1;
	brugi_setup.mpuLPF.offset = -1;
	brugi_setup.mpuLPF.step = 1;
	brugi_setup.mpuLPF.type = 0;
	brugi_setup.angleOffsetPitch.min = -120;
	brugi_setup.angleOffsetPitch.max = 120;
	brugi_setup.angleOffsetPitch.scale = 100.0;
	brugi_setup.angleOffsetPitch.offset = 0;
	brugi_setup.angleOffsetPitch.step = 0.1;
	brugi_setup.angleOffsetPitch.type = 1;
	brugi_setup.angleOffsetRoll.min = -120;
	brugi_setup.angleOffsetRoll.max = 120;
	brugi_setup.angleOffsetRoll.scale = 100.0;
	brugi_setup.angleOffsetRoll.offset = 0;
	brugi_setup.angleOffsetRoll.step = 0.1;
	brugi_setup.angleOffsetRoll.type = 1;
	brugi_setup.dirMotorPitch.min = 0;
	brugi_setup.dirMotorPitch.max = 1;
	brugi_setup.dirMotorPitch.scale = 1;
	brugi_setup.dirMotorPitch.offset = 0;
	brugi_setup.dirMotorPitch.step = 1;
	brugi_setup.dirMotorPitch.type = 0;
	brugi_setup.dirMotorRoll.min = 0;
	brugi_setup.dirMotorRoll.max = 1;
	brugi_setup.dirMotorRoll.scale = 1;
	brugi_setup.dirMotorRoll.offset = 0;
	brugi_setup.dirMotorRoll.step = 1;
	brugi_setup.dirMotorRoll.type = 0;
	brugi_setup.motorNumberPitch.min = 0;
	brugi_setup.motorNumberPitch.max = 1;
	brugi_setup.motorNumberPitch.scale = 1;
	brugi_setup.motorNumberPitch.offset = 1;
	brugi_setup.motorNumberPitch.step = 1;
	brugi_setup.motorNumberPitch.type = 0;
	brugi_setup.motorNumberRoll.min = 0;
	brugi_setup.motorNumberRoll.max = 1;
	brugi_setup.motorNumberRoll.scale = 1;
	brugi_setup.motorNumberRoll.offset = 1;
	brugi_setup.motorNumberRoll.step = 1;
	brugi_setup.motorNumberRoll.type = 0;
	brugi_setup.maxPWMmotorPitch.min = 0;
	brugi_setup.maxPWMmotorPitch.max = 100;
	brugi_setup.maxPWMmotorPitch.scale = 2.5;
	brugi_setup.maxPWMmotorPitch.offset = 0;
	brugi_setup.maxPWMmotorPitch.step = 0.1;
	brugi_setup.maxPWMmotorPitch.type = 1;
	brugi_setup.maxPWMmotorRoll.min = 0;
	brugi_setup.maxPWMmotorRoll.max = 100;
	brugi_setup.maxPWMmotorRoll.scale = 2.5;
	brugi_setup.maxPWMmotorRoll.offset = 0;
	brugi_setup.maxPWMmotorRoll.step = 0.1;
	brugi_setup.maxPWMmotorRoll.type = 1;
	brugi_setup.minRCPitch.min = -120;
	brugi_setup.minRCPitch.max = 120;
	brugi_setup.minRCPitch.scale = 1;
	brugi_setup.minRCPitch.offset = 0;
	brugi_setup.minRCPitch.step = 1;
	brugi_setup.minRCPitch.type = 0;
	brugi_setup.maxRCPitch.min = -120;
	brugi_setup.maxRCPitch.max = 120;
	brugi_setup.maxRCPitch.scale = 1;
	brugi_setup.maxRCPitch.offset = 0;
	brugi_setup.maxRCPitch.step = 1;
	brugi_setup.maxRCPitch.type = 0;
	brugi_setup.minRCRoll.min = -120;
	brugi_setup.minRCRoll.max = 120;
	brugi_setup.minRCRoll.scale = 1;
	brugi_setup.minRCRoll.offset = 0;
	brugi_setup.minRCRoll.step = 1;
	brugi_setup.minRCRoll.type = 0;
	brugi_setup.maxRCRoll.min = -120;
	brugi_setup.maxRCRoll.max = 120;
	brugi_setup.maxRCRoll.scale = 1;
	brugi_setup.maxRCRoll.offset = 0;
	brugi_setup.maxRCRoll.step = 1;
	brugi_setup.maxRCRoll.type = 0;
	brugi_setup.rcGain.min = -200;
	brugi_setup.rcGain.max = 200.0;
	brugi_setup.rcGain.scale = 1;
	brugi_setup.rcGain.offset = 0;
	brugi_setup.rcGain.step = 0.1;
	brugi_setup.rcGain.type = 1;
	brugi_setup.rcLPF.min = 1;
	brugi_setup.rcLPF.max = 20;
	brugi_setup.rcLPF.scale = 10.0;
	brugi_setup.rcLPF.offset = 0;
	brugi_setup.rcLPF.step = 0.1;
	brugi_setup.rcLPF.type = 1;
	brugi_setup.rcModePPM.min = 0;
	brugi_setup.rcModePPM.max = 1;
	brugi_setup.rcModePPM.scale = 1;
	brugi_setup.rcModePPM.offset = 0;
	brugi_setup.rcModePPM.step = 1;
	brugi_setup.rcModePPM.type = 0;
	brugi_setup.rcChannelPitch.min = 1;
	brugi_setup.rcChannelPitch.max = 16;
	brugi_setup.rcChannelPitch.scale = 1;
	brugi_setup.rcChannelPitch.offset = 1;
	brugi_setup.rcChannelPitch.step = 1;
	brugi_setup.rcChannelPitch.type = 0;
	brugi_setup.rcChannelRoll.min = 1;
	brugi_setup.rcChannelRoll.max = 16;
	brugi_setup.rcChannelRoll.scale = 1;
	brugi_setup.rcChannelRoll.offset = 1;
	brugi_setup.rcChannelRoll.step = 1;
	brugi_setup.rcChannelRoll.type = 0;
	brugi_setup.rcMid.min = 1000;
	brugi_setup.rcMid.max = 2000;
	brugi_setup.rcMid.scale = 1;
	brugi_setup.rcMid.offset = 0;
	brugi_setup.rcMid.step = 1;
	brugi_setup.rcMid.type = 0;
	brugi_setup.rcAbsolute.min = 0;
	brugi_setup.rcAbsolute.max = 1;
	brugi_setup.rcAbsolute.scale = 1;
	brugi_setup.rcAbsolute.offset = 0;
	brugi_setup.rcAbsolute.step = 1;
	brugi_setup.rcAbsolute.type = 0;
	brugi_setup.accOutput.min = 0;
	brugi_setup.accOutput.max = 1;
	brugi_setup.accOutput.scale = 1;
	brugi_setup.accOutput.offset = 0;
	brugi_setup.accOutput.step = 1;
	brugi_setup.accOutput.type = 0;
	brugi_setup.enableGyro.min = 0;
	brugi_setup.enableGyro.max = 1;
	brugi_setup.enableGyro.scale = 1;
	brugi_setup.enableGyro.offset = 0;
	brugi_setup.enableGyro.step = 1;
	brugi_setup.enableGyro.type = 0;
	brugi_setup.enableACC.min = 0;
	brugi_setup.enableACC.max = 1;
	brugi_setup.enableACC.scale = 1;
	brugi_setup.enableACC.offset = 0;
	brugi_setup.enableACC.step = 1;
	brugi_setup.enableACC.type = 0;
	brugi_setup.axisReverseZ.min = 0;
	brugi_setup.axisReverseZ.max = 1;
	brugi_setup.axisReverseZ.scale = 1;
	brugi_setup.axisReverseZ.offset = 0;
	brugi_setup.axisReverseZ.step = 1;
	brugi_setup.axisReverseZ.type = 0;
	brugi_setup.axisSwapXY.min = 0;
	brugi_setup.axisSwapXY.max = 1;
	brugi_setup.axisSwapXY.scale = 1;
	brugi_setup.axisSwapXY.offset = 0;
	brugi_setup.axisSwapXY.step = 1;
	brugi_setup.axisSwapXY.type = 0;





	printf("init simple-bgc serial port...\n");
	brugi_serial_fd = serial_open(port, baud);
}

void brugi_exit (void) {
	if (brugi_serial_fd >= 0) {
		brugi_send_cmd("OAC 0\n");
#ifndef WINDOWS
		tcflush(brugi_serial_fd, TCIFLUSH);
#endif
		close(brugi_serial_fd);
		brugi_serial_fd = -1;
		info_num = 0;
	}
}

void brugi_update (void) {
	uint8_t c = 0;
	uint8_t res = 0;
	if (brugi_serial_fd < 0) {
		return;
	}
	static uint8_t info_counter = 0;
	static uint8_t data_count = 0;
	static char data_buffer[255];
	if (info_counter < 250) {
		info_counter++;
	} else {
		info_counter = 0;
		if (info_num == 0) {
			brugi_send_cmd("par\n");
		} else if (info_num == 1) {
			brugi_send_cmd("OAC 1\n");
		}
	}
	while ((res = serial_read(brugi_serial_fd, brugi_serial_buf, 1)) > 0) {
		last_connection = time(0);
		c = brugi_serial_buf[0];

		if (c == '\n') {
			data_count = 0;
			if (strstr(data_buffer, "done.") > 0) {
				info_num = 1;


			} else if (strstr(data_buffer, "vers ") > 0) {
				brugi_setup.vers.value = (atof(data_buffer + 4 + 1) + brugi_setup.vers.offset) / brugi_setup.vers.scale;
			} else if (strstr(data_buffer, "gyroPitchKp ") > 0) {
				brugi_setup.gyroPitchKp.value = (atof(data_buffer + 11 + 1) + brugi_setup.gyroPitchKp.offset) / brugi_setup.gyroPitchKp.scale;
			} else if (strstr(data_buffer, "gyroPitchKi ") > 0) {
				brugi_setup.gyroPitchKi.value = (atof(data_buffer + 11 + 1) + brugi_setup.gyroPitchKi.offset) / brugi_setup.gyroPitchKi.scale;
			} else if (strstr(data_buffer, "gyroPitchKd ") > 0) {
				brugi_setup.gyroPitchKd.value = (atof(data_buffer + 11 + 1) + brugi_setup.gyroPitchKd.offset) / brugi_setup.gyroPitchKd.scale;
			} else if (strstr(data_buffer, "gyroRollKp ") > 0) {
				brugi_setup.gyroRollKp.value = (atof(data_buffer + 10 + 1) + brugi_setup.gyroRollKp.offset) / brugi_setup.gyroRollKp.scale;
			} else if (strstr(data_buffer, "gyroRollKi ") > 0) {
				brugi_setup.gyroRollKi.value = (atof(data_buffer + 10 + 1) + brugi_setup.gyroRollKi.offset) / brugi_setup.gyroRollKi.scale;
			} else if (strstr(data_buffer, "gyroRollKd ") > 0) {
				brugi_setup.gyroRollKd.value = (atof(data_buffer + 10 + 1) + brugi_setup.gyroRollKd.offset) / brugi_setup.gyroRollKd.scale;
			} else if (strstr(data_buffer, "accTimeConstant ") > 0) {
				brugi_setup.accTimeConstant.value = (atof(data_buffer + 15 + 1) + brugi_setup.accTimeConstant.offset) / brugi_setup.accTimeConstant.scale;
			} else if (strstr(data_buffer, "mpuLPF ") > 0) {
				brugi_setup.mpuLPF.value = (atof(data_buffer + 6 + 1) + brugi_setup.mpuLPF.offset) / brugi_setup.mpuLPF.scale;
			} else if (strstr(data_buffer, "angleOffsetPitch ") > 0) {
				brugi_setup.angleOffsetPitch.value = (atof(data_buffer + 16 + 1) + brugi_setup.angleOffsetPitch.offset) / brugi_setup.angleOffsetPitch.scale;
			} else if (strstr(data_buffer, "angleOffsetRoll ") > 0) {
				brugi_setup.angleOffsetRoll.value = (atof(data_buffer + 15 + 1) + brugi_setup.angleOffsetRoll.offset) / brugi_setup.angleOffsetRoll.scale;
			} else if (strstr(data_buffer, "dirMotorPitch ") > 0) {
				brugi_setup.dirMotorPitch.value = (atof(data_buffer + 13 + 1) + brugi_setup.dirMotorPitch.offset) / brugi_setup.dirMotorPitch.scale;
			} else if (strstr(data_buffer, "dirMotorRoll ") > 0) {
				brugi_setup.dirMotorRoll.value = (atof(data_buffer + 12 + 1) + brugi_setup.dirMotorRoll.offset) / brugi_setup.dirMotorRoll.scale;
			} else if (strstr(data_buffer, "motorNumberPitch ") > 0) {
				brugi_setup.motorNumberPitch.value = (atof(data_buffer + 16 + 1) + brugi_setup.motorNumberPitch.offset) / brugi_setup.motorNumberPitch.scale;
			} else if (strstr(data_buffer, "motorNumberRoll ") > 0) {
				brugi_setup.motorNumberRoll.value = (atof(data_buffer + 15 + 1) + brugi_setup.motorNumberRoll.offset) / brugi_setup.motorNumberRoll.scale;
			} else if (strstr(data_buffer, "maxPWMmotorPitch ") > 0) {
				brugi_setup.maxPWMmotorPitch.value = (atof(data_buffer + 16 + 1) + brugi_setup.maxPWMmotorPitch.offset) / brugi_setup.maxPWMmotorPitch.scale;
			} else if (strstr(data_buffer, "maxPWMmotorRoll ") > 0) {
				brugi_setup.maxPWMmotorRoll.value = (atof(data_buffer + 15 + 1) + brugi_setup.maxPWMmotorRoll.offset) / brugi_setup.maxPWMmotorRoll.scale;
			} else if (strstr(data_buffer, "minRCPitch ") > 0) {
				brugi_setup.minRCPitch.value = (atof(data_buffer + 10 + 1) + brugi_setup.minRCPitch.offset) / brugi_setup.minRCPitch.scale;
			} else if (strstr(data_buffer, "maxRCPitch ") > 0) {
				brugi_setup.maxRCPitch.value = (atof(data_buffer + 10 + 1) + brugi_setup.maxRCPitch.offset) / brugi_setup.maxRCPitch.scale;
			} else if (strstr(data_buffer, "minRCRoll ") > 0) {
				brugi_setup.minRCRoll.value = (atof(data_buffer + 9 + 1) + brugi_setup.minRCRoll.offset) / brugi_setup.minRCRoll.scale;
			} else if (strstr(data_buffer, "maxRCRoll ") > 0) {
				brugi_setup.maxRCRoll.value = (atof(data_buffer + 9 + 1) + brugi_setup.maxRCRoll.offset) / brugi_setup.maxRCRoll.scale;
			} else if (strstr(data_buffer, "rcGain ") > 0) {
				brugi_setup.rcGain.value = (atof(data_buffer + 6 + 1) + brugi_setup.rcGain.offset) / brugi_setup.rcGain.scale;
			} else if (strstr(data_buffer, "rcLPF ") > 0) {
				brugi_setup.rcLPF.value = (atof(data_buffer + 5 + 1) + brugi_setup.rcLPF.offset) / brugi_setup.rcLPF.scale;
			} else if (strstr(data_buffer, "rcModePPM ") > 0) {
				brugi_setup.rcModePPM.value = (atof(data_buffer + 9 + 1) + brugi_setup.rcModePPM.offset) / brugi_setup.rcModePPM.scale;
			} else if (strstr(data_buffer, "rcChannelPitch ") > 0) {
				brugi_setup.rcChannelPitch.value = (atof(data_buffer + 14 + 1) + brugi_setup.rcChannelPitch.offset) / brugi_setup.rcChannelPitch.scale;
			} else if (strstr(data_buffer, "rcChannelRoll ") > 0) {
				brugi_setup.rcChannelRoll.value = (atof(data_buffer + 13 + 1) + brugi_setup.rcChannelRoll.offset) / brugi_setup.rcChannelRoll.scale;
			} else if (strstr(data_buffer, "rcMid ") > 0) {
				brugi_setup.rcMid.value = (atof(data_buffer + 5 + 1) + brugi_setup.rcMid.offset) / brugi_setup.rcMid.scale;
			} else if (strstr(data_buffer, "rcAbsolute ") > 0) {
				brugi_setup.rcAbsolute.value = (atof(data_buffer + 10 + 1) + brugi_setup.rcAbsolute.offset) / brugi_setup.rcAbsolute.scale;
			} else if (strstr(data_buffer, "accOutput ") > 0) {
				brugi_setup.accOutput.value = (atof(data_buffer + 9 + 1) + brugi_setup.accOutput.offset) / brugi_setup.accOutput.scale;
			} else if (strstr(data_buffer, "enableGyro ") > 0) {
				brugi_setup.enableGyro.value = (atof(data_buffer + 10 + 1) + brugi_setup.enableGyro.offset) / brugi_setup.enableGyro.scale;
			} else if (strstr(data_buffer, "enableACC ") > 0) {
				brugi_setup.enableACC.value = (atof(data_buffer + 9 + 1) + brugi_setup.enableACC.offset) / brugi_setup.enableACC.scale;
			} else if (strstr(data_buffer, "axisReverseZ ") > 0) {
				brugi_setup.axisReverseZ.value = (atof(data_buffer + 12 + 1) + brugi_setup.axisReverseZ.offset) / brugi_setup.axisReverseZ.scale;
			} else if (strstr(data_buffer, "axisSwapXY ") > 0) {
				brugi_setup.axisSwapXY.value = (atof(data_buffer + 10 + 1) + brugi_setup.axisSwapXY.offset) / brugi_setup.axisSwapXY.scale;


			} else if (strstr(data_buffer, " ACC ") > 0) {
				int acc_x = 0;
				int acc_y = 0;
				sscanf(data_buffer, "%i ACC %i", &acc_y, &acc_x);
				ModelData.roll = (float)acc_x / 1000.0;
				ModelData.pitch = (float)acc_y / 1000.0;
//				printf("#### %f,%f -- %s\n", (float)acc_x / 1000.0, (float)acc_y / 1000.0,  data_buffer);
				info_num = 2;
			}

		} else if (c == '\r') {
		} else if (data_count < 200) {
			data_buffer[data_count++] = c;
			data_buffer[data_count] = 0;
		}
	}
}


