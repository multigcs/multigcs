
#include <all.h>

#include <mavlink/GCS_MAVLink/include/mavlink/v1.0/autoquad/mavlink_msg_aq_telemetry_f.h>

#define MAV_CMD_AQ_TELEMETRY 2
enum mavlinkCustomDataSets {
    AQMAV_DATASET_LEGACY1 = 0,	// legacy sets can eventually be phased out
    AQMAV_DATASET_LEGACY2,
    AQMAV_DATASET_LEGACY3,
    AQMAV_DATASET_ALL,		// use this to toggle all datasets at once
    AQMAV_DATASET_GPS_XTRA,
    AQMAV_DATASET_UKF_XTRA,
    AQMAV_DATASET_SUPERVISOR,
    AQMAV_DATASET_STACKSFREE,
    AQMAV_DATASET_GIMBAL,
    AQMAV_DATASET_ENUM_END
};


#define TCP_BUFLEN 2000
#define UDP_BUFLEN 2042
#define UDP_PORT 14550

#ifndef WINDOWS
static struct sockaddr_in si_me, si_other;
static int s, slen = sizeof(si_other) , recv_len;
int mavlink_tcp_send (uint8_t modelid, uint8_t *buf, uint16_t len);
#endif

LogList loglist[255];

static uint8_t udp_running = 0;
static uint8_t tcp_running = 0;
int16_t mission_max[MODELS_MAX];
ValueList MavLinkVars[MODELS_MAX][MAVLINK_PARAMETER_MAX];
uint8_t mavlink_update_yaw = 0;
int c, res;
char serial_buf[1024];
static uint32_t last_connection[MODELS_MAX];
static int8_t GPS_found[MODELS_MAX];
uint8_t mavlink_loghbeat = 0;
uint16_t mavlink_logs_total = 0;
uint16_t mavlink_logid = 0;
uint16_t mavlink_logstat = 0;
uint32_t mavlink_logreqsize = 0;
uint32_t mavlink_loggetsize = 0;
uint32_t mavlink_logstartstamp = 0;
uint16_t mavlink_timeout[MODELS_MAX];
uint16_t mavlink_maxparam[MODELS_MAX];
uint16_t mavlink_foundparam[MODELS_MAX];
uint8_t mavlink_udp_active = 0;
uint8_t mavlink_tcp_active = 0;
SDL_Thread *thread_udp = NULL;
SDL_Thread *thread_tcp = NULL;
int mavlink_udp (void *data);
int mavlink_tcp (void *data);
int param_timeout[MODELS_MAX];
int param_complete[MODELS_MAX];
int ahrs2_found[MODELS_MAX];

void mavlink_xml_save (uint8_t modelid, FILE *fr) {
	int16_t n = 0;
	fprintf(fr, " <mavlink>\n");
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (MavLinkVars[modelid][n].name[0] != 0) {
			fprintf(fr, "  <param><name>%s</name><value>%f</value></param>\n", MavLinkVars[modelid][n].name, MavLinkVars[modelid][n].value);
		}
	}
	fprintf(fr, " </mavlink>\n");
}

void mavlink_init_udp (void) {
	udp_running = 1;
#ifdef SDL2
	thread_udp = SDL_CreateThread(mavlink_udp, NULL, NULL);
#else
	thread_udp = SDL_CreateThread(mavlink_udp, NULL);
#endif
	if ( thread_udp == NULL ) {
		fprintf(stderr, "mavlink: Thread konnte nicht gestartet werden (mavlink_udp): %s\n", SDL_GetError());
	}
}

void mavlink_init_tcp (void) {
	tcp_running = 1;
#ifdef SDL2
	thread_tcp = SDL_CreateThread(mavlink_tcp, NULL, NULL);
#else
	thread_tcp = SDL_CreateThread(mavlink_tcp, NULL);
#endif
	if ( thread_tcp == NULL ) {
		fprintf(stderr, "mavlink: Thread konnte nicht gestartet werden (mavlink_tcp): %s\n", SDL_GetError());
	}
}

uint8_t mavlink_init (uint8_t modelid, char *port, uint32_t baud) {
	int n = 0;
	if (port[0] != '/' && strncmp(port, "COM", 3)!= 0) {
		return -1;
	}
	mavlink_maxparam[modelid] = 0;
	mavlink_foundparam[modelid] = 0;
	SDL_Log("mavlink(%i): init serial port...\n", modelid);
	ModelData[modelid].serial_fd = serial_open(port, baud);
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		MavLinkVars[modelid][n].name[0] = 0;
		MavLinkVars[modelid][n].group[0] = 0;
		MavLinkVars[modelid][n].display[0] = 0;
		MavLinkVars[modelid][n].desc[0] = 0;
		MavLinkVars[modelid][n].values[0] = 0;
		MavLinkVars[modelid][n].bits[0] = 0;
		MavLinkVars[modelid][n].value = 0.0;
		MavLinkVars[modelid][n].onload = 0.0;
		MavLinkVars[modelid][n].type = MAV_VAR_FLOAT;
		MavLinkVars[modelid][n].id = -1;
	}
	mavlink_message_t msg2;
	mavlink_msg_heartbeat_pack(127, 0, &msg2, MAV_TYPE_GCS, MAV_AUTOPILOT_INVALID, 0, 0, 0);
	mavlink_send_message(modelid, &msg2);
	return 0;
}

void mavlink_exit_udp (void) {
	udp_running = 0;
	if (thread_udp != NULL) {
		SDL_Log("mavlink: wait udp thread\n");
		SDL_WaitThread(thread_udp, NULL);
		thread_udp = NULL;
	}
}

void mavlink_exit_tcp (void) {
	tcp_running = 0;
	if (thread_tcp != NULL) {
		SDL_Log("mavlink: wait tcp thread\n");
		SDL_WaitThread(thread_tcp, NULL);
		thread_tcp = NULL;
	}
}

void mavlink_exit (uint8_t modelid) {
	if (ModelData[modelid].serial_fd >= 0) {
		serial_close(ModelData[modelid].serial_fd);
		ModelData[modelid].serial_fd = -1;
	}
}

void mavlink_stop_feeds (uint8_t modelid) {
	SDL_Log("mavlink(%i): stopping feeds!\n", modelid);
	mavlink_message_t msg1;
	mavlink_msg_request_data_stream_pack(127, 0, &msg1, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_DATA_STREAM_ALL, 0, 0);
	mavlink_send_message(modelid, &msg1);
}

void mavlink_send_value (uint8_t modelid, char *name, float val, int8_t type) {
	mavlink_message_t msg;
	if (type == -1) {
		type = MAV_VAR_FLOAT;
	}
	mavlink_msg_param_set_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, name, val, type);
	if (clientmode == 1) {
#ifndef WINDOWS
		webclient_send_value(clientmode_server, clientmode_port, name, val, type);
#endif
	} else {
		mavlink_send_message(modelid, &msg);
		ModelData[modelid].mavlink_update = (int)time(0);
	}
}

void mavlink_set_value (uint8_t modelid, char *name, float value, int8_t type, int16_t id) {
	uint16_t n = 0;
	uint8_t flag = 0;
	float min = 999999.0;
	float max = 999999.0;
	name[16] = 0;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[modelid][n].name, name) == 0 && (MavLinkVars[modelid][n].id == id || MavLinkVars[modelid][n].id == -1 || id > MAVLINK_PARAMETER_MAX || id == -1)) {
			MavLinkVars[modelid][n].value = value;
			MavLinkVars[modelid][n].id = id;
			if (type == -1 || type > 6) {
				type = MAV_VAR_FLOAT;
			}
			MavLinkVars[modelid][n].type = type;
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
			if (MavLinkVars[modelid][n].name[0] == 0) {
				if (type == MAV_VAR_FLOAT) {
					min = -999999.0;
					max = 999999.0;
				} else if (type == MAV_VAR_UINT8) {
					min = 0.0;
					max = 255.0;
				} else if (type == MAV_VAR_INT8) {
					min = -127.0;
					max = 127.0;
				} else if (type == MAV_VAR_UINT16) {
					min = 0.0;
					max = 65535.0;
				} else if (type == MAV_VAR_INT16) {
					min = -32767.0;
					max = 32767.0;
				} else if (type == MAV_VAR_UINT32) {
					min = 0.0;
					max = 999999.0;
				} else if (type == MAV_VAR_INT32) {
					min = -999999.0;
					max = 999999.0;
				} else {
					min = -999999.0;
					max = 999999.0;
					type = MAV_VAR_FLOAT;
				}
				if (strstr(name, "baud") > 0) {
					min = 1200.0;
					max = 115200.0;
				}
				strncpy(MavLinkVars[modelid][n].name, name, 17);
				MavLinkVars[modelid][n].value = value;
				MavLinkVars[modelid][n].onload = value;
				MavLinkVars[modelid][n].id = id;

				if (type == -1) {
					type = MAV_VAR_FLOAT;
				}
				//printf("###### %s ## %i ###\n", name, type);

				MavLinkVars[modelid][n].type = type;
				MavLinkVars[modelid][n].min = min;
				MavLinkVars[modelid][n].max = max;
				if (MavLinkVars[modelid][n].min > MavLinkVars[modelid][n].value) {
					MavLinkVars[modelid][n].min = MavLinkVars[modelid][n].value;
				}
				if (MavLinkVars[modelid][n].max < MavLinkVars[modelid][n].value) {
					MavLinkVars[modelid][n].max = MavLinkVars[modelid][n].value;
				}

				if (strncmp(MavLinkVars[modelid][n].name, "RC", 2) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "RC", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "CH", 2) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Channels", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "FLTMODE", 7) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "FlightMode", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "COMPASS", 7) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Compass", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "MAG", 3) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Compass", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "SR", 2) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Serial", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "TELEM", 5) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Serial", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "SERIAL", 6) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Serial", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "GPS", 3) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "GPS", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "MNT", 3) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Gimbal", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "CAM", 3) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Gimbal", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "BARO", 4) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Baro", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "THR_", 4) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Throttle", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "SUPER_SIMPLE", 12) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Simple", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "SIMPLE", 6) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Simple", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "INAV", 4) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Navigation", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "WPNAV", 5) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Navigation", 17);
				} else if (strncmp(MavLinkVars[modelid][n].name, "WP_", 3) == 0) {
					strncpy(MavLinkVars[modelid][n].group, "Navigation", 17);
				}
				break;
			}
		}
	}
	ModelData[modelid].mavlink_update = (int)time(0);
}

void mavlink_handleMessage(uint8_t modelid, mavlink_message_t* msg) {
	mavlink_message_t msg2;
	char sysmsg_str[1024];
	if (param_complete[modelid] == 0) {
		if (param_timeout[modelid] > 1) {
			param_timeout[modelid]--;
		} else if (param_timeout[modelid] == 1) {
			param_timeout[modelid] = 20;
			int n = 0;
			int n2 = 0;
			int n3 = 0;
			int flag2 = 0;
			for (n2 = 0; n2 < mavlink_maxparam[modelid]; n2++) {
				int flag = 0;
				for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
					if (MavLinkVars[modelid][n].name[0] != 0 && MavLinkVars[modelid][n].id == n2) {
						flag = 1;
						break;
					}
				}
				if (flag == 0) {
//					SDL_Log("mavlink(%i): param %i not found #\n", modelid, n2);
					mavlink_param_get_id(modelid, n2);
					flag2 = 1;
					n3++;
					if (n3 > 10) {
						break;
					}
				}
			}
			if (flag2 == 0) {
				SDL_Log("mavlink(%i): parameter complete\n", modelid);
				param_complete[modelid] = 1;
			}
		}
	}
	switch (msg->msgid) {
		case MAVLINK_MSG_ID_HEARTBEAT: {
			mavlink_heartbeat_t packet;
			mavlink_msg_heartbeat_decode(msg, &packet);
			ModelData[modelid].dronetype = packet.type;
			ModelData[modelid].pilottype = packet.autopilot;
			ModelData[modelid].mode = packet.custom_mode;
			ModelData[modelid].armed = packet.system_status;
//			SDL_Log("Heartbeat(%i): %i, %i, %i\n", modelid, ModelData[modelid].armed, packet.custom_mode, packet.system_status);
			if (mavlink_maxparam[modelid] == 0) {
				mavlink_start_feeds(modelid);
			} else if (ModelData[modelid].heartbeat == 0) {
				mavlink_start_feeds(modelid);
			}
			ModelData[modelid].heartbeat = 100;
//			sprintf(sysmsg_str, "Heartbeat: %i", (int)time(0));
			if ((*msg).sysid != 0xff) {
				ModelData[modelid].sysid = (*msg).sysid;
				ModelData[modelid].compid = (*msg).compid;
			}
			mavlink_msg_heartbeat_pack(127, 0, &msg2, MAV_TYPE_GCS, MAV_AUTOPILOT_INVALID, 0, 0, 0);
			mavlink_send_message(modelid, &msg2);
				if (ModelData[modelid].pilottype == MAV_AUTOPILOT_GENERIC) {
					strcpy(ModelData[modelid].sysstr, "Generic autopilot");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_PIXHAWK) {
					strcpy(ModelData[modelid].sysstr, "Pixhawk");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_SLUGS) {
					strcpy(ModelData[modelid].sysstr, "SLUGS autopilot");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_ARDUPILOTMEGA) {
					strcpy(ModelData[modelid].sysstr, "ArduPilotMega");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_OPENPILOT) {
					strcpy(ModelData[modelid].sysstr, "OpenPilot");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_GENERIC_WAYPOINTS_ONLY) {
					strcpy(ModelData[modelid].sysstr, "simple Generic autopilot");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_GENERIC_WAYPOINTS_AND_SIMPLE_NAVIGATION_ONLY) {
					strcpy(ModelData[modelid].sysstr, "simple2 Generic autopilot");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_GENERIC_MISSION_FULL) {
					strcpy(ModelData[modelid].sysstr, "Generic autopilot");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_INVALID) {
					strcpy(ModelData[modelid].sysstr, "GCS or other MAVLink component");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_PPZ) {
					strcpy(ModelData[modelid].sysstr, "PPZ UAV");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_UDB) {
					strcpy(ModelData[modelid].sysstr, "UAV Dev Board");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_FP) {
					strcpy(ModelData[modelid].sysstr, "FlexiPilot");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_PX4) {
					strcpy(ModelData[modelid].sysstr, "PX4 Autopilot");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_SMACCMPILOT) {
					strcpy(ModelData[modelid].sysstr, "SMACCMPilot");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_AUTOQUAD) {
					strcpy(ModelData[modelid].sysstr, "AutoQuad");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_ARMAZILA) {
					strcpy(ModelData[modelid].sysstr, "Armazila");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_AEROB) {
					strcpy(ModelData[modelid].sysstr, "Aerob");
				} else if (ModelData[modelid].pilottype == MAV_AUTOPILOT_ASLUAV) {
					strcpy(ModelData[modelid].sysstr, "ASLUAV autopilot");
				} else {
					sprintf(ModelData[modelid].sysstr, "UNKNOWN_FC(%i)", ModelData[modelid].pilottype);
				}
			break;
		}
		case MAVLINK_MSG_ID_RC_CHANNELS_SCALED: {
			mavlink_rc_channels_scaled_t packet;
			mavlink_msg_rc_channels_scaled_decode(msg, &packet);
//			SDL_Log("Radio1: %i,%i,%i\n", packet.chan1_scaled, packet.chan2_scaled, packet.chan3_scaled);
			ModelData[modelid].radio[0] = (int)packet.chan1_scaled / 100.0;
			ModelData[modelid].radio[1] = (int)packet.chan2_scaled / 100.0;
			ModelData[modelid].radio[2] = (int)packet.chan3_scaled / 100.0;
			ModelData[modelid].radio[3] = (int)packet.chan4_scaled / 100.0;
			ModelData[modelid].radio[4] = (int)packet.chan5_scaled / 100.0;
			ModelData[modelid].radio[5] = (int)packet.chan6_scaled / 100.0;
			ModelData[modelid].radio[6] = (int)packet.chan7_scaled / 100.0;
			ModelData[modelid].radio[7] = (int)packet.chan8_scaled / 100.0;
			break;
		}
		case MAVLINK_MSG_ID_SCALED_PRESSURE: {
			mavlink_scaled_pressure_t packet;
			mavlink_msg_scaled_pressure_decode(msg, &packet);
//			SDL_Log("BAR;%i;%0.2f;%0.2f;%0.2f\n", time(0), packet.press_abs, packet.press_diff, packet.temperature / 100.0);
			break;
		}
		case MAVLINK_MSG_ID_ATTITUDE: {
			mavlink_attitude_t packet;
			mavlink_msg_attitude_decode(msg, &packet);
			if (ahrs2_found[modelid] == 0) {
				ModelData[modelid].roll = toDeg(packet.roll);
				ModelData[modelid].pitch = toDeg(packet.pitch);
			}
			if (toDeg(packet.yaw) < 0.0) {
				ModelData[modelid].yaw = 360.0 + toDeg(packet.yaw);
			} else {
				ModelData[modelid].yaw = toDeg(packet.yaw);
			}
			mavlink_update_yaw = 1;
//			SDL_Log("ATT;%i;%0.2f;%0.2f;%0.2f\n", time(0), toDeg(packet.roll), toDeg(packet.pitch), toDeg(packet.yaw));
			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_RAW_IMU: {
			mavlink_raw_imu_t packet;
			mavlink_msg_raw_imu_decode(msg, &packet);
			ModelData[modelid].acc_x = (float)packet.xacc / 1000.0;
			ModelData[modelid].acc_y = (float)packet.yacc / 1000.0;
			ModelData[modelid].acc_z = (float)packet.zacc / 1000.0;
			ModelData[modelid].gyro_x = (float)packet.xgyro;
			ModelData[modelid].gyro_y = (float)packet.ygyro;
			ModelData[modelid].gyro_z = (float)packet.zgyro;
			ModelData[modelid].mag_x = (float)packet.xmag;
			ModelData[modelid].mag_y = (float)packet.ymag;
			ModelData[modelid].mag_z = (float)packet.zmag;
//printf("IMU1_RAW %f %f %f\n", (float)packet.xmag, (float)packet.ymag, (float)packet.zmag);
			break;
		}
		case MAVLINK_MSG_ID_SCALED_IMU: {
			mavlink_scaled_imu_t packet;
			mavlink_msg_scaled_imu_decode(msg, &packet);
//printf("IMU1_SCL %f %f %f\n", (float)packet.xmag, (float)packet.ymag, (float)packet.zmag);
			break;
		}
		case MAVLINK_MSG_ID_SCALED_IMU2: {
			mavlink_scaled_imu2_t packet;
			mavlink_msg_scaled_imu2_decode(msg, &packet);
			ModelData[modelid].mag2_x = (float)packet.xmag;
			ModelData[modelid].mag2_y = (float)packet.ymag;
			ModelData[modelid].mag2_z = (float)packet.zmag;
//printf("IMU2_SCL %f %f %f\n", (float)packet.xmag, (float)packet.ymag, (float)packet.zmag);
			break;
		}
		case MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN: {
			mavlink_gps_global_origin_t packet;
			mavlink_msg_gps_global_origin_decode(msg, &packet);
			WayPoints[modelid][0].p_lat = (float)packet.latitude / 10000000.0;
			WayPoints[modelid][0].p_long = (float)packet.longitude / 10000000.0;
			WayPoints[modelid][0].p_alt = (float)packet.altitude / 1000.0;
			break;
		}
		case MAVLINK_MSG_ID_GPS_RAW_INT: {
			mavlink_gps_raw_int_t packet;
			mavlink_msg_gps_raw_int_decode(msg, &packet);
			if (packet.lat != 0 && packet.lon != 0) {
				ModelData[modelid].p_lat = (float)packet.lat / 10000000.0;
				ModelData[modelid].p_long = (float)packet.lon / 10000000.0;
/*
				static uint8_t pos[MODELS_MAX];
				ModelData[modelid].history[pos[modelid]][0] = ModelData[modelid].p_lat;
				ModelData[modelid].history[pos[modelid]][1] = ModelData[modelid].p_long;
				ModelData[modelid].history[pos[modelid]][2] = ModelData[modelid].p_alt;
				ModelData[modelid].history[pos[modelid]][3] = ModelData[modelid].yaw;
				ModelData[modelid].history[pos[modelid]][4] = ModelData[modelid].roll;
				pos[modelid]++;
*/
				ModelData[modelid].speed = (float)packet.vel / 100.0;
				ModelData[modelid].numSat = packet.satellites_visible;
				ModelData[modelid].gpsfix = packet.fix_type;
				ModelData[modelid].hdop = (float)packet.eph / 100.0;
				ModelData[modelid].vdop = (float)packet.epv / 100.0;
				if (ModelData[modelid].gpsfix > 2) {
					GPS_found[modelid] = 1;
					ModelData[modelid].p_alt = (float)packet.alt / 1000.0;
				}
				redraw_flag = 1;
			}
			break;
		}
		case MAVLINK_MSG_ID_RC_CHANNELS_RAW: {
			mavlink_rc_channels_raw_t packet;
			mavlink_msg_rc_channels_raw_decode(msg, &packet);
//			SDL_Log("Radio2: %i,%i,%i\n", packet.chan1_raw, packet.chan2_raw, packet.chan3_raw);
			int cn = packet.port * 8;
			if (ModelData[modelid].chancount < packet.port * 8 + 8) {
				ModelData[modelid].chancount = packet.port * 8 + 8;
			}
			ModelData[modelid].radio_raw[cn++] = (int)packet.chan1_raw;
			ModelData[modelid].radio_raw[cn++] = (int)packet.chan2_raw;
			ModelData[modelid].radio_raw[cn++] = (int)packet.chan3_raw;
			ModelData[modelid].radio_raw[cn++] = (int)packet.chan4_raw;
			ModelData[modelid].radio_raw[cn++] = (int)packet.chan5_raw;
			ModelData[modelid].radio_raw[cn++] = (int)packet.chan6_raw;
			ModelData[modelid].radio_raw[cn++] = (int)packet.chan7_raw;
			ModelData[modelid].radio_raw[cn++] = (int)packet.chan8_raw;
			if (ModelData[modelid].pilottype == MAV_AUTOPILOT_AUTOQUAD) {
				cn = packet.port * 8;
				ModelData[modelid].radio[cn++] = (int)packet.chan1_raw / 10 - 175;
				ModelData[modelid].radio[cn++] = (int)packet.chan2_raw / 10 - 100;
				ModelData[modelid].radio[cn++] = (int)packet.chan3_raw / 10 - 100;
				ModelData[modelid].radio[cn++] = (int)packet.chan4_raw / 10 - 100;
				ModelData[modelid].radio[cn++] = (int)packet.chan5_raw / 10 - 100;
				ModelData[modelid].radio[cn++] = (int)packet.chan6_raw / 10 - 100;
				ModelData[modelid].radio[cn++] = (int)packet.chan7_raw / 10 - 100;
				ModelData[modelid].radio[cn++] = (int)packet.chan8_raw / 10 - 100;
				ModelData[modelid].rssi_rc_rx = (int)packet.rssi * 100 / 255;
			} else {
				cn = packet.port * 8;
				ModelData[modelid].radio[cn++] = (int)packet.chan1_raw / 5 - 300;
				ModelData[modelid].radio[cn++] = (int)packet.chan2_raw / 5 - 300;
				ModelData[modelid].radio[cn++] = (int)packet.chan3_raw / 5 - 300;
				ModelData[modelid].radio[cn++] = (int)packet.chan4_raw / 5 - 300;
				ModelData[modelid].radio[cn++] = (int)packet.chan5_raw / 5 - 300;
				ModelData[modelid].radio[cn++] = (int)packet.chan6_raw / 5 - 300;
				ModelData[modelid].radio[cn++] = (int)packet.chan7_raw / 5 - 300;
				ModelData[modelid].radio[cn++] = (int)packet.chan8_raw / 5 - 300;
				ModelData[modelid].rssi_rc_rx = (int)packet.rssi * 100 / 255;
			}
			break;
		}
		case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW: {
//			SDL_Log("SERVO_OUTPUT_RAW\n");
			break;
		}
		case MAVLINK_MSG_ID_SYS_STATUS: {
			mavlink_sys_status_t packet;
			mavlink_msg_sys_status_decode(msg, &packet);
//			SDL_Log("%0.1f %%, %0.3f V\n", packet.load / 10.0, packet.voltage_battery / 1000.0);
			ModelData[modelid].voltage = packet.voltage_battery / 1000.0;
			ModelData[modelid].ampere = (float)packet.current_battery / 100.0;
			ModelData[modelid].load = packet.load / 10.0;
			break;
		}
		case MAVLINK_MSG_ID_STATUSTEXT: {
			mavlink_statustext_t packet;
			mavlink_msg_statustext_decode(msg, &packet);
			if (packet.text[strlen(packet.text) - 1] == '\n') {
				packet.text[strlen(packet.text) - 1] = 0;
			}
			SDL_Log("mavlink(%i): msg: ### %s ###\n", modelid, packet.text);
			sprintf(sysmsg_str, "model:%i %s", modelid, packet.text);
			sys_message(sysmsg_str);
			break;
		}
		case MAVLINK_MSG_ID_PARAM_VALUE: {
			mavlink_param_value_t packet;
			mavlink_msg_param_value_decode(msg, &packet);
			char var[101];
			uint16_t n1 = 0;
			uint16_t n2 = 0;
			for (n1 = 0; n1 < strlen(packet.param_id); n1++) {
				if (packet.param_id[n1] != 9 && packet.param_id[n1] != ' ' && packet.param_id[n1] != '\t') {
					var[n2++] = packet.param_id[n1];
				}
			}
			var[n2++] = 0;
			var[16] = 0;
			mavlink_maxparam[modelid] = packet.param_count;
			mavlink_timeout[modelid] = 0;
			mavlink_set_value(modelid, var, packet.param_value, packet.param_type, packet.param_index);
			if (packet.param_index + 1 == packet.param_count || packet.param_index % 10 == 0) {
				mavlink_param_xml_meta_load(modelid);
			}
			sprintf(sysmsg_str, "PARAM_VALUE (%03i/%03i): %s = %f (Type: %i)", packet.param_index + 1, packet.param_count, var, packet.param_value, packet.param_type);
			SDL_Log("mavlink(%i): %s\n", modelid, sysmsg_str);
			for (n1 = strlen(var); n1 < 20; n1++) {
				var[n1] = ' ';
				var[n1 + 1] = 0;
			}
			sprintf(sysmsg_str, "model:%i PARAM_VALUE (%03i/%03i): %s = %0.3f", modelid, packet.param_index + 1, packet.param_count, var, packet.param_value);
			for (n1 = strlen(sysmsg_str); n1 < 63; n1++) {
				sysmsg_str[n1] = ' ';
				sysmsg_str[n1 + 1] = 0;
			}
			sys_message(sysmsg_str);
			param_timeout[modelid] = 20;
			break;
		}
		case MAVLINK_MSG_ID_MISSION_COUNT: {
			mavlink_mission_count_t packet;
			mavlink_msg_mission_count_decode(msg, &packet);
			sprintf(sysmsg_str, "model:%i MISSION_COUNT: %i\n", modelid, packet.count);
			sys_message(sysmsg_str);
			mission_max[modelid] = packet.count;
			if (mission_max[modelid] > 0) {
				mavlink_msg_mission_request_pack(127, 0, &msg2, ModelData[modelid].sysid, ModelData[modelid].compid, 0);
				mavlink_send_message(modelid, &msg2);
			}
			break;
		}
		case MAVLINK_MSG_ID_MISSION_ACK: {
//			SDL_Log("mavlink(%i): Mission-Transfer ACK\n", modelid);
			break;
		}
		case MAVLINK_MSG_ID_MISSION_REQUEST: {
			mavlink_mission_request_t packet;
			mavlink_msg_mission_request_decode(msg, &packet);
			uint16_t id = packet.seq;
			uint16_t id2 = packet.seq;
			uint16_t type = 0;
			if (ModelData[modelid].teletype == TELETYPE_MEGAPIRATE_NG || ModelData[modelid].teletype == TELETYPE_ARDUPILOT) {
				if (id2 > 0) {
					id2 = id2 - 1;
				}
			}
			sprintf(sysmsg_str, "model:%i sending Waypoint (%i): %s\n", modelid, id, WayPoints[modelid][id2 + 1].name);
			sys_message(sysmsg_str);
			if (strcmp(WayPoints[modelid][id2 + 1].command, "WAYPOINT") == 0) {
				SDL_Log("mavlink(%i): Type: MAV_CMD_NAV_WAYPOINT\n", modelid);
				type = MAV_CMD_NAV_WAYPOINT;
			} else if (strcmp(WayPoints[modelid][id2 + 1].command, "RTL") == 0) {
				SDL_Log("mavlink(%i): Type: MAV_CMD_NAV_RETURN_TO_LAUNCH\n", modelid);
				type = MAV_CMD_NAV_RETURN_TO_LAUNCH;
			} else if (strcmp(WayPoints[modelid][id2 + 1].command, "LAND") == 0) {
				SDL_Log("mavlink(%i): Type: MAV_CMD_NAV_LAND\n", modelid);
				type = MAV_CMD_NAV_LAND;
			} else if (strcmp(WayPoints[modelid][id2 + 1].command, "TAKEOFF") == 0) {
				SDL_Log("mavlink(%i): Type: MAV_CMD_NAV_TAKEOFF\n", modelid);
				type = MAV_CMD_NAV_TAKEOFF;
			} else if (strcmp(WayPoints[modelid][id2 + 1].command, "SHUTTER") == 0) {
				SDL_Log("mavlink(%i): Type: MAV_CMD_DO_DIGICAM_CONTROL\n", modelid);
				type = MAV_CMD_DO_DIGICAM_CONTROL;
			} else if (strcmp(WayPoints[modelid][id2 + 1].command, "SHUTTER_INT") == 0) {
				SDL_Log("mavlink(%i): Type: MAV_CMD_DO_SET_CAM_TRIGG_DIST\n", modelid);
				type = MAV_CMD_DO_SET_CAM_TRIGG_DIST;
			} else if (strcmp(WayPoints[modelid][id2 + 1].command, "RELAY") == 0) {
				SDL_Log("mavlink(%i): Type: MAV_CMD_DO_SET_RELAY\n", modelid);
				type = MAV_CMD_DO_SET_RELAY;
			} else if (strcmp(WayPoints[modelid][id2 + 1].command, "RELAY_REP") == 0) {
				SDL_Log("mavlink(%i): Type: MAV_CMD_DO_REPEAT_RELAY\n", modelid);
				type = MAV_CMD_DO_REPEAT_RELAY;
			} else if (strcmp(WayPoints[modelid][id2 + 1].command, "SERVO") == 0) {
				SDL_Log("mavlink(%i): Type: MAV_CMD_DO_SET_SERVO\n", modelid);
				type = MAV_CMD_DO_SET_SERVO;
			} else if (strcmp(WayPoints[modelid][id2 + 1].command, "SERVO_REP") == 0) {
				SDL_Log("mavlink(%i): Type: MAV_CMD_DO_REPEAT_SERVO\n", modelid);
				type = MAV_CMD_DO_REPEAT_SERVO;
			} else if (strcmp(WayPoints[modelid][id2 + 1].command, "SET_ROI") == 0) {
				SDL_Log("mavlink(%i): Type: MAV_CMD_NAV_ROI\n", modelid);
				type = MAV_CMD_NAV_ROI;
				type = 201;
			} else {
				SDL_Log("mavlink(%i): Type: UNKNOWN\n", modelid);
				type = MAV_CMD_NAV_WAYPOINT;
			}

			sprintf(sysmsg_str, "SENDING MISSION_ITEM: %i: %f, %f, %f\n", id, WayPoints[modelid][id2 + 1].p_lat, WayPoints[modelid][id2 + 1].p_long, WayPoints[modelid][id2 + 1].p_alt);
			SDL_Log("mavlink(%i): %s\n", modelid, sysmsg_str);
			if (ModelData[modelid].dronetype != MAV_TYPE_FIXED_WING && WayPoints[modelid][id2 + 1].frametype == MAV_FRAME_GLOBAL) {
				SDL_Log("mavlink(%i): copter absolut alt workaround", modelid);
				mavlink_msg_mission_item_pack(127, 0, &msg2, ModelData[modelid].sysid, ModelData[modelid].compid, id, WayPoints[modelid][id2 + 1].frametype, type, 0, 1, WayPoints[modelid][id2 + 1].param1, WayPoints[modelid][id2 + 1].param2, WayPoints[modelid][id2 + 1].param3, WayPoints[modelid][id2 + 1].param4, WayPoints[modelid][id2 + 1].p_lat, WayPoints[modelid][id2 + 1].p_long, WayPoints[modelid][id2 + 1].p_alt - WayPoints[modelid][0].p_alt);
			} else {
				mavlink_msg_mission_item_pack(127, 0, &msg2, ModelData[modelid].sysid, ModelData[modelid].compid, id, WayPoints[modelid][id2 + 1].frametype, type, 0, 1, WayPoints[modelid][id2 + 1].param1, WayPoints[modelid][id2 + 1].param2, WayPoints[modelid][id2 + 1].param3, WayPoints[modelid][id2 + 1].param4, WayPoints[modelid][id2 + 1].p_lat, WayPoints[modelid][id2 + 1].p_long, WayPoints[modelid][id2 + 1].p_alt);
			}
			mavlink_send_message(modelid, &msg2);
			break;
		}
		case MAVLINK_MSG_ID_MISSION_ITEM: {
			mavlink_mission_item_t packet;
			mavlink_msg_mission_item_decode(msg, &packet);
			sprintf(sysmsg_str, "RECEIVED MISSION_ITEM: %i/%i: %f, %f, %f (%i)", packet.seq, mission_max[modelid], packet.x, packet.y, packet.z, packet.frame);
			SDL_Log("mavlink(%i): %s\n", modelid, sysmsg_str);
			sprintf(sysmsg_str, "	->: %f, %f, %f, %f", packet.param1, packet.param2, packet.param3, packet.param4);
			SDL_Log("mavlink(%i): %s\n", modelid, sysmsg_str);
			sprintf(sysmsg_str, "	->: %i, %i, %i", packet.command, packet.current, packet.autocontinue);
			SDL_Log("mavlink(%i): %s\n", modelid, sysmsg_str);
			sprintf(sysmsg_str, "model:%i RECEIVED MISSION_ITEM: %i/%i: %f, %f, %f (%i)", modelid, packet.seq, mission_max[modelid], packet.x, packet.y, packet.z, packet.frame);
			sys_message(sysmsg_str);
			if (packet.seq < mission_max[modelid] - 1) {
				mavlink_msg_mission_request_pack(127, 0, &msg2, ModelData[modelid].sysid, ModelData[modelid].compid, packet.seq + 1);
				mavlink_send_message(modelid, &msg2);
			} else {
				mavlink_msg_mission_ack_pack(127, 0, &msg2, ModelData[modelid].sysid, ModelData[modelid].compid, 15);
				mavlink_send_message(modelid, &msg2);
			}
			if (ModelData[modelid].teletype == TELETYPE_MEGAPIRATE_NG || ModelData[modelid].teletype == TELETYPE_ARDUPILOT) {
				if (packet.seq > 0) {
					packet.seq = packet.seq - 1;
				} else {
					break;
				}
			}
			SDL_Log("mavlink(%i): getting WP(%i): %f, %f\n", modelid, packet.seq, packet.x, packet.y);
			switch (packet.command) {
				case MAV_CMD_NAV_WAYPOINT: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "WAYPOINT");
					break;
				}
				case MAV_CMD_NAV_LOITER_UNLIM: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "LOITER_UNLIM");
					break;
				}
				case MAV_CMD_NAV_LOITER_TURNS: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "LOITER_TURNS");
					break;
				}
				case MAV_CMD_NAV_LOITER_TIME: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "LOITER_TIME");
					break;
				}
				case MAV_CMD_NAV_RETURN_TO_LAUNCH: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "RTL");
					break;
				}
				case MAV_CMD_NAV_LAND: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "LAND");
					break;
				}
				case MAV_CMD_NAV_TAKEOFF: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "TAKEOFF");
					break;
				}
				case MAV_CMD_DO_DIGICAM_CONTROL: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "SHUTTER");
					break;
				}
				case MAV_CMD_DO_SET_CAM_TRIGG_DIST: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "SHUTTER_INT");
					break;
				}
				case MAV_CMD_DO_SET_RELAY: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "RELAY");
					break;
				}
				case MAV_CMD_DO_REPEAT_RELAY: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "RELAY_REP");
					break;
				}
				case MAV_CMD_DO_SET_SERVO: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "SERVO");
					break;
				}
				case MAV_CMD_DO_REPEAT_SERVO: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "SERVO_REP");
					break;
				}
				case MAV_CMD_NAV_ROI: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "SET_ROI");
					break;
				}
				case 201: {
					strcpy(WayPoints[modelid][1 + packet.seq].command, "SET_ROI");
					break;
				}
				default: {
					sprintf(WayPoints[modelid][1 + packet.seq].command, "CMD:%i", packet.command);
					break;
				}
			}
			if (packet.x == 0.0) {
				packet.x = 0.00001;
			}
			if (packet.y == 0.0) {
				packet.y = 0.00001;
			}
			if (packet.z == 0.0) {
				packet.z = 0.00001;
			}
			if (ModelData[modelid].dronetype != MAV_TYPE_FIXED_WING && WayPoints[modelid][1 + packet.seq].frametype == MAV_FRAME_GLOBAL) {
				SDL_Log("mavlink(%i): copter absolut alt workaround", modelid);
				packet.z += WayPoints[modelid][0].p_alt;
			}

			WayPoints[modelid][1 + packet.seq].p_lat = packet.x;
			WayPoints[modelid][1 + packet.seq].p_long = packet.y;
			WayPoints[modelid][1 + packet.seq].p_alt = packet.z;
			WayPoints[modelid][1 + packet.seq].param1 = packet.param1;
			WayPoints[modelid][1 + packet.seq].param2 = packet.param2;
			WayPoints[modelid][1 + packet.seq].param3 = packet.param3;
			WayPoints[modelid][1 + packet.seq].param4 = packet.param4;
			WayPoints[modelid][1 + packet.seq].frametype = packet.frame;
			sprintf(WayPoints[modelid][1 + packet.seq].name, "WP%i", packet.seq + 1);

			WayPoints[modelid][1 + packet.seq + 1].p_lat = 0.0;
			WayPoints[modelid][1 + packet.seq + 1].p_long = 0.0;
			WayPoints[modelid][1 + packet.seq + 1].p_alt = 0.0;
			WayPoints[modelid][1 + packet.seq + 1].param1 = 0.0;
			WayPoints[modelid][1 + packet.seq + 1].param2 = 0.0;
			WayPoints[modelid][1 + packet.seq + 1].param3 = 0.0;
			WayPoints[modelid][1 + packet.seq + 1].param4 = 0.0;
			WayPoints[modelid][1 + packet.seq + 1].name[0] = 0;
			WayPoints[modelid][1 + packet.seq + 1].frametype = 0;
			WayPoints[modelid][1 + packet.seq + 1].command[0] = 0;
			break;
		}
		case MAVLINK_MSG_ID_MISSION_CURRENT: {
			mavlink_mission_current_t packet;
			mavlink_msg_mission_current_decode(msg, &packet);
			uav_active_waypoint = (uint8_t)packet.seq;
			break;
		}
		case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT: {
			mavlink_nav_controller_output_t packet;
			mavlink_msg_nav_controller_output_decode(msg, &packet);
			break;
		}
		case MAVLINK_MSG_ID_VFR_HUD: {
			mavlink_vfr_hud_t packet;
			mavlink_msg_vfr_hud_decode(msg, &packet);
			if (GPS_found[modelid] == 0) {
				ModelData[modelid].p_alt = packet.alt;
			}
			break;
		}
		case MAVLINK_MSG_ID_RADIO_STATUS: {
			mavlink_radio_status_t packet;
			mavlink_msg_radio_status_decode(msg, &packet);
			ModelData[modelid].rssi_tx = packet.rssi / 2;
			ModelData[modelid].rssi_rx = packet.remrssi / 2;
			break;
		}
		case MAVLINK_MSG_ID_RADIO: {
			mavlink_radio_t packet;
			mavlink_msg_radio_decode(msg, &packet);
			ModelData[modelid].rssi_tx = packet.rssi / 2;
			ModelData[modelid].rssi_rx = packet.remrssi / 2;
			break;
		}
		case MAVLINK_MSG_ID_GLOBAL_POSITION_INT: {
			mavlink_global_position_int_t packet;
			mavlink_msg_global_position_int_decode(msg, &packet);
			if (GPS_found[modelid] == 0) {
				if (packet.lat != 0 && packet.lon != 0) {
				}
			}
			break;
		}
		case MAVLINK_MSG_ID_SYSTEM_TIME: {
			mavlink_system_time_t packet;
			mavlink_msg_system_time_decode(msg, &packet);
			break;
		}
		case MAVLINK_MSG_ID_RC_CHANNELS: {
			mavlink_rc_channels_t packet;
			mavlink_msg_rc_channels_decode(msg, &packet);
//			SDL_Log("Radio3: %i,%i,%i\n", packet.chan1_raw, packet.chan2_raw, packet.chan3_raw);

			ModelData[modelid].radio_raw[0] = (int)packet.chan1_raw;
			ModelData[modelid].radio_raw[1] = (int)packet.chan2_raw;
			ModelData[modelid].radio_raw[2] = (int)packet.chan3_raw;
			ModelData[modelid].radio_raw[3] = (int)packet.chan4_raw;
			ModelData[modelid].radio_raw[4] = (int)packet.chan5_raw;
			ModelData[modelid].radio_raw[5] = (int)packet.chan6_raw;
			ModelData[modelid].radio_raw[6] = (int)packet.chan7_raw;
			ModelData[modelid].radio_raw[7] = (int)packet.chan8_raw;

			ModelData[modelid].radio[0] = (int)packet.chan1_raw / 5 - 300;
			ModelData[modelid].radio[1] = (int)packet.chan2_raw / 5 - 300;
			ModelData[modelid].radio[2] = (int)packet.chan3_raw / 5 - 300;
			ModelData[modelid].radio[3] = (int)packet.chan4_raw / 5 - 300;
			ModelData[modelid].radio[4] = (int)packet.chan5_raw / 5 - 300;
			ModelData[modelid].radio[5] = (int)packet.chan6_raw / 5 - 300;
			ModelData[modelid].radio[6] = (int)packet.chan7_raw / 5 - 300;
			ModelData[modelid].radio[7] = (int)packet.chan8_raw / 5 - 300;
			ModelData[modelid].radio[8] = (int)packet.chan9_raw / 5 - 300;
			ModelData[modelid].radio[9] = (int)packet.chan10_raw / 5 - 300;
			ModelData[modelid].radio[10] = (int)packet.chan11_raw / 5 - 300;
			ModelData[modelid].radio[11] = (int)packet.chan12_raw / 5 - 300;
			ModelData[modelid].radio[12] = (int)packet.chan13_raw / 5 - 300;
			ModelData[modelid].radio[13] = (int)packet.chan14_raw / 5 - 300;
			ModelData[modelid].radio[14] = (int)packet.chan15_raw / 5 - 300;
			ModelData[modelid].radio[15] = (int)packet.chan16_raw / 5 - 300;
			uint16_t n = 0;
			for (n = 1; n < 16; n++) {
				if (ModelData[modelid].radio[n] > 100) {
					ModelData[modelid].radio[n] = 100;
				} else if (ModelData[modelid].radio[n] < -100) {
					ModelData[modelid].radio[n] = -100;
				}
			}
			ModelData[modelid].rssi_rc_rx = (int)packet.rssi * 100 / 255;
			ModelData[modelid].chancount = (uint8_t)packet.chancount;
			break;
		}
		case MAVLINK_MSG_ID_AHRS: {
			mavlink_ahrs_t packet;
			mavlink_msg_ahrs_decode(msg, &packet);
			break;
		}
		case MAVLINK_MSG_ID_HWSTATUS: {
			mavlink_hwstatus_t packet;
			mavlink_msg_hwstatus_decode(msg, &packet);
			ModelData[modelid].fc_voltage1 = (float)packet.Vcc / 1000.0;
			ModelData[modelid].fc_i2c_errors = packet.I2Cerr;
//			SDL_Log("############### hwstat\n");
			break;
		}
		case MAVLINK_MSG_ID_POWER_STATUS: {
			mavlink_power_status_t packet;
			mavlink_msg_power_status_decode(msg, &packet);
			ModelData[modelid].fc_voltage1 = (float)packet.Vcc / 1000.0;
			ModelData[modelid].fc_voltage2 = (float)packet.Vservo / 1000.0;
			ModelData[modelid].fc_status = packet.flags;
//			SDL_Log("############### powerstat\n");
			break;
		}
		case MAVLINK_MSG_ID_MEMINFO: {
			mavlink_meminfo_t packet;
			mavlink_msg_meminfo_decode(msg, &packet);
//			SDL_Log("############### meminfo\n");
			break;
		}
		case MAVLINK_MSG_ID_AHRS2: {
			mavlink_ahrs2_t packet;
			mavlink_msg_ahrs2_decode(msg, &packet);
			ahrs2_found[modelid] = 1;
			ModelData[modelid].roll = toDeg(packet.roll);
			ModelData[modelid].pitch = toDeg(packet.pitch);
			mavlink_update_yaw = 1;
			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_MOUNT_STATUS: {
			mavlink_mount_status_t packet;
			mavlink_msg_mount_status_decode(msg, &packet);
			ModelData[modelid].mnt_pitch = (float)packet.pointing_a / 100.0;
			ModelData[modelid].mnt_roll = (float)packet.pointing_b / 100.0;
			ModelData[modelid].mnt_yaw = (float)packet.pointing_c / 100.0;
		}
		case MAVLINK_MSG_ID_WIND: {
			mavlink_wind_t packet;
			mavlink_msg_wind_decode(msg, &packet);
			break;
		}
		case MAVLINK_MSG_ID_LOG_ENTRY: {
			mavlink_log_entry_t packet;
			mavlink_msg_log_entry_decode(msg, &packet);
			loglist[mavlink_logs_total].id = packet.id;
			loglist[mavlink_logs_total].size = packet.size;
			mavlink_logs_total++;
			break;
		}
		case MAVLINK_MSG_ID_LOG_DATA: {
			mavlink_log_data_t packet;
			mavlink_msg_log_data_decode(msg, &packet);
			mavlink_logid = packet.id;
			mavlink_loggetsize = packet.ofs + packet.count;
			mavlink_logstat = mavlink_loggetsize * 100 / mavlink_logreqsize;
			mavlink_loghbeat = 100;
			if (mavlink_logstartstamp == 0) {
				mavlink_logstartstamp = SDL_GetTicks();
			}
			if (mavlink_loggetsize == mavlink_logreqsize) {
				mavlink_logstat = 100;
				mavlink_loghbeat = 255;
			}
			char tmp_str[1024];
			sprintf(tmp_str, "/tmp/mavlink_%i_%i.log", packet.id, mavlink_logreqsize);
			FILE *fdlog = fopen(tmp_str, "ab");
			fwrite(packet.data, packet.count, 1, fdlog);
			fclose(fdlog);
			break;
		}
		case MAVLINK_MSG_ID_DATA_STREAM: {
			mavlink_data_stream_t packet;
			mavlink_msg_data_stream_decode(msg, &packet);
//			SDL_Log("mavlink: ## MAVLINK_MSG_ID_DATA_STREAM message_rate %i ##\n", packet.message_rate); //UINT16_T
//			SDL_Log("mavlink: ## MAVLINK_MSG_ID_DATA_STREAM stream_id %i ##\n", packet.stream_id); //UINT8_T
//			SDL_Log("mavlink: ## MAVLINK_MSG_ID_DATA_STREAM on_off %i ##\n", packet.on_off); //UINT8_T
			break;
		}
		case 150: { // MAVLINK_MSG_ID_AQ_TELEMETRY_F and MAVLINK_MSG_ID_SENSOR_OFFSETS
/*
			printf("########################################\n");
			if (ModelData[modelid].pilottype == MAV_AUTOPILOT_AUTOQUAD) {
				mavlink_aq_telemetry_f_t packet;
				mavlink_msg_aq_telemetry_f_decode(msg, &packet);
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value1 %f ##\n", packet.value1); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value2 %f ##\n", packet.value2); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value3 %f ##\n", packet.value3); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value4 %f ##\n", packet.value4); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value5 %f ##\n", packet.value5); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value6 %f ##\n", packet.value6); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value7 %f ##\n", packet.value7); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value8 %f ##\n", packet.value8); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value9 %f ##\n", packet.value9); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value10 %f ##\n", packet.value10); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value11 %f ##\n", packet.value11); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value12 %f ##\n", packet.value12); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value13 %f ##\n", packet.value13); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value14 %f ##\n", packet.value14); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value15 %f ##\n", packet.value15); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value16 %f ##\n", packet.value16); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value17 %f ##\n", packet.value17); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value18 %f ##\n", packet.value18); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value19 %f ##\n", packet.value19); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F value20 %f ##\n", packet.value20); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_AQ_TELEMETRY_F Index %i ##\n", packet.Index); //UINT16_T
			} else {
				mavlink_sensor_offsets_t packet;
				mavlink_msg_sensor_offsets_decode(msg, &packet);
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_SENSOR_OFFSETS mag_declination %f ##\n", packet.mag_declination); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_SENSOR_OFFSETS raw_press %i ##\n", packet.raw_press); //INT32_T
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_SENSOR_OFFSETS raw_temp %i ##\n", packet.raw_temp); //INT32_T
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_SENSOR_OFFSETS gyro_cal_x %f ##\n", packet.gyro_cal_x); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_SENSOR_OFFSETS gyro_cal_y %f ##\n", packet.gyro_cal_y); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_SENSOR_OFFSETS gyro_cal_z %f ##\n", packet.gyro_cal_z); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_SENSOR_OFFSETS accel_cal_x %f ##\n", packet.accel_cal_x); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_SENSOR_OFFSETS accel_cal_y %f ##\n", packet.accel_cal_y); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_SENSOR_OFFSETS accel_cal_z %f ##\n", packet.accel_cal_z); //FLOAT
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_SENSOR_OFFSETS mag_ofs_x %i ##\n", packet.mag_ofs_x); //INT16_T
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_SENSOR_OFFSETS mag_ofs_y %i ##\n", packet.mag_ofs_y); //INT16_T
				SDL_Log("mavlink: ## MAVLINK_MSG_ID_SENSOR_OFFSETS mag_ofs_z %i ##\n", packet.mag_ofs_z); //INT16_T
			}
*/
			break;
		}
		case MAVLINK_MSG_ID_PARAM_SET: {
			mavlink_param_set_t packet;
			mavlink_msg_param_set_decode(msg, &packet);
//			SDL_Log("mavlink: ## MAVLINK_MSG_ID_PARAM_SET param_value %f ##\n", packet.param_value); //FLOAT
//			SDL_Log("mavlink: ## MAVLINK_MSG_ID_PARAM_SET target_system %i ##\n", packet.target_system); //UINT8_T
//			SDL_Log("mavlink: ## MAVLINK_MSG_ID_PARAM_SET target_component %i ##\n", packet.target_component); //UINT8_T
//			SDL_Log("mavlink: ## MAVLINK_MSG_ID_PARAM_SET param_id %s ##\n", packet.param_id); //CHAR
//			SDL_Log("mavlink: ## MAVLINK_MSG_ID_PARAM_SET param_type %i ##\n", packet.param_type); //UINT8_T
			break;
		}
		case MAVLINK_MSG_ID_SIMSTATE: {
			mavlink_simstate_t packet;
			mavlink_msg_simstate_decode(msg, &packet);
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SIMSTATE roll %f ##\n", packet.roll); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SIMSTATE pitch %f ##\n", packet.pitch); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SIMSTATE yaw %f ##\n", packet.yaw); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SIMSTATE xacc %f ##\n", packet.xacc); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SIMSTATE yacc %f ##\n", packet.yacc); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SIMSTATE zacc %f ##\n", packet.zacc); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SIMSTATE xgyro %f ##\n", packet.xgyro); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SIMSTATE ygyro %f ##\n", packet.ygyro); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SIMSTATE zgyro %f ##\n", packet.zgyro); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SIMSTATE lat %i ##\n", packet.lat); //INT32_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SIMSTATE lng %i ##\n", packet.lng); //INT32_T
*/
			break;
		}
		case MAVLINK_MSG_ID_TERRAIN_REPORT: {
			mavlink_terrain_report_t packet;
			mavlink_msg_terrain_report_decode(msg, &packet);
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REPORT lat %i ##\n", packet.lat); //INT32_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REPORT lon %i ##\n", packet.lon); //INT32_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REPORT terrain_height %f ##\n", packet.terrain_height); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REPORT current_height %f ##\n", packet.current_height); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REPORT spacing %i ##\n", packet.spacing); //UINT16_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REPORT pending %i ##\n", packet.pending); //UINT16_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REPORT loaded %i ##\n", packet.loaded); //UINT16_T
*/
			break;
		}
		case MAVLINK_MSG_ID_TERRAIN_REQUEST: {
			mavlink_terrain_request_t packet;
			mavlink_msg_terrain_request_decode(msg, &packet);
/*
			static uint64_t send_mask = 0;

			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REQUEST mask %llu ##\n", packet.mask); //UINT64_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REQUEST lat %i ##\n", packet.lat); //INT32_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REQUEST lon %i ##\n", packet.lon); //INT32_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REQUEST grid_spacing %i ##\n", packet.grid_spacing); //UINT16_T

			int n = 0;
			int bit = 0;
			for (bit = 0; bit < 56; bit++) {
				if ((packet.mask & (1<<bit)) && !(send_mask & (1<<bit))) {
					SDL_Log("######### bit %i %llu\n", bit, send_mask);
					send_mask |= (1<<bit);
					int bit_spacing = packet.grid_spacing * 4;
					int east = bit_spacing * (bit % 8);
					int north = bit_spacing * (bit / 8);
					SDL_Log("############## %i %i %i\n", bit_spacing, east, north);
					int16_t data[16];
					float lat = packet.lat / 10000000.0;
					float lon = packet.lon / 10000000.0;
					float alt = 0;
					latlong_offset(&lat, &lon, &alt, north, east, 0);
					for (n = 0; n < (4 * 4); n++) {
						int y = n % 4;
						int x = n / 4;
						int east2 = packet.grid_spacing * y;
						int north2 = packet.grid_spacing * x;
						SDL_Log("############## %i %i %i\n", bit_spacing, east2, north2);
						float lat2 = lat;
						float lon2 = lon;
						float alt2 = alt;
						latlong_offset(&lat2, &lon2, &alt2, north2, east2, 0);
						data[n] = get_altitude(lat2, lon2);
					}
					mavlink_message_t msg_s;
					mavlink_msg_terrain_data_pack(127, 0, &msg_s, lat, lon, packet.grid_spacing, bit, data);
					mavlink_send_message(modelid, &msg_s);
				}
			}
*/
			break;
		}
		case MAVLINK_MSG_ID_LOCAL_POSITION_NED: {
			mavlink_local_position_ned_t packet;
			mavlink_msg_local_position_ned_decode(msg, &packet);
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_LOCAL_POSITION_NED time_boot_ms %i ##\n", packet.time_boot_ms); //UINT32_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_LOCAL_POSITION_NED x %f ##\n", packet.x); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_LOCAL_POSITION_NED y %f ##\n", packet.y); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_LOCAL_POSITION_NED z %f ##\n", packet.z); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_LOCAL_POSITION_NED vx %f ##\n", packet.vx); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_LOCAL_POSITION_NED vy %f ##\n", packet.vy); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_LOCAL_POSITION_NED vz %f ##\n", packet.vz); //FLOAT
* */
			break;
		}
		case MAVLINK_MSG_ID_AIRSPEED_AUTOCAL: {
			mavlink_airspeed_autocal_t packet;
			mavlink_msg_airspeed_autocal_decode(msg, &packet);
/*
 			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AIRSPEED_AUTOCAL vx %f ##\n", packet.vx); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AIRSPEED_AUTOCAL vy %f ##\n", packet.vy); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AIRSPEED_AUTOCAL vz %f ##\n", packet.vz); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AIRSPEED_AUTOCAL diff_pressure %f ##\n", packet.diff_pressure); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AIRSPEED_AUTOCAL EAS2TAS %f ##\n", packet.EAS2TAS); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AIRSPEED_AUTOCAL ratio %f ##\n", packet.ratio); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AIRSPEED_AUTOCAL state_x %f ##\n", packet.state_x); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AIRSPEED_AUTOCAL state_y %f ##\n", packet.state_y); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AIRSPEED_AUTOCAL state_z %f ##\n", packet.state_z); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AIRSPEED_AUTOCAL Pax %f ##\n", packet.Pax); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AIRSPEED_AUTOCAL Pby %f ##\n", packet.Pby); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AIRSPEED_AUTOCAL Pcz %f ##\n", packet.Pcz); //FLOAT
*/
			break;
		}
		case MAVLINK_MSG_ID_COMMAND_ACK: {
			mavlink_command_ack_t packet;
			mavlink_msg_command_ack_decode(msg, &packet);
			SDL_Log("mavlink(%i): ## MAVLINK_MSG_ID_COMMAND_ACK command %i ##\n", modelid, packet.command); //UINT16_T
			if (packet.result == MAV_RESULT_ACCEPTED) {
				SDL_Log("mavlink(%i): ## MAVLINK_MSG_ID_COMMAND_ACK result %i: ACCEPTED ##\n", modelid, packet.result); //UINT8_T
			} else if (packet.result == MAV_RESULT_TEMPORARILY_REJECTED) {
				SDL_Log("mavlink(%i): ## MAVLINK_MSG_ID_COMMAND_ACK result %i: TEMPORARILY_REJECTED ##\n", modelid, packet.result); //UINT8_T
			} else if (packet.result == MAV_RESULT_DENIED) {
				SDL_Log("mavlink(%i): ## MAVLINK_MSG_ID_COMMAND_ACK result %i: DENIED ##\n", modelid, packet.result); //UINT8_T
			} else if (packet.result == MAV_RESULT_UNSUPPORTED) {
				SDL_Log("mavlink(%i): ## MAVLINK_MSG_ID_COMMAND_ACK result %i: UNSUPPORTED ##\n", modelid, packet.result); //UINT8_T
			} else if (packet.result == MAV_RESULT_FAILED) {
				SDL_Log("mavlink(%i): ## MAVLINK_MSG_ID_COMMAND_ACK result %i: FAILED ##\n", modelid, packet.result); //UINT8_T
			} else {
				SDL_Log("mavlink(%i): ## MAVLINK_MSG_ID_COMMAND_ACK result %i: UNKNOWN ##\n", modelid, packet.result); //UINT8_T
			}
			break;
		}
		default: {
			SDL_Log("mavlink(%i): ## UNSUPPORTED MSG_ID == %i (mavlink/get_case_by_file.sh %i) ##\n", modelid, msg->msgid, msg->msgid);
			break;
		}
	}
}

void mavlink_send_terrain_data (uint8_t modelid, int32_t lat, int32_t lon, uint16_t grid_spacing, uint8_t gridbit, int16_t data[16]) {
	SDL_Log("mavlink(%i): sending terrain_data\n", modelid);
	mavlink_message_t msg;
	mavlink_msg_terrain_data_pack(127, 0, &msg, lat, lon, grid_spacing, gridbit, data);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_magcal (uint8_t modelid, float x, float y, float z) {
	SDL_Log("mavlink(%i): save magcal (%f,%f,%f)\n", modelid, x, y, z);
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_CMD_PREFLIGHT_SET_SENSOR_OFFSETS, 1, 2.0, x, y, z, 0.0, 0.0, 0.0);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_magcal2 (uint8_t modelid, float x, float y, float z) {
	SDL_Log("mavlink(%i): save magcal (%f,%f,%f)\n", modelid, x, y, z);
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_CMD_PREFLIGHT_SET_SENSOR_OFFSETS, 1, 5.0, x, y, z, 0.0, 0.0, 0.0);
	mavlink_send_message(modelid, &msg);
}

void mavlink_read_waypoints (uint8_t modelid) {
	SDL_Log("mavlink(%i): reading Waypoints\n", modelid);
	mavlink_message_t msg;
	mavlink_msg_mission_request_list_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid);
	mavlink_send_message(modelid, &msg);
}

void mavlink_read_loglist (uint8_t modelid) {
	int n = 0;
	SDL_Log("mavlink(%i): reading loglist\n", modelid);
	mavlink_logs_total = 0;
	for (n = 0; n < 255; n++) {
		loglist[n].id = 0;
		loglist[n].size = 0;
	}
	mavlink_message_t msg;
	mavlink_msg_log_request_list_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, 0, 0xffff);
	mavlink_send_message(modelid, &msg);
}

void mavlink_read_logfile (uint8_t modelid, uint16_t id, uint32_t offset, uint32_t len) {
	char tmp_str[1024];
	sprintf(tmp_str, "/tmp/mavlink_%i_%i.log", id, len);
	FILE *fdlog = fopen(tmp_str, "w");
	fclose(fdlog);
	mavlink_loggetsize = 0;
	mavlink_logstartstamp = 0;
	mavlink_logreqsize = len;
	mavlink_loghbeat = 100;
	SDL_Log("mavlink(%i): get logfile: %i (%ibytes)\n", modelid, id, len);
	mavlink_message_t msg;
	mavlink_msg_log_request_data_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, id, offset, len);
	mavlink_send_message(modelid, &msg);
}

void mavlink_save_to_flash (uint8_t modelid) {
	SDL_Log("mavlink(%i): save values to flash\n", modelid);
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_CMD_PREFLIGHT_STORAGE, 0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	mavlink_send_message(modelid, &msg);
}

void mavlink_load_from_flash (uint8_t modelid) {
	SDL_Log("mavlink(%i): load values from flash\n", modelid);
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_CMD_PREFLIGHT_STORAGE, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_cmd_calibration (uint8_t modelid) {
	SDL_Log("mavlink(%i): send cmd: Calibration ACC\n", modelid);
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_CMD_PREFLIGHT_CALIBRATION, 0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_cmd_calibration_mag_aq (uint8_t modelid) {
	SDL_Log("mavlink(%i): send cmd: Calibration MAG(AQ)\n", modelid);
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_CMD_PREFLIGHT_CALIBRATION, 0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_cmd_calibration_ack (uint8_t modelid) {
	SDL_Log("mavlink(%i): send cmd: Calibration ACK\n", modelid);
	mavlink_message_t msg;
	mavlink_msg_command_ack_pack(127, 0, &msg, MAV_CMD_PREFLIGHT_CALIBRATION, MAV_CMD_ACK_OK);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_cmd_rtl (uint8_t modelid) {
	SDL_Log("mavlink(%i): send cmd: RTL\n", modelid);
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_CMD_NAV_RETURN_TO_LAUNCH, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_cmd_land (uint8_t modelid) {
	SDL_Log("mavlink(%i): send cmd: LAND\n", modelid);
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_CMD_NAV_LAND, 0, 0.0, 0.0, 0.0, 0.0, ModelData[modelid].p_lat, ModelData[modelid].p_long, ModelData[modelid].p_alt);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_cmd_takeoff (uint8_t modelid) {
	SDL_Log("mavlink(%i): send cmd: TAKEOFF\n", modelid);
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_CMD_NAV_TAKEOFF, 0, 0.0, 0.0, 0.0, 0.0, ModelData[modelid].p_lat, ModelData[modelid].p_long, ModelData[modelid].p_alt);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_cmd_mission (uint8_t modelid) {
	SDL_Log("mavlink(%i): send cmd: MISSION\n", modelid);
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_CMD_MISSION_START, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_cmd_arm (uint8_t modelid, uint8_t mode) {
	SDL_Log("mavlink(%i): send cmd: ARM: %i\n", modelid, mode);
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_CMD_COMPONENT_ARM_DISARM, 0, (float)mode, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_cmd_mode (uint8_t modelid, uint8_t mode) {
	SDL_Log("mavlink(%i): send cmd: MODE: %i\n", modelid, mode);
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_CMD_DO_SET_MODE, 0, (float)mode, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_cmd_guided (uint8_t modelid) {
	SDL_Log("mavlink(%i): send cmd: GUIDED\n", modelid);
	mavlink_message_t msg;
	mavlink_msg_set_mode_pack(127, 0, &msg, ModelData[modelid].sysid, MAV_MODE_FLAG_CUSTOM_MODE_ENABLED, 4);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_cmd_loiter (uint8_t modelid) {
	SDL_Log("mavlink(%i): send cmd: LOITER\n", modelid);
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_CMD_NAV_LOITER_UNLIM, 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_cmd_yaw (uint8_t modelid, float yaw, float rate) {
	mavlink_message_t msg;
	mavlink_msg_mission_item_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, 0, MAV_FRAME_GLOBAL_RELATIVE_ALT, MAV_CMD_CONDITION_YAW, 2, 0, yaw, rate, 1.0, 0.0, 0.0, 0.0, 0.0);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_cmd_follow (uint8_t modelid, float p_lat, float p_long, float p_alt, float radius) {
	mavlink_message_t msg;
	ModelData[modelid].next_lat = p_lat;
	ModelData[modelid].next_long = p_long;
	ModelData[modelid].next_alt = p_alt;
	ModelData[modelid].next_count = 1000;
	mavlink_msg_mission_item_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, 0, MAV_FRAME_GLOBAL_RELATIVE_ALT, MAV_CMD_NAV_WAYPOINT, 2, 0, 0.0, radius, 0.0, 0.0, p_lat, p_long, p_alt);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_waypoints (uint8_t modelid) {
	mavlink_message_t msg;
	mavlink_msg_mission_clear_all_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid);
	mavlink_send_message(modelid, &msg);
	usleep(100000);
	uint16_t n = 0;
	for (n = 1; n < MAX_WAYPOINTS; n++) {
		if (WayPoints[modelid][n].p_lat == 0.0) {
			break;
		}
	}
	if (ModelData[modelid].teletype == TELETYPE_MEGAPIRATE_NG || ModelData[modelid].teletype == TELETYPE_ARDUPILOT) {
		SDL_Log("mavlink(%i): WORKAROUND: MEGAPIRATE_NG: fake one WP\n", modelid);
		n++;
	}
	SDL_Log("mavlink(%i): sending Waypoints (%i)\n", modelid, n - 1);
	mavlink_msg_mission_count_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, n - 1);
	mavlink_send_message(modelid, &msg);
}

void mavlink_send_message (uint8_t modelid, mavlink_message_t* msg) {
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	uint16_t len = mavlink_msg_to_send_buffer(buf, msg);
	uint16_t i = 0;
	for(i = 0; i < len; i++) {
		uint8_t c = buf[i];
		serial_write(ModelData[modelid].serial_fd, &c, 1);
	}
#ifndef WINDOWS
	if (mavlink_udp_active == 1) {
		if (strcmp(ModelData[modelid].telemetry_port, "UDP") == 0) {
			if (sendto(s, buf, len, 0, (struct sockaddr *)&si_other, slen) == -1) {
				SDL_Log("mavlink(%i): error: sendto udp()\n", modelid);
			}
		}
	}
	if (mavlink_tcp_active == 1) {
		if (strcmp(ModelData[modelid].telemetry_port, "TCP") == 0) {
			mavlink_tcp_send(modelid, buf, len);
		}
	}
#endif
}

uint8_t mavlink_connection_status (uint8_t modelid) {
	if (ModelData[modelid].serial_fd == -1) {
		return 0;
	}
	return last_connection[modelid];
}

void mavlink_update (uint8_t modelid) {
	ModelData[modelid].serial_fd = serial_check(ModelData[modelid].serial_fd);
	if (ModelData[modelid].serial_fd == -1) {
		return;
	}
	uint8_t c = 0;
	uint16_t n = 0;
	mavlink_message_t msg;
	mavlink_status_t status;
	while ((res = serial_read(ModelData[modelid].serial_fd, serial_buf, 1000)) > 0) {
		last_connection[modelid] = time(0);
		for (n = 0; n < res; n++) {
			c = serial_buf[n];
			if(mavlink_parse_char(modelid, c, &msg, &status)) {
				mavlink_handleMessage(modelid, &msg);
			}
		}
	}
}

void mavlink_param_get_id (uint8_t modelid, uint16_t id) {
	SDL_Log("mavlink(%i): get param id: %i\n", modelid, id);
	mavlink_message_t msg;
	mavlink_msg_param_request_read_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, NULL, id);
	mavlink_send_message(modelid, &msg);
}

void mavlink_start_feeds (uint8_t modelid) {
	mavlink_message_t msg;
	mavlink_timeout[modelid] = 0;
	param_complete[modelid] = 0;

	SDL_Log("mavlink(%i): starting feeds\n", modelid);
//	if (ModelData[modelid].get_param == 1) {
		mavlink_msg_param_request_list_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid);
		mavlink_send_message(modelid, &msg);
		SDL_Delay(30);
//	}

	mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_DATA_STREAM_RAW_SENSORS, MAV_DATA_STREAM_RAW_SENSORS_RATE, MAV_DATA_STREAM_RAW_SENSORS_ACTIVE);
	mavlink_send_message(modelid, &msg);
	SDL_Delay(30);

	mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_DATA_STREAM_RC_CHANNELS, MAV_DATA_STREAM_RC_CHANNELS_RATE, MAV_DATA_STREAM_RC_CHANNELS_ACTIVE);
	mavlink_send_message(modelid, &msg);
	SDL_Delay(30);

	if (ModelData[modelid].pilottype == MAV_AUTOPILOT_AUTOQUAD) {
		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_DATA_STREAM_EXTRA1, MAV_DATA_STREAM_EXTRA1_RATE, MAV_DATA_STREAM_EXTRA1_ACTIVE);
		mavlink_send_message(modelid, &msg);
		SDL_Delay(30);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_DATA_STREAM_EXTRA2, MAV_DATA_STREAM_EXTRA2_RATE, MAV_DATA_STREAM_EXTRA2_ACTIVE);
		mavlink_send_message(modelid, &msg);
		SDL_Delay(30);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_DATA_STREAM_EXTRA3, MAV_DATA_STREAM_EXTRA3_RATE, MAV_DATA_STREAM_EXTRA3_ACTIVE);
		mavlink_send_message(modelid, &msg);
		SDL_Delay(30);

//		mavlink_msg_command_long_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, \
//			MAV_CMD_AQ_TELEMETRY, 1, 1.0, 100000.0, AQMAV_DATASET_SUPERVISOR, 0.0, 0.0, 0.0, 0.0);

		mavlink_send_message(modelid, &msg);
		SDL_Delay(30);


	} else if (ModelData[modelid].teletype == TELETYPE_MEGAPIRATE_NG || ModelData[modelid].teletype == TELETYPE_ARDUPILOT || ModelData[modelid].teletype == TELETYPE_HARAKIRIML) {
		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_DATA_STREAM_EXTENDED_STATUS, MAV_DATA_STREAM_EXTENDED_STATUS_RATE, MAV_DATA_STREAM_EXTENDED_STATUS_ACTIVE);
		mavlink_send_message(modelid, &msg);
		SDL_Delay(30);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_DATA_STREAM_RAW_CONTROLLER, MAV_DATA_STREAM_RAW_CONTROLLER_RATE, MAV_DATA_STREAM_RAW_CONTROLLER_ACTIVE);
		mavlink_send_message(modelid, &msg);
		SDL_Delay(30);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_DATA_STREAM_POSITION, MAV_DATA_STREAM_POSITION_RATE, MAV_DATA_STREAM_POSITION_ACTIVE);
		mavlink_send_message(modelid, &msg);
		SDL_Delay(30);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_DATA_STREAM_EXTRA1, MAV_DATA_STREAM_EXTRA1_RATE, MAV_DATA_STREAM_EXTRA1_ACTIVE);
		mavlink_send_message(modelid, &msg);
		SDL_Delay(30);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_DATA_STREAM_EXTRA2, MAV_DATA_STREAM_EXTRA2_RATE, MAV_DATA_STREAM_EXTRA2_ACTIVE);
		mavlink_send_message(modelid, &msg);
		SDL_Delay(30);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData[modelid].sysid, ModelData[modelid].compid, MAV_DATA_STREAM_EXTRA3, MAV_DATA_STREAM_EXTRA3_RATE, MAV_DATA_STREAM_EXTRA3_ACTIVE);
		mavlink_send_message(modelid, &msg);
		SDL_Delay(30);
	}
}

void mavlink_parseParams1 (uint8_t modelid, xmlDocPtr doc, xmlNodePtr cur, char *name) { 
	int n = 0;
	int n2 = 0;
	int n3 = 0;
	int n4 = 0;
	char tmp_str3[1024];
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[modelid][n].name, name) == 0) {
			break;
		}
	}
	if (n == MAVLINK_PARAMETER_MAX) {
		return;
	}
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Range"))) {
			float min = 0.0;
			float max = 0.0;
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				sscanf((char *)key, "%f %f", &min, &max);
				MavLinkVars[modelid][n].min = min;
				MavLinkVars[modelid][n].max = max;
				if (MavLinkVars[modelid][n].min > MavLinkVars[modelid][n].value) {
					MavLinkVars[modelid][n].min = MavLinkVars[modelid][n].value;
				}
				if (MavLinkVars[modelid][n].max < MavLinkVars[modelid][n].value) {
					MavLinkVars[modelid][n].max = MavLinkVars[modelid][n].value;
				}
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Description"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[modelid][n].desc, (char *)key, 1023);
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Group"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[modelid][n].group, (char *)key, 20);
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Values"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[modelid][n].values, (char *)key, 1023);
				if (MavLinkVars[modelid][n].values[0] != 0) {
					MavLinkVars[modelid][n].min = atof(MavLinkVars[modelid][n].values);
					for (n2 = 0; n2 < strlen(MavLinkVars[modelid][n].values); n2++) {
						if (MavLinkVars[modelid][n].values[n2] == ',') {
							strncpy(tmp_str3, MavLinkVars[modelid][n].values + n3, 1023);
							for (n4 = 0; n4 < strlen(tmp_str3); n4++) {
								if (tmp_str3[n4] == ',') {
									tmp_str3[n4] = 0;
									break;
								}
							}
							n3 = n2 + 1;
						}
					}
					strncpy(tmp_str3, MavLinkVars[modelid][n].values + n3, 1023);
					MavLinkVars[modelid][n].max = atof(tmp_str3);
				}
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Bits"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[modelid][n].bits, (char *)key, 1023);
				if (MavLinkVars[modelid][n].bits[0] != 0) {
					MavLinkVars[modelid][n].min = 0;
					for (n2 = 0; n2 < strlen(MavLinkVars[modelid][n].bits); n2++) {
						if (MavLinkVars[modelid][n].bits[n2] == ',') {
							strncpy(tmp_str3, MavLinkVars[modelid][n].bits + n3, 1023);
							for (n4 = 0; n4 < strlen(tmp_str3); n4++) {
								if (tmp_str3[n4] == ',') {
									tmp_str3[n4] = 0;
									break;
								}
							}
							n3 = n2 + 1;
						}
					}
					strncpy(tmp_str3, MavLinkVars[modelid][n].bits + n3, 1023);
					MavLinkVars[modelid][n].max = (float)((1<<atoi(tmp_str3)) * (1<<atoi(tmp_str3)) - 1);
				}
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"DisplayName"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[modelid][n].display, (char *)key, 100);
				xmlFree(key);
			}
		}
		cur = cur->next;
	}
	return;
}

void mavlink_parseParamsGetAttr (uint8_t modelid, xmlDocPtr doc, xmlNodePtr cur, char *attrName, char *attrValue) {
	xmlAttrPtr attribute = NULL;
	for (attribute = cur->properties; attribute != NULL; attribute = attribute->next){
		if (!(xmlStrcasecmp(attribute->name, (const xmlChar *)attrName))) {
			xmlChar *content = xmlNodeListGetString(doc, attribute->children, 1);
			strcpy(attrValue, (char *)content);
			xmlFree(content);
			return;
		}
	}
	attrValue[0] = 0;
}

size_t trimline (char *out, size_t len, const char *str) {
	if(len == 0) {
		return 0;
	}
	const char *end;
	size_t out_size;
	while (*str == ' ' || *str == '\r' || *str == '\n') {
		str++;
	}
	if (*str == 0) {
		*out = 0;
		return 1;
	}
	end = str + strlen(str) - 1;
	while(end > str && (*end == ' ' || *end == '\r' || *end == '\n')) {
		end--;
	}
	end++;
	out_size = (end - str) < (int)len - 1 ? (end - str) : len - 1;
	memcpy(out, str, out_size);
	out[out_size] = 0;
	return out_size;
}

void mavlink_parseParams1New (uint8_t modelid, xmlDocPtr doc, xmlNodePtr cur, char *name, char *disp, char *desc) { 
	int n = 0;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[modelid][n].name, name) == 0) {
			break;
		}
	}
	if (n == MAVLINK_PARAMETER_MAX) {
		return;
	}
	strncpy(MavLinkVars[modelid][n].desc, (char *)desc, 1023);
	strncpy(MavLinkVars[modelid][n].display, (char *)disp, 100);
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		char attrValue[1024];
		mavlink_parseParamsGetAttr(modelid, doc, cur, "Name", attrValue);
		if ((!xmlStrcasecmp((const xmlChar *)attrValue, (const xmlChar *)"Range"))) {
			float min = 0.0;
			float max = 0.0;
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				sscanf((char *)key, "%f %f", &min, &max);
				MavLinkVars[modelid][n].min = min;
				MavLinkVars[modelid][n].max = max;
				if (MavLinkVars[modelid][n].min > MavLinkVars[modelid][n].value) {
					MavLinkVars[modelid][n].min = MavLinkVars[modelid][n].value;
				}
				if (MavLinkVars[modelid][n].max < MavLinkVars[modelid][n].value) {
					MavLinkVars[modelid][n].max = MavLinkVars[modelid][n].value;
				}
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp((const xmlChar *)attrValue, (const xmlChar *)"Group"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[modelid][n].group, (char *)key, 20);
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Values"))) {
			float last_val = 0.0;
			MavLinkVars[modelid][n].values[0] = 0;
			xmlNodePtr cur2 = cur->xmlChildrenNode;
			while (cur2 != NULL) {
				if (!(xmlStrcasecmp(cur2->name, (const xmlChar *)"Value"))) {
					xmlChar *key;
					key = xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
					if (key != NULL) {
						char Value[1024];
						char Value2[1024];
						mavlink_parseParamsGetAttr(modelid, doc, cur2, "Code", Value);
						trimline(Value2, 1024, Value);
						last_val = atof(Value2);
						if (MavLinkVars[modelid][n].values[0] == 0) {
							MavLinkVars[modelid][n].min = last_val;
						} else {
							strcat(MavLinkVars[modelid][n].values, ",");
						}
						strcat(MavLinkVars[modelid][n].values, Value2);
						strcat(MavLinkVars[modelid][n].values, ":");
						strcat(MavLinkVars[modelid][n].values, (char *)key);
						xmlFree(key);
					}
				}
				cur2 = cur2->next;
			}
			MavLinkVars[modelid][n].max = last_val;
		}
		cur = cur->next;
	}
	return;
}

void mavlink_parseParamsNew (uint8_t modelid, xmlDocPtr doc, xmlNodePtr cur) { 
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if (!(xmlStrcasecmp(cur->name, (const xmlChar *)"param"))) {
			char attrValue[1024];
			char Desc[1024];
			char Disp[1024];
			mavlink_parseParamsGetAttr(modelid, doc, cur, "Name", attrValue);
			mavlink_parseParamsGetAttr(modelid, doc, cur, "Documentation", Desc);
			mavlink_parseParamsGetAttr(modelid, doc, cur, "humanName", Disp);
			if (strncmp(attrValue, "ArduCopter:", 11) == 0) {
				mavlink_parseParams1New(modelid, doc, cur, attrValue + 11, Disp, Desc);
			}
		}
		cur = cur->next;
	}
	return;
}

void mavlink_parseParams (uint8_t modelid, xmlDocPtr doc, xmlNodePtr cur) { 
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if (!(xmlStrcasecmp(cur->name, (const xmlChar *)"parameters"))) {
			mavlink_parseParamsNew(modelid, doc, cur);
		} else if ((xmlStrcasecmp(cur->name, (const xmlChar *)"text"))) {
			mavlink_parseParams1(modelid, doc, cur, (char *)cur->name);
		}
		cur = cur->next;
	}
	return;
}

static void mavlink_parseDoc (uint8_t modelid, char *docname) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	if (strncmp(docname, "./", 2) == 0) {
		docname += 2;
	}
	char *buffer = NULL;
	int len = 0;
	SDL_RWops *ops_file = SDL_RWFromFile(docname, "r");
	if (ops_file == NULL) {
		SDL_Log("mavlink(%i): Document open failed: %s\n", modelid, docname);
		return;
	}
	len = SDL_RWseek(ops_file, 0, SEEK_END);
	SDL_RWseek(ops_file, 0, SEEK_SET);
	buffer = malloc(len);
	SDL_RWread(ops_file, buffer, 1, len);
	doc = xmlParseMemory(buffer, len);
	SDL_RWclose(ops_file);
	free(buffer);
	if (doc == NULL) {
		SDL_Log("mavlink(%i): Document parsing failed: %s\n", modelid, docname);
		return;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		xmlFreeDoc(doc);
		SDL_Log("mavlink(%i): Document is Empty!!!\n", modelid);
		return;
	}
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((xmlStrcasecmp(cur->name, (const xmlChar *)"vehicles")) == 0) {
			mavlink_parseParams(modelid, doc, cur);
		} else if ((xmlStrcasecmp(cur->name, (const xmlChar *)"ArduCopter2")) == 0) {
			mavlink_parseParams(modelid, doc, cur);
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}

void mavlink_param_xml_meta_load (uint8_t modelid) {
	char filename[1024];
	sprintf(filename, "%s/mavlink/ParameterMetaData-%s.xml", get_datadirectory(), teletypes[ModelData[modelid].teletype]);
	if (file_exists(filename) != 0) {
		mavlink_parseDoc(modelid, filename);
		return;
	}
	sprintf(filename, "%s/mavlink/ParameterMetaData-%s.xml", BASE_DIR, teletypes[ModelData[modelid].teletype]);
	if (file_exists(filename) != 0) {
		mavlink_parseDoc(modelid, filename);
		return;
	}
}

static void model_parseMavlinkParam (uint8_t modelid, xmlDocPtr doc, xmlNodePtr cur, uint16_t param) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"name"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				strncpy(MavLinkVars[modelid][param].name, (char *)key, 20);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"value"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				MavLinkVars[modelid][param].value = atof((char *)key);
				MavLinkVars[modelid][param].onload = atof((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

void mavlink_xml_load (uint8_t modelid, xmlDocPtr doc, xmlNodePtr cur) { 
	uint16_t param = 0;
	for (param = 0; param < MAVLINK_PARAMETER_MAX; param++) {
		MavLinkVars[modelid][param].name[0] = 0;
		MavLinkVars[modelid][param].group[0] = 0;
		MavLinkVars[modelid][param].value = 0.0;
		MavLinkVars[modelid][param].onload = 0.0;
	}
	param = 0;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"param"))) {
			model_parseMavlinkParam (modelid, doc, cur, param++);
		}
		cur = cur->next;
	}
	return;
}

static void mavlink_html_page (uint8_t modelid, char *content, char *sub) {
	char tmp_str[512];
	char tmp_str2[512];
	uint16_t n = 0;
	uint16_t n2 = 0;
	content[0] = 0;
	webserv_html_head(content, "MAVLINK");
	strcat(content, "<SCRIPT>\n");
	strcat(content, "function check_option(name) {\n");
	strcat(content, "	var value = document.getElementById(name).options[document.getElementById(name).selectedIndex].value;\n");
	strcat(content, "	xmlHttp = new XMLHttpRequest();\n");
	strcat(content, "	xmlHttp.open(\"GET\", \"/mavlink_value_set?\" + name + \"=\" + value, true);\n");
	strcat(content, "	xmlHttp.send(null);\n");
	strcat(content, "}\n");
	strcat(content, "function check_value(name) {\n");
	strcat(content, "	var value = document.getElementById(name).value;\n");
	strcat(content, "	xmlHttp = new XMLHttpRequest();\n");
	strcat(content, "	xmlHttp.open(\"GET\", \"/mavlink_value_set?\" + name + \"=\" + value, true);\n");
	strcat(content, "	xmlHttp.send(null);\n");
	strcat(content, "}\n");
	strcat(content, "</SCRIPT>\n");
	webserv_html_start(content, 0);
	strcat(content, "<TABLE class=\"main\">\n");
	strcat(content, "<TR class=\"main\"><TD width=\"160px\" valign=\"top\">\n");
	strcat(content, "<TABLE width=\"100%\">\n");
	strcat(content, "<TR class=\"thead\"><TH>MODE</TH></TR>\n");
	strcat(content, "<TR class=\"first\"><TD><A href=\"/mavlink.html\">ALL</A></TD></TR>");
	uint8_t flag = 0;
	char mavlink_subs[512][128];
	for (n2 = 0; n2 < MAVLINK_PARAMETER_MAX; n2++) {
		mavlink_subs[n2][0] = 0;
	}
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (MavLinkVars[modelid][n].name[0] != 0) {
			strcpy(tmp_str, MavLinkVars[modelid][n].name);
			if (MavLinkVars[modelid][n].group[0] == 0) {
				for (n2 = 0; n2 < strlen(tmp_str) && n2 < 6; n2++) {
					if (tmp_str[n2] == '_') {
						break;
					}
				}
				strncpy(MavLinkVars[modelid][n].group, tmp_str, 17);
			}
			flag = 0;
			for (n2 = 0; n2 < MAVLINK_PARAMETER_MAX; n2++) {
				if (strcmp(mavlink_subs[n2], MavLinkVars[modelid][n].group) == 0) {
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				if (strcmp(MavLinkVars[modelid][n].group, sub) == 0) {
					sprintf(tmp_str2, "<TR class=\"sec\"><TD><A href=\"/mavlink.html?%s\">%s</A></TD></TR>", MavLinkVars[modelid][n].group, MavLinkVars[modelid][n].group);
				} else {
					sprintf(tmp_str2, "<TR class=\"first\"><TD><A href=\"/mavlink.html?%s\">%s</A></TD></TR>", MavLinkVars[modelid][n].group, MavLinkVars[modelid][n].group);
				}
				strcat(content, tmp_str2);
				for (n2 = 0; n2 < MAVLINK_PARAMETER_MAX; n2++) {
					if (mavlink_subs[n2][0] == 0) {
						strcpy(mavlink_subs[n2], MavLinkVars[modelid][n].group);
						break;
					}
				}
			}
		}
	}
	strcat(content, "</TABLE><BR><BR><BR>\n");
	strcat(content, "</TD><TD valign=\"top\" width=\"20px\">&nbsp;</TD><TD valign=\"top\">\n");
	strcat(content, "<TABLE width=\"100%\" border=\"0\">\n");
	strcat(content, "<TR class=\"thead\"><TH>NAME</TH><TH>VALUE</TH><TH>DESCRIPTION</TH><TH>MIN</TH><TH>MAX</TH><TH>ONLOAD</TH></TR>\n");
	int lc = 0;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (MavLinkVars[modelid][n].name[0] != 0 && (sub[0] == 0 || strncmp(MavLinkVars[modelid][n].name, sub, strlen(sub)) == 0 || strcmp(MavLinkVars[modelid][n].group, sub) == 0)) {
			lc = 1 - lc;
			if (lc == 0) {
				strcat(content, "<TR class=\"first\">");
			} else {
				strcat(content, "<TR class=\"sec\">");
			}
			sprintf(tmp_str, "<TD>%s (%s)</TD>\n", MavLinkVars[modelid][n].name, MavLinkVars[modelid][n].display);
			strcat(content, tmp_str);
			if (MavLinkVars[modelid][n].values[0] != 0) {
				int n2 = 0;
				sprintf(tmp_str, "<TD><SELECT class=\"form-input\" onchange=\"check_option('%s');\" id=\"%s\">\n", MavLinkVars[modelid][n].name, MavLinkVars[modelid][n].name);
				strcat(content, tmp_str);
				tmp_str2[0] = 0;
				for (n2 = (int)MavLinkVars[modelid][n].min; n2 <= (int)MavLinkVars[modelid][n].max; n2++) {
					tmp_str2[0] = 0;
					mavlink_meta_get_option(n2, MavLinkVars[modelid][n].name, tmp_str2);
					if (tmp_str2[0] != 0) {
						if (n2 == (int)MavLinkVars[modelid][n].value) {
							sprintf(tmp_str, "<OPTION value=\"%i\" selected>%s</OPTION>\n", n2, tmp_str2);
						} else {
							sprintf(tmp_str, "<OPTION value=\"%i\">%s</OPTION>\n", n2, tmp_str2);
						}
						strcat(content, tmp_str);
					}
				}
				strcat(content, "</SELECT></TD>");
			} else if (MavLinkVars[modelid][n].bits[0] != 0) {
				sprintf(tmp_str, "<TD>\n");
				strcat(content, tmp_str);
				int n2 = 0;
				strcat(content, "<SCRIPT>\n");
				sprintf(tmp_str, "function check_%s() {\n", MavLinkVars[modelid][n].name);
				strcat(content, tmp_str);
				strcat(content, "	var value = 0;\n");
				tmp_str2[0] = 0;
				for (n2 = (int)MavLinkVars[modelid][n].min; n2 <= (int)MavLinkVars[modelid][n].max; n2++) {
					tmp_str2[0] = 0;
					mavlink_meta_get_bits(n2, MavLinkVars[modelid][n].name, tmp_str2);
					if (tmp_str2[0] != 0) {
						sprintf(tmp_str, "	if (document.getElementsByName(\"%s-%s\")[0].checked) {\n", MavLinkVars[modelid][n].name, tmp_str2);
						strcat(content, tmp_str);
						sprintf(tmp_str, "		value |= (1<<%i);\n", n2);
						strcat(content, tmp_str);
						strcat(content, "	}\n");
					}
				}
				strcat(content, "	xmlHttp = new XMLHttpRequest();\n");
				sprintf(tmp_str, "	xmlHttp.open(\"GET\", \"/mavlink_value_set?%s=\" + value, true);\n", MavLinkVars[modelid][n].name);
				strcat(content, tmp_str);
				strcat(content, "	xmlHttp.send(null);\n");
				strcat(content, "}\n");
				strcat(content, "</SCRIPT>\n");
				tmp_str2[0] = 0;
				for (n2 = (int)MavLinkVars[modelid][n].min; n2 <= (int)MavLinkVars[modelid][n].max; n2++) {
					tmp_str2[0] = 0;
					mavlink_meta_get_bits(n2, MavLinkVars[modelid][n].name, tmp_str2);
					if (tmp_str2[0] != 0) {
						if ((int)MavLinkVars[modelid][n].value & (1<<n2)) {
							sprintf(tmp_str, "<NOBR><INPUT class=\"form-input\" onchange=\"check_%s();\" type=\"checkbox\" name=\"%s-%s\" value=\"%i\" checked>%s</NOBR>\n", MavLinkVars[modelid][n].name, MavLinkVars[modelid][n].name, tmp_str2, n2, tmp_str2);
						} else {
							sprintf(tmp_str, "<NOBR><INPUT class=\"form-input\" onchange=\"check_%s();\" type=\"checkbox\" name=\"%s-%s\" value=\"%i\">%s</NOBR>\n", MavLinkVars[modelid][n].name, MavLinkVars[modelid][n].name, tmp_str2, n2, tmp_str2);
						}
						strcat(content, tmp_str);
					}
				}
				strcat(content, "</TD>");
			} else {
				sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('%s');\" id=\"%s\" value=\"%f\" type=\"text\"></TD>\n", MavLinkVars[modelid][n].name, MavLinkVars[modelid][n].name, MavLinkVars[modelid][n].value);
				strcat(content, tmp_str);
			}
			sprintf(tmp_str, "<TD>%s&nbsp;</TD><TD>%0.4f</TD><TD>%0.4f</TD><TD>%0.4f</TD></TR>\n", MavLinkVars[modelid][n].desc, MavLinkVars[modelid][n].min, MavLinkVars[modelid][n].max, MavLinkVars[modelid][n].onload);
			strcat(content, tmp_str);
		}
	}
	strcat(content, "</TABLE><BR><BR>\n");
	strcat(content, "</TD></TR></TABLE>\n");
	webserv_html_stop(content);
}


void mavlink_web_get (uint8_t modelid, char *url, char *content, char *type) {
	char tmp_str[512];
	if (strncmp(url, "/mavlink_value_set?", 19) == 0) {
		char name[20];
		float value = 0.0;
		int ntype = 0;
		sscanf(url + 19, "%[0-9a-zA-Z_]=%f&%i", name, &value, &ntype);
		mavlink_set_value(0, name, value, ntype, -1);
		mavlink_send_value(0, name, value, ntype);
		sprintf(content, "mavlink set value: %s to %f (type:%i)\n", name, value, ntype);
		strcpy(type, "text/plain");
	} else if (strncmp(url, "/mavlink.html?", 14) == 0) {
		char sub[128];
		sscanf(url + 14, "%[0-9a-zA-Z_]", sub);
		mavlink_html_page(modelid, content, sub);
		strcpy(type, "text/html");
	} else if (strncmp(url, "/mavlink.html", 13) == 0) {
		mavlink_html_page(modelid, content, "");
		strcpy(type, "text/html");
	} else if (strncmp(url, "/mavlink_value_get", 18) == 0) {
		uint16_t n = 0;
		strcpy(content, "# MAV ID  COMPONENT ID  PARAM NAME  VALUE (FLOAT) TYPE (INT)\n");
		for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
			if (MavLinkVars[modelid][n].name[0] != 0) {
				sprintf(tmp_str, "%i %i %s %f %i\n", ModelData[modelid].sysid, ModelData[modelid].compid, MavLinkVars[modelid][n].name, MavLinkVars[modelid][n].value, MavLinkVars[modelid][n].type);
				strcat(content, tmp_str);
			}
		}
		strcpy(type, "text/plain");
	}
}

#ifndef WINDOWS

/*
typedef struct {
	TCPsocket sock;
	char ip[16];
} Client;

int running = 1;
Client *clients = NULL;
int num_clients = 0;
TCPsocket server;


int find_client(TCPsocket sock) {
	int i;
	for (i = 0; i < num_clients; i++) {
		if (clients[i].sock == sock) {
			return(i);
		}
	}
	return(-1);
}

Client *add_client(TCPsocket sock) {
	IPaddress *ipaddr;
	clients = (Client*)realloc(clients, (num_clients+1) * sizeof(Client));
	clients[num_clients].sock = sock;
	ipaddr = SDLNet_TCP_GetPeerAddress(sock);
	if (ipaddr) {
		uint32_t ip = SDL_SwapBE32(ipaddr->host);
		sprintf(clients[num_clients].ip, "%d.%d.%d.%d", ip>>24, (ip>>16)&0xff, (ip>>8)&0xff, ip&0xff);
	} else {
		clients[num_clients].ip[0] = 0;
	}
	num_clients++;
	return (&clients[num_clients - 1]);
}

void remove_client(int i) {
	if (i < 0 && i >= num_clients) {
		return;
	}
	SDLNet_TCP_Close(clients[i].sock);
	num_clients--;
	if (num_clients > i) {
		memmove(&clients[i], &clients[i + 1], (num_clients - i) * sizeof(Client));
	}
	clients=(Client*)realloc(clients, num_clients*sizeof(Client));
}

SDLNet_SocketSet create_sockset() {
	static SDLNet_SocketSet set = NULL;
	int i = 0;
	if (set) {
		SDLNet_FreeSocketSet(set);
	}
	set = SDLNet_AllocSocketSet(num_clients + 1);
	if (!set) {
		printf("SDLNet_AllocSocketSet: %s\n", SDLNet_GetError());
		exit(1);
	}
	SDLNet_TCP_AddSocket(set,server);
	for (i = 0; i < num_clients; i++) {
		SDLNet_TCP_AddSocket(set, clients[i].sock);
	}
	return(set);
}

int mavlink_tcp_send (uint8_t modelid, uint8_t *buf, uint16_t len) {
	int i = 0;;
	if (strcmp(ModelData[modelid].telemetry_port, "TCP") == 0) {
		for (i = 0; i < num_clients; i++) {
			SDLNet_TCP_Send(clients[i].sock, buf, len);
		}
	}
	return 0;
}

int mavlink_tcp (void *data) {
	IPaddress ip;
	TCPsocket sock;
	SDLNet_SocketSet set;
	char buf[TCP_BUFLEN + 1];
	uint8_t modelid = 0;
	mavlink_message_t msg;
	mavlink_status_t status;
	int n = 0;
	Uint32 ipaddr;
	Uint16 port;
	if (SDLNet_Init() == -1) {
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		SDL_Quit();
		return 2;
	}
	port = (Uint16)strtol("9999", NULL, 0);
	if (SDLNet_ResolveHost(&ip,NULL,port) == -1) {
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		SDLNet_Quit();
		SDL_Quit();
		return 3;
	}
	ipaddr = SDL_SwapBE32(ip.host);
	printf("IP Address : %d.%d.%d.%d\n", ipaddr>>24, (ipaddr>>16)&0xff, (ipaddr>>8)&0xff, ipaddr&0xff);
	printf("Port       : %d\n",port);
	server = SDLNet_TCP_Open(&ip);
	if (!server) {
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		SDLNet_Quit();
		SDL_Quit();
		return 4;
	}
	while (tcp_running == 1) {
		int numready,i;
		set = create_sockset();
		if (SDLNet_SocketReady(set)) {
			numready = SDLNet_CheckSockets(set, (Uint32)1000);
		} else {
			continue;
		}
		if (numready == -1) {
			printf("SDLNet_CheckSockets: %s\n", SDLNet_GetError());
			break;
		}
		if (!numready) {
			continue;
		}
		if (SDLNet_SocketReady(server)) {
			numready--;
			sock = SDLNet_TCP_Accept(server);
			if (sock) {
				Client *client;
				client = add_client(sock);
				if (client) {
					printf("## new client %s\n", client->ip);
				}
			}
		}
		for (i = 0; numready && i < num_clients; i++) {
			if (SDLNet_SocketReady(clients[i].sock)) {
				Uint32 result;
				if ((result = SDLNet_TCP_Recv(clients[i].sock, buf, TCP_BUFLEN)) > 0) {
					for (modelid = 0; modelid < MODELS_MAX; modelid++) {
						if (strcmp(ModelData[modelid].telemetry_port, "TCP") == 0) {
							for (n = 0; n < result; n++) {
								if (mavlink_parse_char(modelid, buf[n], &msg, &status)) {
									if (ModelData[modelid].use_deviceid == 0 || msg.sysid == ModelData[modelid].mavlink_sysid) {
										mavlink_handleMessage(modelid, &msg);
										mavlink_tcp_active = 1;
									}
								}
							}
							break;
						}
					}
				}
			}
		}
	}
	SDLNet_Quit();
	return(0);
}

*/

int mavlink_tcp_send (uint8_t modelid, uint8_t *buf, uint16_t len) {
	send(ModelData[modelid].netsock, buf, len, 0);
	return 0;
}

int mavlink_tcp_connect (char *ip, uint16_t port) {
	int tcp_sock = -1;
    struct sockaddr_in server;
    tcp_sock = socket(AF_INET , SOCK_STREAM , 0);
    if (tcp_sock == -1) {
		SDL_Log("mavlink: Could not create tcp socket\n");
        return -1;
    }
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (connect(tcp_sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
        SDL_Log("mavlink: tcp connection failed (%s:%i)\n", ip, port);
        return -1;
    }
	SDL_Log("mavlink: tcp connected (%s:%i)\n", ip, port);
	return tcp_sock;
}

int mavlink_tcp (void *data) {
	uint8_t modelid = 0;
	mavlink_message_t msg;
	mavlink_status_t status;
	SDL_Log("mavlink: init tcp thread\n");
	for (modelid = 0; modelid < MODELS_MAX; modelid++) {
		if (strcmp(ModelData[modelid].telemetry_port, "TCP") == 0 && ModelData[modelid].netip[0] != 0 && ModelData[modelid].netport != 0) {
			ModelData[modelid].netsock = mavlink_tcp_connect(ModelData[modelid].netip, ModelData[modelid].netport);
		}
	}
	while (tcp_running == 1) {
		char buf[TCP_BUFLEN + 1];
		fd_set fds;
		struct timeval ts;
		ts.tv_sec = 0;
		ts.tv_usec = 1000;
		for (modelid = 0; modelid < MODELS_MAX; modelid++) {
			if (strcmp(ModelData[modelid].telemetry_port, "TCP") == 0 && ModelData[modelid].netip[0] != 0 && ModelData[modelid].netport != 0) {
				FD_ZERO(&fds);
				if (ModelData[modelid].netsock != 0) {
					FD_SET(ModelData[modelid].netsock, &fds);
				}
				FD_SET(0, &fds);
				int nready = select(ModelData[modelid].netsock + 1, &fds, (fd_set *)0, (fd_set *)0, &ts);
				if (nready < 0) {
					SDL_Log("mavlink: tcp error");
					break;
				} else if (nready == 0) {
					ts.tv_sec = 0;
					ts.tv_usec = 1000;
				} else if (ModelData[modelid].netsock != 0 && FD_ISSET(ModelData[modelid].netsock, &fds)) {
					int rv;
					if ((rv = recv(ModelData[modelid].netsock , buf , TCP_BUFLEN , 0)) < 0) {
						return 1;
					} else if (rv == 0) {
						SDL_Log("mavlink: tcp connection closed by the remote end\n");
						return 0;
					}
					int n = 0;
					for (n = 0; n < rv; n++) {
						if (mavlink_parse_char(modelid, buf[n], &msg, &status)) {
							if (ModelData[modelid].use_deviceid == 0 || msg.sysid == ModelData[modelid].mavlink_sysid) {
								mavlink_handleMessage(modelid, &msg);
								mavlink_tcp_active = 1;
							}
						}
					}
					fflush(0);
				}
			}
		}
		SDL_Delay(1);
	}
	SDL_Log("mavlink: exit tcp thread\n");
	return 0;
}

int mavlink_udp (void *data) {
	uint8_t modelid = 0;
	mavlink_message_t msg;
	mavlink_status_t status;
	char buf[UDP_BUFLEN];
	SDL_Log("mavlink: init udp thread\n");
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		SDL_Log("mavlink: udp socket error\n");
		return 0;
	}
	int flags = fcntl(s, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(s, F_SETFL, flags);
	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(setup.mavlink_udp_port);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s , (struct sockaddr*)&si_me, sizeof(si_me)) == -1) {
		SDL_Log("mavlink: udp bind error\n");
		return 0;
	}
	while (udp_running == 1) {
		fflush(stdout);
		while ((recv_len = recvfrom(s, buf, UDP_BUFLEN, 0, (struct sockaddr *)&si_other, (socklen_t *)&slen)) != -1) {
			int n = 0;
			for (n = 0; n < recv_len; n++) {
				for (modelid = 0; modelid < MODELS_MAX; modelid++) {
					if (strcmp(ModelData[modelid].telemetry_port, "UDP") == 0) {
						if (mavlink_parse_char(modelid, buf[n], &msg, &status)) {
							if (ModelData[modelid].use_deviceid == 0 || msg.sysid == ModelData[modelid].mavlink_sysid) {
								mavlink_handleMessage(modelid, &msg);
								mavlink_udp_active = 1;
							}
						}
					}
				}
			}
		}
		SDL_Delay(1);
	}
	close(s);
	SDL_Log("mavlink: exit udp thread\n");
	return 0;
}
#else
int mavlink_tcp (void *data) {
	SDL_Log("mavlink: tcp not supported\n");
	return 0;
}

int mavlink_udp (void *data) {
	SDL_Log("mavlink: udp not supported\n");
	return 0;
}
#endif
