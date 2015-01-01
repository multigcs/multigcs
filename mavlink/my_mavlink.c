
#include <all.h>

#define UDP_BUFLEN 2042
#define UDP_PORT 14550

static struct sockaddr_in si_me, si_other;
static int s, slen = sizeof(si_other) , recv_len;

static uint8_t udp_running = 0;
int16_t mission_max = -1;
int serial_fd_mavlink = -1;
ValueList MavLinkVars[MAVLINK_PARAMETER_MAX];
uint8_t mavlink_update_yaw = 0;
int c, res;
char serial_buf[255];
static uint32_t last_connection = 1;
static int8_t GPS_found = 0;
uint16_t mavlink_timeout = 0;
uint16_t mavlink_maxparam = 0;
uint16_t mavlink_foundparam = 0;
uint8_t mavlink_udp_active = 0;
SDL_Thread *thread_udp = NULL;
int mavlink_udp (void *data);
int param_timeout = 0;
int param_complete = 0;
int ahrs2_found = 0;

void mavlink_xml_save (FILE *fr) {
	int16_t n = 0;
	fprintf(fr, " <mavlink>\n");
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (MavLinkVars[n].name[0] != 0) {
			fprintf(fr, "  <param><name>%s</name><value>%f</value></param>\n", MavLinkVars[n].name, MavLinkVars[n].value);
		}
	}
	fprintf(fr, " </mavlink>\n");
}

uint8_t mavlink_init (char *port, uint32_t baud) {
	int n = 0;
	mavlink_maxparam = 0;
	mavlink_foundparam = 0;
	SDL_Log("mavlink: init serial port...\n");
	serial_fd_mavlink = serial_open(port, baud);
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		MavLinkVars[n].name[0] = 0;
		MavLinkVars[n].group[0] = 0;
		MavLinkVars[n].display[0] = 0;
		MavLinkVars[n].desc[0] = 0;
		MavLinkVars[n].values[0] = 0;
		MavLinkVars[n].bits[0] = 0;
		MavLinkVars[n].value = 0.0;
		MavLinkVars[n].onload = 0.0;
		MavLinkVars[n].type = MAV_VAR_FLOAT;
		MavLinkVars[n].id = -1;
	}

	udp_running = 1;
#ifdef SDL2
	thread_udp = SDL_CreateThread(mavlink_udp, NULL, NULL);
#else
	thread_udp = SDL_CreateThread(mavlink_udp, NULL);
#endif
	if ( thread_udp == NULL ) {
		fprintf(stderr, "mavlink: Thread konnte nicht gestartet werden (mavlink_udp): %s\n", SDL_GetError());
		return 0;
	}
	return 0;
}

void mavlink_exit (void) {
	udp_running = 0;
	if (thread_udp != NULL) {
		SDL_Log("mavlink: wait udp thread\n");
		SDL_WaitThread(thread_udp, NULL);
		thread_udp = NULL;
	}
	if (serial_fd_mavlink >= 0) {
		serial_close(serial_fd_mavlink);
		serial_fd_mavlink = -1;
	}
}

void mavlink_stop_feeds (void) {
	SDL_Log("mavlink: stopping feeds!\n");
	mavlink_message_t msg1;
	mavlink_msg_request_data_stream_pack(127, 0, &msg1, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_ALL, 0, 0);
	mavlink_send_message(&msg1);
}

void mavlink_send_value (char *name, float val, int8_t type) {
	mavlink_message_t msg;
	if (type == -1) {
		type = MAV_VAR_FLOAT;
	}
	mavlink_msg_param_set_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, name, val, type);
	if (clientmode == 1) {
#ifndef WINDOWS
		webclient_send_value(clientmode_server, clientmode_port, name, val, type);
#endif
	} else {
		mavlink_send_message(&msg);
		ModelData.mavlink_update = (int)time(0);
	}
}

void mavlink_set_value (char *name, float value, int8_t type, int16_t id) {
	uint16_t n = 0;
	uint8_t flag = 0;
	float min = 999999.0;
	float max = 999999.0;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[n].name, name) == 0 && (MavLinkVars[n].id == id || MavLinkVars[n].id == -1 || id > MAVLINK_PARAMETER_MAX || id == -1)) {
			MavLinkVars[n].value = value;
			MavLinkVars[n].id = id;
			if (type == -1 || type > 6) {
				type = MAV_VAR_FLOAT;
			}
			MavLinkVars[n].type = type;
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
			if (MavLinkVars[n].name[0] == 0) {
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
				strncpy(MavLinkVars[n].name, name, 17);
				MavLinkVars[n].value = value;
				MavLinkVars[n].onload = value;
				MavLinkVars[n].id = id;

				if (type == -1) {
					type = MAV_VAR_FLOAT;
				}
printf("###### %s ## %i ###\n", name, type);

				MavLinkVars[n].type = type;
				MavLinkVars[n].min = min;
				MavLinkVars[n].max = max;
				if (MavLinkVars[n].min > MavLinkVars[n].value) {
					MavLinkVars[n].min = MavLinkVars[n].value;
				}
				if (MavLinkVars[n].max < MavLinkVars[n].value) {
					MavLinkVars[n].max = MavLinkVars[n].value;
				}

				if (strncmp(MavLinkVars[n].name, "RC", 2) == 0) {
					strncpy(MavLinkVars[n].group, "RC", 17);
				} else if (strncmp(MavLinkVars[n].name, "CH", 2) == 0) {
					strncpy(MavLinkVars[n].group, "Channels", 17);
				} else if (strncmp(MavLinkVars[n].name, "FLTMODE", 7) == 0) {
					strncpy(MavLinkVars[n].group, "FlightMode", 17);
				} else if (strncmp(MavLinkVars[n].name, "COMPASS", 7) == 0) {
					strncpy(MavLinkVars[n].group, "Compass", 17);
				} else if (strncmp(MavLinkVars[n].name, "SR", 2) == 0) {
					strncpy(MavLinkVars[n].group, "SR", 17);
				}
				break;
			}
		}
	}
	ModelData.mavlink_update = (int)time(0);
}

void mavlink_handleMessage(mavlink_message_t* msg) {
	mavlink_message_t msg2;
	char sysmsg_str[1024];
	if (param_complete == 0) {
		if (param_timeout > 1) {
			param_timeout--;
		} else if (param_timeout == 1) {
			param_timeout = 10;
			int n = 0;
			int n2 = 0;
			int flag2 = 0;
			for (n2 = 0; n2 < mavlink_maxparam; n2++) {
				int flag = 0;
				for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
					if (MavLinkVars[n].name[0] != 0 && MavLinkVars[n].id == n2) {
						flag = 1;
						break;
					}
				}
				if (flag == 0) {
					printf("# parameter %i not found #\n", n2);
					mavlink_param_get_id(n2);
					flag2 = 1;
					break;
				}
			}
			if (flag2 == 0) {
				printf("# parameter complete #\n");
				param_complete = 1;
			}
		}
	}

	//SDL_Log("mavlink: ## MAVLINK_MSG_ID %i ##\n", msg->msgid);

	switch (msg->msgid) {
		case MAVLINK_MSG_ID_HEARTBEAT: {
			mavlink_heartbeat_t packet;
			mavlink_msg_heartbeat_decode(msg, &packet);
			ModelData.dronetype = packet.type;
			ModelData.pilottype = packet.autopilot;
			if (packet.base_mode == MAV_MODE_MANUAL_ARMED) {
				ModelData.mode = MODEL_MODE_MANUAL;
			} else if (packet.base_mode == 128 + 64 + 16) {
				ModelData.mode = MODEL_MODE_RTL;
			} else if (packet.base_mode == 128 + 16) {
				ModelData.mode = MODEL_MODE_POSHOLD;
			} else if (packet.base_mode == 128 + 4) {
				ModelData.mode = MODEL_MODE_MISSION;
			}
			if (packet.system_status == MAV_STATE_ACTIVE) {
				ModelData.armed = MODEL_ARMED;
			} else {
				ModelData.armed = MODEL_DISARMED;
			}
//			SDL_Log("Heartbeat: %i, %i, %i\n", ModelData.armed, ModelData.mode, ModelData.status);
			ModelData.heartbeat = 100;
//			sprintf(sysmsg_str, "Heartbeat: %i", (int)time(0));
			if ((*msg).sysid != 0xff) {
				ModelData.sysid = (*msg).sysid;
				ModelData.compid = (*msg).compid;
				if (mavlink_maxparam == 0) {
					mavlink_start_feeds();
				}
			}
//			redraw_flag = 1;

			mavlink_msg_heartbeat_pack(127, 0, &msg2, MAV_TYPE_GCS, MAV_AUTOPILOT_INVALID, 0, 0, 0);
			mavlink_send_message(&msg2);

			break;
		}
		case MAVLINK_MSG_ID_RC_CHANNELS_SCALED: {
			mavlink_rc_channels_scaled_t packet;
			mavlink_msg_rc_channels_scaled_decode(msg, &packet);
			SDL_Log("Radio: %i,%i,%i\n", packet.chan1_scaled, packet.chan2_scaled, packet.chan3_scaled);

/*			if ((int)packet.chan6_scaled > 1000) {
				mode = MODE_MISSION;
			} else if ((int)packet.chan6_scaled < -1000) {
				mode = MODE_MANUEL;
			} else {
				mode = MODE_POSHOLD;
			}
			if ((int)packet.chan7_scaled > 1000) {
				mode = MODE_RTL;
			} else if ((int)packet.chan7_scaled < -1000) {
				mode = MODE_SETHOME;
			}
*/
			ModelData.radio[0] = (int)packet.chan1_scaled / 100.0;
			ModelData.radio[1] = (int)packet.chan2_scaled / 100.0;
			ModelData.radio[2] = (int)packet.chan3_scaled / 100.0;
			ModelData.radio[3] = (int)packet.chan4_scaled / 100.0;
			ModelData.radio[4] = (int)packet.chan5_scaled / 100.0;
			ModelData.radio[5] = (int)packet.chan6_scaled / 100.0;
			ModelData.radio[6] = (int)packet.chan7_scaled / 100.0;
			ModelData.radio[7] = (int)packet.chan8_scaled / 100.0;

//			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_SCALED_PRESSURE: {
			mavlink_scaled_pressure_t packet;
			mavlink_msg_scaled_pressure_decode(msg, &packet);
//			SDL_Log("BAR;%i;%0.2f;%0.2f;%0.2f\n", time(0), packet.press_abs, packet.press_diff, packet.temperature / 100.0);
//			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_ATTITUDE: {
			mavlink_attitude_t packet;
			mavlink_msg_attitude_decode(msg, &packet);
			if (ahrs2_found == 0) {
				ModelData.roll = toDeg(packet.roll);
				ModelData.pitch = toDeg(packet.pitch);
			}
			if (toDeg(packet.yaw) < 0.0) {
				ModelData.yaw = 360.0 + toDeg(packet.yaw);
			} else {
				ModelData.yaw = toDeg(packet.yaw);
			}
			mavlink_update_yaw = 1;
//			SDL_Log("ATT;%i;%0.2f;%0.2f;%0.2f\n", time(0), toDeg(packet.roll), toDeg(packet.pitch), toDeg(packet.yaw));
			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_SCALED_IMU: {
//			SDL_Log("SCALED_IMU\n");
			break;
		}
		case MAVLINK_MSG_ID_GPS_RAW_INT: {
			mavlink_gps_raw_int_t packet;
			mavlink_msg_gps_raw_int_decode(msg, &packet);
			if (packet.lat != 0 && packet.lon != 0) {
				GPS_found = 1;
				ModelData.p_lat = (float)packet.lat / 10000000.0;
				ModelData.p_long = (float)packet.lon / 10000000.0;
				ModelData.p_alt = (float)packet.alt / 1000.0;
				ModelData.speed = (float)packet.vel / 100.0;
				ModelData.numSat = packet.satellites_visible;
				ModelData.gpsfix = packet.fix_type;
				redraw_flag = 1;
			}
			break;
		}
		case MAVLINK_MSG_ID_RC_CHANNELS_RAW: {
			mavlink_rc_channels_raw_t packet;
			mavlink_msg_rc_channels_raw_decode(msg, &packet);

			ModelData.radio[0] = (int)packet.chan1_raw / 5 - 300;
			ModelData.radio[1] = (int)packet.chan2_raw / 5 - 300;
			ModelData.radio[2] = (int)packet.chan3_raw / 5 - 300;
			ModelData.radio[3] = (int)packet.chan4_raw / 5 - 300;
			ModelData.radio[4] = (int)packet.chan5_raw / 5 - 300;
			ModelData.radio[5] = (int)packet.chan6_raw / 5 - 300;
			ModelData.radio[6] = (int)packet.chan7_raw / 5 - 300;
			ModelData.radio[7] = (int)packet.chan8_raw / 5 - 300;
			ModelData.rssi_rc_rx = (int)packet.rssi * 100 / 255;
//			redraw_flag = 1;
/*
			SDL_Log("RC_CHANNELS_RAW\n");
			SDL_Log("mavlink: ## rc: ch1 %i ##\n", packet.chan1_raw);
			SDL_Log("mavlink: ## rc: ch2 %i ##\n", packet.chan2_raw);
			SDL_Log("mavlink: ## rc: ch3 %i ##\n", packet.chan3_raw);
			SDL_Log("mavlink: ## rc: ch4 %i ##\n", packet.chan4_raw);
			SDL_Log("mavlink: ## rc: ch5 %i ##\n", packet.chan5_raw);
			SDL_Log("mavlink: ## rc: ch6 %i ##\n", packet.chan6_raw);
			SDL_Log("mavlink: ## rc: ch7 %i ##\n", packet.chan7_raw);
			SDL_Log("mavlink: ## rc: ch8 %i ##\n", packet.chan8_raw);
			SDL_Log("mavlink: ## rc: port %i ##\n", packet.port);
			SDL_Log("mavlink: ## rc: rssi %i ##\n", packet.rssi);
*/
			break;
		}
		case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW: {
//			SDL_Log("SERVO_OUTPUT_RAW\n");
			break;
		}
		case MAVLINK_MSG_ID_SYS_STATUS: {
			mavlink_sys_status_t packet;
			mavlink_msg_sys_status_decode(msg, &packet);
//			SDL_Log("%0.1f %%, %0.3f V)\n", packet.load / 10.0, packet.voltage_battery / 1000.0);
			ModelData.voltage = packet.voltage_battery / 1000.0;
			ModelData.ampere = (float)packet.current_battery / 100.0;
			ModelData.load = packet.load / 10.0;
//			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_STATUSTEXT: {
			mavlink_statustext_t packet;
			mavlink_msg_statustext_decode(msg, &packet);
			SDL_Log("mavlink: ## %s ##\n", packet.text);
			sys_message((char *)packet.text);
//			redraw_flag = 1;
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
//strcpy(var, packet.param_id);

//	MAV_VAR_FLOAT=0, /* 32 bit float | */
//	MAV_VAR_UINT8=1, /* 8 bit unsigned integer | */
//	MAV_VAR_INT8=2, /* 8 bit signed integer | */
//	MAV_VAR_UINT16=3, /* 16 bit unsigned integer | */
//	MAV_VAR_INT16=4, /* 16 bit signed integer | */
//	MAV_VAR_UINT32=5, /* 32 bit unsigned integer | */
//	MAV_VAR_INT32=6, /* 32 bit signed integer | */

//mavlink_param_get_id (uint16_t id);

			sprintf(sysmsg_str, "PARAM_VALUE (%i/%i): #%s#%s# = %f (Type: %i)", packet.param_index + 1, packet.param_count, var, packet.param_id, packet.param_value, packet.param_type);
			SDL_Log("mavlink: %s\n", sysmsg_str);
			sys_message(sysmsg_str);
			mavlink_maxparam = packet.param_count;
			mavlink_timeout = 0;

			mavlink_set_value(var, packet.param_value, packet.param_type, packet.param_index);

			if (packet.param_index + 1 == packet.param_count || packet.param_index % 10 == 0) {
				mavlink_param_xml_meta_load();
			}

			param_timeout = 10;

//			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_MISSION_COUNT: {
			mavlink_mission_count_t packet;
			mavlink_msg_mission_count_decode(msg, &packet);
			sprintf(sysmsg_str, "MISSION_COUNT: %i\n", packet.count);
			sys_message(sysmsg_str);
			mission_max = packet.count;
			if (mission_max > 0) {
				mavlink_msg_mission_request_pack(127, 0, &msg2, ModelData.sysid, ModelData.compid, 0);
				mavlink_send_message(&msg2);
			}
//			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_MISSION_ACK: {
			SDL_Log("mavlink: Mission-Transfer ACK\n");
			break;
		}
		case MAVLINK_MSG_ID_MISSION_REQUEST: {
			mavlink_mission_request_t packet;
			mavlink_msg_mission_request_decode(msg, &packet);
			uint16_t id = packet.seq;
			uint16_t id2 = packet.seq;
			uint16_t type = 0;

			if (ModelData.teletype == TELETYPE_MEGAPIRATE_NG || ModelData.teletype == TELETYPE_ARDUPILOT) {
				if (id2 > 0) {
					id2 = id2 - 1;
				} else {
					SDL_Log("mavlink: WORKAROUND: first WP == HOME ?\n");
				}
			}

			sprintf(sysmsg_str, "sending Waypoint (%i): %s\n", id, WayPoints[1 + id2].name);
			sys_message(sysmsg_str);
			if (strcmp(WayPoints[1 + id2].command, "WAYPOINT") == 0) {
				SDL_Log("mavlink: Type: MAV_CMD_NAV_WAYPOINT\n");
				type = MAV_CMD_NAV_WAYPOINT;
			} else if (strcmp(WayPoints[1 + id2].command, "RTL") == 0) {
				SDL_Log("mavlink: Type: MAV_CMD_NAV_RETURN_TO_LAUNCH\n");
				type = MAV_CMD_NAV_RETURN_TO_LAUNCH;
			} else if (strcmp(WayPoints[1 + id2].command, "LAND") == 0) {
				SDL_Log("mavlink: Type: MAV_CMD_NAV_LAND\n");
				type = MAV_CMD_NAV_LAND;
			} else if (strcmp(WayPoints[1 + id2].command, "TAKEOFF") == 0) {
				SDL_Log("mavlink: Type: MAV_CMD_NAV_TAKEOFF\n");
				type = MAV_CMD_NAV_TAKEOFF;
			} else if (strcmp(WayPoints[1 + id2].command, "SET_ROI") == 0) {
				SDL_Log("mavlink: Type: MAV_CMD_NAV_ROI\n");
				type = MAV_CMD_NAV_ROI;
			} else {
				SDL_Log("mavlink: Type: UNKNOWN\n");
				type = MAV_CMD_NAV_WAYPOINT;
			}

			sprintf(sysmsg_str, "SENDING MISSION_ITEM: %i: %f, %f, %f\n", id, WayPoints[1 + id2].p_lat, WayPoints[1 + id2].p_long, WayPoints[1 + id2].p_alt);
			SDL_Log("mavlink: %s\n", sysmsg_str);


			mavlink_msg_mission_item_pack(127, 0, &msg2, ModelData.sysid, ModelData.compid, id, 0, type, 0.0, 0.0, WayPoints[1 + id2].radius, WayPoints[1 + id2].wait, WayPoints[1 + id2].orbit, WayPoints[1 + id2].yaw, WayPoints[1 + id2].p_lat, WayPoints[1 + id2].p_long, WayPoints[1 + id2].p_alt);
			mavlink_send_message(&msg2);
/*
mavlink_msg_mission_item_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.seq , packet1.frame , packet1.command , packet1.current , packet1.autocontinue , packet1.param1 , packet1.param2 , packet1.param3 , packet1.param4 , packet1.x , packet1.y , packet1.z );
float param1; ///< PARAM1 / For NAV command MISSIONs: Radius in which the MISSION is accepted as reached, in meters
float param2; ///< PARAM2 / For NAV command MISSIONs: Time that the MAV should stay inside the PARAM1 radius before advancing, in milliseconds
float param3; ///< PARAM3 / For LOITER command MISSIONs: Orbit to circle around the MISSION, in meters. If positive the orbit direction should be clockwise, if negative the orbit direction should be counter-clockwise.
float param4; ///< PARAM4 / For NAV and LOITER command MISSIONs: Yaw orientation in degrees, [0..360] 0 = NORTH
float x; ///< PARAM5 / local: x position, global: latitude
float y; ///< PARAM6 / y position: global: longitude
float z; ///< PARAM7 / z position: global: altitude
uint16_t seq; ///< Sequence
uint16_t command; ///< The scheduled action for the MISSION. see MAV_CMD in common.xml MAVLink specs
uint8_t target_system; ///< System ID
uint8_t target_component; ///< Component ID
uint8_t frame; ///< The coordinate system of the MISSION. see MAV_FRAME in mavlink_types.h
uint8_t current; ///< false:0, true:1
uint8_t autocontinue; ///< autocontinue to next wp
*/

//			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_MISSION_ITEM: {
			mavlink_mission_item_t packet;
			mavlink_msg_mission_item_decode(msg, &packet);

			sprintf(sysmsg_str, "RECEIVED MISSION_ITEM: %i/%i: %f, %f, %f (%i)\n", packet.seq, mission_max, packet.x, packet.y, packet.z, packet.frame);
			SDL_Log("mavlink: %s\n", sysmsg_str);
			sys_message(sysmsg_str);

			if (packet.seq < mission_max - 1) {
				mavlink_msg_mission_request_pack(127, 0, &msg2, ModelData.sysid, ModelData.compid, packet.seq + 1);
				mavlink_send_message(&msg2);
			} else {
				mavlink_msg_mission_ack_pack(127, 0, &msg2, ModelData.sysid, ModelData.compid, 15);
				mavlink_send_message(&msg2);
			}

			if (ModelData.teletype == TELETYPE_MEGAPIRATE_NG || ModelData.teletype == TELETYPE_ARDUPILOT) {
				if (packet.seq > 0) {
					packet.seq = packet.seq - 1;
				} else {
					SDL_Log("mavlink: WORKAROUND: ignore first WP\n");
					break;
				}
			}

			SDL_Log("mavlink: getting WP(%i): %f, %f\n", packet.seq, packet.x, packet.y);

			switch (packet.command) {
				case MAV_CMD_NAV_WAYPOINT: {
					strcpy(WayPoints[1 + packet.seq].command, "WAYPOINT");
					break;
				}
				case MAV_CMD_NAV_LOITER_UNLIM: {
					strcpy(WayPoints[1 + packet.seq].command, "LOITER_UNLIM");
					break;
				}
				case MAV_CMD_NAV_LOITER_TURNS: {
					strcpy(WayPoints[1 + packet.seq].command, "LOITER_TURNS");
					break;
				}
				case MAV_CMD_NAV_LOITER_TIME: {
					strcpy(WayPoints[1 + packet.seq].command, "LOITER_TIME");
					break;
				}
				case MAV_CMD_NAV_RETURN_TO_LAUNCH: {
					strcpy(WayPoints[1 + packet.seq].command, "RTL");
					break;
				}
				case MAV_CMD_NAV_LAND: {
					strcpy(WayPoints[1 + packet.seq].command, "LAND");
					break;
				}
				case MAV_CMD_NAV_TAKEOFF: {
					strcpy(WayPoints[1 + packet.seq].command, "TAKEOFF");
					break;
				}
				case MAV_CMD_NAV_ROI: {
					strcpy(WayPoints[1 + packet.seq].command, "SET_ROI");
					break;
				}
				default: {
					sprintf(WayPoints[1 + packet.seq].command, "CMD:%i", packet.command);
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
			WayPoints[1 + packet.seq].p_lat = packet.x;
			WayPoints[1 + packet.seq].p_long = packet.y;
			WayPoints[1 + packet.seq].p_alt = packet.z;
			WayPoints[1 + packet.seq].yaw = packet.param4;
			sprintf(WayPoints[1 + packet.seq].name, "WP%i", packet.seq + 1);

			WayPoints[1 + packet.seq + 1].p_lat = 0.0;
			WayPoints[1 + packet.seq + 1].p_long = 0.0;
			WayPoints[1 + packet.seq + 1].p_alt = 0.0;
			WayPoints[1 + packet.seq + 1].yaw = 0.0;
			WayPoints[1 + packet.seq + 1].name[0] = 0;
			WayPoints[1 + packet.seq + 1].command[0] = 0;

//			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_MISSION_CURRENT: {
			mavlink_mission_current_t packet;
			mavlink_msg_mission_current_decode(msg, &packet);
//			SDL_Log("mavlink: ## Active_WP %f ##\n", packet.seq);
			uav_active_waypoint = (uint8_t)packet.seq;
			break;
		}
		case MAVLINK_MSG_ID_RAW_IMU: {
			mavlink_raw_imu_t packet;
			mavlink_msg_raw_imu_decode(msg, &packet);
/*
			SDL_Log("## IMU_RAW_ACC_X %i ##\n", packet.xacc);
			SDL_Log("## IMU_RAW_ACC_Y %i ##\n", packet.yacc);
			SDL_Log("## IMU_RAW_ACC_Z %i ##\n", packet.zacc);
			SDL_Log("## IMU_RAW_GYRO_X %i ##\n", packet.xgyro);
			SDL_Log("## IMU_RAW_GYRO_Y %i ##\n", packet.ygyro);
			SDL_Log("## IMU_RAW_GYRO_Z %i ##\n", packet.zgyro);
			SDL_Log("## IMU_RAW_MAG_X %i ##\n", packet.xmag);
			SDL_Log("## IMU_RAW_MAG_Y %i ##\n", packet.ymag);
			SDL_Log("## IMU_RAW_MAG_Z %i ##\n", packet.zmag);
*/
			ModelData.acc_x = (float)packet.xacc / 1000.0;
			ModelData.acc_y = (float)packet.yacc / 1000.0;
			ModelData.acc_z = (float)packet.zacc / 1000.0;
			ModelData.gyro_x = (float)packet.zgyro;
			ModelData.gyro_y = (float)packet.zgyro;
			ModelData.gyro_z = (float)packet.zgyro;
//			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT: {
			mavlink_nav_controller_output_t packet;
			mavlink_msg_nav_controller_output_decode(msg, &packet);
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT nav_roll %f ##\n", packet.nav_roll); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT nav_pitch %f ##\n", packet.nav_pitch); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT alt_error %f ##\n", packet.alt_error); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT aspd_error %f ##\n", packet.aspd_error); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT xtrack_error %f ##\n", packet.xtrack_error); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT nav_bearing %i ##\n", packet.nav_bearing); //INT16_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT target_bearing %i ##\n", packet.target_bearing); //INT16_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT wp_dist %i ##\n", packet.wp_dist); //UINT16_T
*/	
			break;
		}
		case MAVLINK_MSG_ID_VFR_HUD: {
			mavlink_vfr_hud_t packet;
			mavlink_msg_vfr_hud_decode(msg, &packet);
			if (GPS_found == 0) {
				ModelData.p_alt = packet.alt;
			}
/*
			SDL_Log("## pa %f ##\n", packet.airspeed);
			SDL_Log("## pg %f ##\n", packet.groundspeed);
			SDL_Log("## palt %f ##\n", packet.alt);
			SDL_Log("## pc %f ##\n", packet.climb);
			SDL_Log("## ph %i ##\n", packet.heading);
			SDL_Log("## pt %i ##\n", packet.throttle);
*/
			break;
		}
		case MAVLINK_MSG_ID_RADIO_STATUS: {
			mavlink_radio_status_t packet;
			mavlink_msg_radio_status_decode(msg, &packet);
			ModelData.rssi_tx = packet.rssi / 2;
			ModelData.rssi_rx = packet.remrssi / 2;
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RADIO_STATUS rxerrors %i ##\n", packet.rxerrors); //UINT16_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RADIO_STATUS fixed %i ##\n", packet.fixed); //UINT16_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RADIO_STATUS rssi %i ##\n", packet.rssi); //UINT8_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RADIO_STATUS remrssi %i ##\n", packet.remrssi); //UINT8_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RADIO_STATUS txbuf %i ##\n", packet.txbuf); //UINT8_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RADIO_STATUS noise %i ##\n", packet.noise); //UINT8_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RADIO_STATUS remnoise %i ##\n", packet.remnoise); //UINT8_T
*/
			break;
		}
		case MAVLINK_MSG_ID_RADIO: {
			mavlink_radio_t packet;
			mavlink_msg_radio_decode(msg, &packet);
			ModelData.rssi_tx = packet.rssi / 2;
			ModelData.rssi_rx = packet.remrssi / 2;
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RADIO rxerrors %i ##\n", packet.rxerrors); //UINT16_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RADIO fixed %i ##\n", packet.fixed); //UINT16_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RADIO rssi %i ##\n", packet.rssi); //UINT8_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RADIO remrssi %i ##\n", packet.remrssi); //UINT8_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RADIO txbuf %i ##\n", packet.txbuf); //UINT8_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RADIO noise %i ##\n", packet.noise); //UINT8_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RADIO remnoise %i ##\n", packet.remnoise); //UINT8_T
*/
			break;
		}
		case MAVLINK_MSG_ID_GLOBAL_POSITION_INT: {
			mavlink_global_position_int_t packet;
			mavlink_msg_global_position_int_decode(msg, &packet);
			if (GPS_found == 0) {
				if (packet.lat != 0 && packet.lon != 0) {
//					ModelData.p_lat = (float)packet.lat / 10000000.0;
//					ModelData.p_long = (float)packet.lon / 10000000.0;
//					ModelData.p_alt = (float)packet.alt / 1000.0;
//					ModelData.yaw = (float)packet.hdg / 100.0;
				}
			}
/*
			SDL_Log("mavlink: ## gp: lat %i ##\n", packet.lat);
			SDL_Log("mavlink: ## gp: lon %i ##\n", packet.lon);
			SDL_Log("mavlink: ## gp: alt %i ##\n", packet.alt);
			SDL_Log("mavlink: ## gp: ralt %i ##\n", packet.relative_alt);
			SDL_Log("mavlink: ## gp: vx %i ##\n", packet.vx);
			SDL_Log("mavlink: ## gp: vy %i ##\n", packet.vy);
			SDL_Log("mavlink: ## gp: vz %i ##\n", packet.vz);
			SDL_Log("mavlink: ## gp: hdg %0.2f ##\n", (float)packet.hdg / 100.0);
*/
			break;
		}
		case MAVLINK_MSG_ID_SYSTEM_TIME: {
			mavlink_system_time_t packet;
			mavlink_msg_system_time_decode(msg, &packet);
/*
			SDL_Log("mavlink: ## time_unix_usec %i ##\n", packet.time_unix_usec);
			SDL_Log("mavlink: ## time_boot_ms %i ##\n", packet.time_boot_ms);
*/
			break;
		}
		case MAVLINK_MSG_ID_RC_CHANNELS: {
			mavlink_rc_channels_t packet;
			mavlink_msg_rc_channels_decode(msg, &packet);
			ModelData.radio[0] = (int)packet.chan1_raw / 5 - 300;
			ModelData.radio[1] = (int)packet.chan2_raw / 5 - 300;
			ModelData.radio[2] = (int)packet.chan3_raw / 5 - 300;
			ModelData.radio[3] = (int)packet.chan4_raw / 5 - 300;
			ModelData.radio[4] = (int)packet.chan5_raw / 5 - 300;
			ModelData.radio[5] = (int)packet.chan6_raw / 5 - 300;
			ModelData.radio[6] = (int)packet.chan7_raw / 5 - 300;
			ModelData.radio[7] = (int)packet.chan8_raw / 5 - 300;
			ModelData.radio[8] = (int)packet.chan9_raw / 5 - 300;
			ModelData.radio[9] = (int)packet.chan10_raw / 5 - 300;
			ModelData.radio[10] = (int)packet.chan11_raw / 5 - 300;
			ModelData.radio[11] = (int)packet.chan12_raw / 5 - 300;
			ModelData.radio[12] = (int)packet.chan13_raw / 5 - 300;
			ModelData.radio[13] = (int)packet.chan14_raw / 5 - 300;
			ModelData.radio[14] = (int)packet.chan15_raw / 5 - 300;
			ModelData.radio[15] = (int)packet.chan16_raw / 5 - 300;
			uint16_t n = 0;
			for (n = 1; n < 16; n++) {
				if (ModelData.radio[n] > 100) {
					ModelData.radio[n] = 100;
				} else if (ModelData.radio[n] < -100) {
					ModelData.radio[n] = -100;
				}
			}
			ModelData.rssi_rc_rx = (int)packet.rssi * 100 / 255;
			ModelData.chancount = (uint8_t)packet.chancount;
//			redraw_flag = 1;
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS time_boot_ms %i ##\n", packet.time_boot_ms);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan1_raw %i ##\n", packet.chan1_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan2_raw %i ##\n", packet.chan2_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan3_raw %i ##\n", packet.chan3_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan4_raw %i ##\n", packet.chan4_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan5_raw %i ##\n", packet.chan5_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan6_raw %i ##\n", packet.chan6_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan7_raw %i ##\n", packet.chan7_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan8_raw %i ##\n", packet.chan8_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan9_raw %i ##\n", packet.chan9_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan10_raw %i ##\n", packet.chan10_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan11_raw %i ##\n", packet.chan11_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan12_raw %i ##\n", packet.chan12_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan13_raw %i ##\n", packet.chan13_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan14_raw %i ##\n", packet.chan14_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan15_raw %i ##\n", packet.chan15_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan16_raw %i ##\n", packet.chan16_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan17_raw %i ##\n", packet.chan17_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chan18_raw %i ##\n", packet.chan18_raw);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS chancount %i ##\n", packet.chancount);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_RC_CHANNELS rssi %i ##\n", packet.rssi);
*/
			break;
		}
		case MAVLINK_MSG_ID_AHRS: {
			mavlink_ahrs_t packet;
			mavlink_msg_ahrs_decode(msg, &packet);
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AHRS omegaIx %f ##\n", packet.omegaIx);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AHRS omegaIy %f ##\n", packet.omegaIy);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AHRS omegaIz %f ##\n", packet.omegaIz);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AHRS accel_weight %f ##\n", packet.accel_weight);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AHRS renorm_val %f ##\n", packet.renorm_val);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AHRS error_rp %f ##\n", packet.error_rp);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AHRS error_yaw %f ##\n", packet.error_yaw);
*/
			break;
		}
		case MAVLINK_MSG_ID_HWSTATUS: {
			mavlink_hwstatus_t packet;
			mavlink_msg_hwstatus_decode(msg, &packet);
			ModelData.fc_voltage1 = (float)packet.Vcc / 1000.0;
			ModelData.fc_i2c_errors = packet.I2Cerr;
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_HWSTATUS Vcc %i ##\n", packet.Vcc);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_HWSTATUS I2Cerr %i ##\n", packet.I2Cerr);
*/
			break;
		}
		case MAVLINK_MSG_ID_SCALED_IMU2: {
			mavlink_scaled_imu2_t packet;
			mavlink_msg_scaled_imu2_decode(msg, &packet);
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SCALED_IMU2 xacc %i ##\n", packet.xacc);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SCALED_IMU2 yacc %i ##\n", packet.yacc);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SCALED_IMU2 zacc %i ##\n", packet.zacc);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SCALED_IMU2 xgyro %i ##\n", packet.xgyro);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SCALED_IMU2 ygyro %i ##\n", packet.ygyro);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SCALED_IMU2 zgyro %i ##\n", packet.zgyro);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SCALED_IMU2 xmag %i ##\n", packet.xmag);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SCALED_IMU2 ymag %i ##\n", packet.ymag);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_SCALED_IMU2 zmag %i ##\n", packet.zmag);
*/
			break;
		}
		case MAVLINK_MSG_ID_POWER_STATUS: {
			mavlink_power_status_t packet;
			mavlink_msg_power_status_decode(msg, &packet);
			ModelData.fc_voltage1 = (float)packet.Vcc / 1000.0;
			ModelData.fc_voltage2 = (float)packet.Vservo / 1000.0;
			ModelData.fc_status = packet.flags;
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_POWER_STATUS Vcc %i ##\n", packet.Vcc);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_POWER_STATUS Vservo %i ##\n", packet.Vservo);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_POWER_STATUS flags %i ##\n", packet.flags);
			if (packet.flags & MAV_POWER_STATUS_BRICK_VALID) {
				SDL_Log("	mavlink: ## POWER_STATUS: main brick power supply valid ##\n");
			}
			if (packet.flags & MAV_POWER_STATUS_SERVO_VALID) {
				SDL_Log("	mavlink: ## POWER_STATUS: main servo power supply valid for FMU ##\n");
			}
			if (packet.flags & MAV_POWER_STATUS_USB_CONNECTED) {
				SDL_Log("	mavlink: ## POWER_STATUS: USB power is connected ##\n");
				ModelData.rssi_rx = 100;
				ModelData.rssi_tx = 100;
			}
			if (packet.flags & MAV_POWER_STATUS_PERIPH_OVERCURRENT) {
				SDL_Log("	mavlink: ## POWER_STATUS: peripheral supply is in over-current state ##\n");
			}
			if (packet.flags & MAV_POWER_STATUS_PERIPH_HIPOWER_OVERCURRENT) {
				SDL_Log("	mavlink: ## POWER_STATUS: hi-power peripheral supply is in over-current state ##\n");
			}
			if (packet.flags & MAV_POWER_STATUS_CHANGED) {
				SDL_Log("	mavlink: ## POWER_STATUS: Power status has changed since boot ##\n");
			}
*/
			break;
		}
		case MAVLINK_MSG_ID_MEMINFO: {
			mavlink_meminfo_t packet;
			mavlink_msg_meminfo_decode(msg, &packet);
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_MEMINFO brkval %i ##\n", packet.brkval);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_MEMINFO freemem %i ##\n", packet.freemem);
*/
			break;
		}
		case MAVLINK_MSG_ID_SENSOR_OFFSETS: {
			mavlink_sensor_offsets_t packet;
			mavlink_msg_sensor_offsets_decode(msg, &packet);
/*
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
*/
			break;
		}
		case MAVLINK_MSG_ID_AHRS2: {
			mavlink_ahrs2_t packet;
			mavlink_msg_ahrs2_decode(msg, &packet);
			ahrs2_found = 1;
			ModelData.roll = toDeg(packet.roll);
			ModelData.pitch = toDeg(packet.pitch);
//			if (toDeg(packet.yaw) < 0.0) {
//				ModelData.yaw = 360.0 + toDeg(packet.yaw);
//			} else {
//				ModelData.yaw = toDeg(packet.yaw);
//			}
//			ModelData.p_alt = packet.altitude;
//			if (packet.lat != 0 && packet.lng != 0) {
//				ModelData.p_lat = (float)packet.lat / 10000000.0;
//				ModelData.p_long = (float)packet.lng / 10000000.0;
//			}
			mavlink_update_yaw = 1;
			redraw_flag = 1;
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AHRS2 roll %f ##\n", packet.roll); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AHRS2 pitch %f ##\n", packet.pitch); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AHRS2 yaw %f ##\n", packet.yaw); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AHRS2 altitude %f ##\n", packet.altitude); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AHRS2 lat %i ##\n", packet.lat); //INT32_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_AHRS2 lng %i ##\n", packet.lng); //INT32_T
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
		case MAVLINK_MSG_ID_MOUNT_STATUS: {
			mavlink_mount_status_t packet;
			mavlink_msg_mount_status_decode(msg, &packet);
			ModelData.mnt_pitch = (float)packet.pointing_a / 100.0;
			ModelData.mnt_roll = (float)packet.pointing_b / 100.0;
			ModelData.mnt_yaw = (float)packet.pointing_c / 100.0;
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_MOUNT_STATUS pointing_a %i ##\n", packet.pointing_a); //INT32_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_MOUNT_STATUS pointing_b %i ##\n", packet.pointing_b); //INT32_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_MOUNT_STATUS pointing_c %i ##\n", packet.pointing_c); //INT32_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_MOUNT_STATUS target_system %i ##\n", packet.target_system); //UINT8_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_MOUNT_STATUS target_component %i ##\n", packet.target_component); //UINT8_T
*/
			break;
		}
		case MAVLINK_MSG_ID_TERRAIN_REQUEST: {
			mavlink_terrain_request_t packet;
			mavlink_msg_terrain_request_decode(msg, &packet);
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REQUEST mask %llu ##\n", packet.mask); //UINT64_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REQUEST lat %i ##\n", packet.lat); //INT32_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REQUEST lon %i ##\n", packet.lon); //INT32_T
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_TERRAIN_REQUEST grid_spacing %i ##\n", packet.grid_spacing); //UINT16_T
			break;
		}
		case MAVLINK_MSG_ID_WIND: {
			mavlink_wind_t packet;
			mavlink_msg_wind_decode(msg, &packet);
/*
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_WIND direction %f ##\n", packet.direction); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_WIND speed %f ##\n", packet.speed); //FLOAT
			SDL_Log("mavlink: ## MAVLINK_MSG_ID_WIND speed_z %f ##\n", packet.speed_z); //FLOAT
*/
			break;
		}
		default: {
			SDL_Log("mavlink: ## UNSUPPORTED MSG_ID == %i (mavlink/get_case_by_file.sh %i) ##\n", msg->msgid, msg->msgid);
			break;
		}
	}
}

void mavlink_send_terrain_data (int32_t lat, int32_t lon, uint16_t grid_spacing, uint8_t gridbit, int16_t data[16]) {
	SDL_Log("mavlink: sending terrain_data\n");
	mavlink_message_t msg;
	mavlink_msg_terrain_data_pack(127, 0, &msg, lat, lon, grid_spacing, gridbit, data);
	mavlink_send_message(&msg);
}

void mavlink_read_waypoints (void) {
	SDL_Log("mavlink: reading Waypoints\n");
	mavlink_message_t msg;
	mavlink_msg_mission_request_list_pack(127, 0, &msg, ModelData.sysid, ModelData.compid);
	mavlink_send_message(&msg);
}

void mavlink_save_to_flash (void) {
	SDL_Log("mavlink: save values to flash\n");
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_CMD_PREFLIGHT_STORAGE, 0, 1.0f, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	mavlink_send_message(&msg);
}

void mavlink_load_from_flash (void) {
	SDL_Log("mavlink: load values from flash\n");
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_CMD_PREFLIGHT_STORAGE, 0, 0.0f, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	mavlink_send_message(&msg);
}

void mavlink_send_waypoints (void) {
	mavlink_message_t msg;
	mavlink_msg_mission_clear_all_pack(127, 0, &msg, ModelData.sysid, ModelData.compid);
	mavlink_send_message(&msg);
	usleep(100000);
	uint16_t n = 0;
	for (n = 1; n < MAX_WAYPOINTS; n++) {
		if (WayPoints[n].p_lat == 0.0) {
			break;
		}
	}
	if (ModelData.teletype == TELETYPE_MEGAPIRATE_NG || ModelData.teletype == TELETYPE_ARDUPILOT) {
		SDL_Log("mavlink: WORKAROUND: MEGAPIRATE_NG: fake one WP\n");
		n++;
	}
	SDL_Log("mavlink: sending Waypoints (%i)\n", n - 1);
	mavlink_msg_mission_count_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, n - 1);
	mavlink_send_message(&msg);
}

void mavlink_send_message (mavlink_message_t* msg) {
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	SDL_Log("mavlink: send_msg...\n");
	uint16_t len = mavlink_msg_to_send_buffer(buf, msg);
	uint16_t i = 0;
	for(i = 0; i < len; i++) {
		uint8_t c = buf[i];
		serial_write(serial_fd_mavlink, &c, 1);
	}
#ifndef WINDOWS
	if (mavlink_udp_active == 1) {
		if (sendto(s, buf, len, 0, (struct sockaddr *)&si_other, slen) == -1) {
			SDL_Log("mavlink: error: sendto udp()\n");
		}
	}
#endif
}

uint8_t mavlink_connection_status (void) {
	if (serial_fd_mavlink == -1) {
		return 0;
	}
	return last_connection;
}

void mavlink_update (void) {
	if (serial_fd_mavlink == -1) {
		return;
	}
	uint8_t c = 0;
	uint16_t n = 0;
	mavlink_message_t msg;
	mavlink_status_t status;
	while ((res = serial_read(serial_fd_mavlink, serial_buf, 250)) > 0) {
		last_connection = time(0);
		for (n = 0; n < res; n++) {
			c = serial_buf[n];
			if(mavlink_parse_char(0, c, &msg, &status)) {
				mavlink_handleMessage(&msg);
			}
		}
	}
}

void mavlink_param_get_id (uint16_t id) {
	SDL_Log("mavlink: get id: %i\n", id);
	mavlink_message_t msg;
	mavlink_msg_param_request_read_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, NULL, id);
	mavlink_send_message(&msg);
}

void mavlink_start_feeds (void) {
	mavlink_message_t msg;
	mavlink_timeout = 0;
	param_complete = 0;

//	mavlink_maxparam = 1;

	SDL_Log("mavlink: starting feeds!\n");
	mavlink_msg_param_request_list_pack(127, 0, &msg, ModelData.sysid, ModelData.compid);
	mavlink_send_message(&msg);
	SDL_Delay(30);


	mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_RAW_SENSORS, MAV_DATA_STREAM_RAW_SENSORS_RATE, MAV_DATA_STREAM_RAW_SENSORS_ACTIVE);
	mavlink_send_message(&msg);
	SDL_Delay(30);

	mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_RC_CHANNELS, MAV_DATA_STREAM_RC_CHANNELS_RATE, MAV_DATA_STREAM_RC_CHANNELS_ACTIVE);
	mavlink_send_message(&msg);
	SDL_Delay(30);

	if (ModelData.teletype == TELETYPE_MEGAPIRATE_NG || ModelData.teletype == TELETYPE_ARDUPILOT || ModelData.teletype == TELETYPE_HARAKIRIML) {
		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_EXTENDED_STATUS, MAV_DATA_STREAM_EXTENDED_STATUS_RATE, MAV_DATA_STREAM_EXTENDED_STATUS_ACTIVE);
		mavlink_send_message(&msg);
		SDL_Delay(30);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_RAW_CONTROLLER, MAV_DATA_STREAM_RAW_CONTROLLER_RATE, MAV_DATA_STREAM_RAW_CONTROLLER_ACTIVE);
		mavlink_send_message(&msg);
		SDL_Delay(30);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_POSITION, MAV_DATA_STREAM_POSITION_RATE, MAV_DATA_STREAM_POSITION_ACTIVE);
		mavlink_send_message(&msg);
		SDL_Delay(30);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_EXTRA1, MAV_DATA_STREAM_EXTRA1_RATE, MAV_DATA_STREAM_EXTRA1_ACTIVE);
		mavlink_send_message(&msg);
		SDL_Delay(30);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_EXTRA2, MAV_DATA_STREAM_EXTRA2_RATE, MAV_DATA_STREAM_EXTRA2_ACTIVE);
		mavlink_send_message(&msg);
		SDL_Delay(30);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_EXTRA3, MAV_DATA_STREAM_EXTRA3_RATE, MAV_DATA_STREAM_EXTRA3_ACTIVE);
		mavlink_send_message(&msg);
		SDL_Delay(30);
	}
}

#ifndef WINDOWS
int mavlink_udp (void *data) {
	SDL_Log("mavlink: init udp thread\n");
	mavlink_message_t msg;
	mavlink_status_t status;
	char buf[UDP_BUFLEN];

	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		SDL_Log("mavlink: socket error\n");
		return 0;
	}

	int flags = fcntl(s, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(s, F_SETFL, flags);

	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(UDP_PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1) {
		SDL_Log("mavlink: bind error\n");
		return 0;
	}
	while (udp_running == 1) {
		fflush(stdout);
		while ((recv_len = recvfrom(s, buf, UDP_BUFLEN, 0, (struct sockaddr *)&si_other, (socklen_t *)&slen)) != -1) {
			int n = 0;
			for (n = 0; n < recv_len; n++) {
				if(mavlink_parse_char(1, buf[n], &msg, &status)) {
					mavlink_handleMessage(&msg);
					mavlink_udp_active = 1;
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
int mavlink_udp (void *data) {
	return 0;
}
#endif

void mavlink_parseParams1 (xmlDocPtr doc, xmlNodePtr cur, char *name) { 
	int n = 0;
	int n2 = 0;
	int n3 = 0;
	int n4 = 0;
	char tmp_str3[1024];
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[n].name, name) == 0) {
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
				MavLinkVars[n].min = min;
				MavLinkVars[n].max = max;
				if (MavLinkVars[n].min > MavLinkVars[n].value) {
					MavLinkVars[n].min = MavLinkVars[n].value;
				}
				if (MavLinkVars[n].max < MavLinkVars[n].value) {
					MavLinkVars[n].max = MavLinkVars[n].value;
				}
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Description"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[n].desc, (char *)key, 1023);
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Group"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[n].group, (char *)key, 20);
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Values"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[n].values, (char *)key, 1023);
				if (MavLinkVars[n].values[0] != 0) {
					MavLinkVars[n].min = atof(MavLinkVars[n].values);
					for (n2 = 0; n2 < strlen(MavLinkVars[n].values); n2++) {
						if (MavLinkVars[n].values[n2] == ',') {
							strncpy(tmp_str3, MavLinkVars[n].values + n3, 1023);
							for (n4 = 0; n4 < strlen(tmp_str3); n4++) {
								if (tmp_str3[n4] == ',') {
									tmp_str3[n4] = 0;
									break;
								}
							}
							n3 = n2 + 1;
						}
					}
					strncpy(tmp_str3, MavLinkVars[n].values + n3, 1023);
					MavLinkVars[n].max = atof(tmp_str3);
				}
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Bits"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[n].bits, (char *)key, 1023);
				if (MavLinkVars[n].bits[0] != 0) {
					MavLinkVars[n].min = 0;
					for (n2 = 0; n2 < strlen(MavLinkVars[n].bits); n2++) {
						if (MavLinkVars[n].bits[n2] == ',') {
							strncpy(tmp_str3, MavLinkVars[n].bits + n3, 1023);
							for (n4 = 0; n4 < strlen(tmp_str3); n4++) {
								if (tmp_str3[n4] == ',') {
									tmp_str3[n4] = 0;
									break;
								}
							}
							n3 = n2 + 1;
						}
					}
					strncpy(tmp_str3, MavLinkVars[n].bits + n3, 1023);
					MavLinkVars[n].max = (float)((1<<atoi(tmp_str3)) * (1<<atoi(tmp_str3)) - 1);
				}
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"DisplayName"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[n].display, (char *)key, 100);
				xmlFree(key);
			}
		}
		cur = cur->next;
	}
	return;
}

void mavlink_parseParamsGetAttr (xmlDocPtr doc, xmlNodePtr cur, char *attrName, char *attrValue) {
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

void mavlink_parseParams1New (xmlDocPtr doc, xmlNodePtr cur, char *name, char *disp, char *desc) { 
	int n = 0;
	for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
		if (strcmp(MavLinkVars[n].name, name) == 0) {
			break;
		}
	}
	if (n == MAVLINK_PARAMETER_MAX) {
		return;
	}
	strncpy(MavLinkVars[n].desc, (char *)desc, 1023);
	strncpy(MavLinkVars[n].display, (char *)disp, 100);
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		char attrValue[1024];
		mavlink_parseParamsGetAttr(doc, cur, "Name", attrValue);
		if ((!xmlStrcasecmp((const xmlChar *)attrValue, (const xmlChar *)"Range"))) {
			float min = 0.0;
			float max = 0.0;
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				sscanf((char *)key, "%f %f", &min, &max);
				MavLinkVars[n].min = min;
				MavLinkVars[n].max = max;
				if (MavLinkVars[n].min > MavLinkVars[n].value) {
					MavLinkVars[n].min = MavLinkVars[n].value;
				}
				if (MavLinkVars[n].max < MavLinkVars[n].value) {
					MavLinkVars[n].max = MavLinkVars[n].value;
				}
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp((const xmlChar *)attrValue, (const xmlChar *)"Group"))) {
			xmlChar *key;
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if (key != NULL) {
				strncpy(MavLinkVars[n].group, (char *)key, 20);
				xmlFree(key);
			}
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"Values"))) {
			float last_val = 0.0;
			MavLinkVars[n].values[0] = 0;
			xmlNodePtr cur2 = cur->xmlChildrenNode;
			while (cur2 != NULL) {
				if (!(xmlStrcasecmp(cur2->name, (const xmlChar *)"Value"))) {
					xmlChar *key;
					key = xmlNodeListGetString(doc, cur2->xmlChildrenNode, 1);
					if (key != NULL) {
						char Value[1024];
						char Value2[1024];
						mavlink_parseParamsGetAttr(doc, cur2, "Code", Value);
						trimline(Value2, 1024, Value);
						last_val = atof(Value2);
						if (MavLinkVars[n].values[0] == 0) {
							MavLinkVars[n].min = last_val;
						} else {
							strcat(MavLinkVars[n].values, ",");
						}
						strcat(MavLinkVars[n].values, Value2);
						strcat(MavLinkVars[n].values, ":");
						strcat(MavLinkVars[n].values, (char *)key);
						xmlFree(key);
					}
				}
				cur2 = cur2->next;
			}
			MavLinkVars[n].max = last_val;
		}
		cur = cur->next;
	}
	return;
}

void mavlink_parseParamsNew (xmlDocPtr doc, xmlNodePtr cur) { 
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if (!(xmlStrcasecmp(cur->name, (const xmlChar *)"param"))) {
			char attrValue[1024];
			char Desc[1024];
			char Disp[1024];
			mavlink_parseParamsGetAttr(doc, cur, "Name", attrValue);
			mavlink_parseParamsGetAttr(doc, cur, "Documentation", Desc);
			mavlink_parseParamsGetAttr(doc, cur, "humanName", Disp);
			if (strncmp(attrValue, "ArduCopter:", 11) == 0) {
				mavlink_parseParams1New(doc, cur, attrValue + 11, Disp, Desc);
			}
		}
		cur = cur->next;
	}
	return;
}

void mavlink_parseParams (xmlDocPtr doc, xmlNodePtr cur) { 
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if (!(xmlStrcasecmp(cur->name, (const xmlChar *)"parameters"))) {
			mavlink_parseParamsNew(doc, cur);
		} else if ((xmlStrcasecmp(cur->name, (const xmlChar *)"text"))) {
			mavlink_parseParams1(doc, cur, (char *)cur->name);
		}
		cur = cur->next;
	}
	return;
}

static void mavlink_parseDoc (char *docname) {
	xmlDocPtr doc;
	xmlNodePtr cur;
	if (strncmp(docname, "./", 2) == 0) {
		docname += 2;
	}
	char *buffer = NULL;
	int len = 0;
	SDL_RWops *ops_file = SDL_RWFromFile(docname, "r");
	if (ops_file == NULL) {
		SDL_Log("map: Document open failed: %s\n", docname);
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
		SDL_Log("mavlink: Document parsing failed: %s\n", docname);
		return;
	}
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL) {
		xmlFreeDoc(doc);
		SDL_Log("mavlink: Document is Empty!!!\n");
		return;
	}
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((xmlStrcasecmp(cur->name, (const xmlChar *)"text"))) {
			mavlink_parseParams(doc, cur);
		} else if ((xmlStrcasecmp(cur->name, (const xmlChar *)"vehicles"))) {
			mavlink_parseParams(doc, cur);
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}

void mavlink_param_xml_meta_load (void) {
	char filename[1024];
	sprintf(filename, "%s/mavlink/ParameterMetaData-%s.xml", get_datadirectory(), teletypes[ModelData.teletype]);
	if (file_exists(filename) != 0) {
		mavlink_parseDoc(filename);
		return;
	}
	sprintf(filename, "%s/mavlink/ParameterMetaData-%s.xml", BASE_DIR, teletypes[ModelData.teletype]);
	if (file_exists(filename) != 0) {
		mavlink_parseDoc(filename);
		return;
	}
}

static void model_parseMavlinkParam (xmlDocPtr doc, xmlNodePtr cur, uint16_t param) { 
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"name"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				strncpy(MavLinkVars[param].name, (char *)key, 20);
			}
			xmlFree(key);
		} else if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"value"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			if ((char *)key != NULL) {
				MavLinkVars[param].value = atof((char *)key);
				MavLinkVars[param].onload = atof((char *)key);
			}
			xmlFree(key);
		}
		cur = cur->next;
	}
	return;
}

void mavlink_xml_load (xmlDocPtr doc, xmlNodePtr cur) { 
	uint16_t param = 0;
	for (param = 0; param < MAVLINK_PARAMETER_MAX; param++) {
		MavLinkVars[param].name[0] = 0;
		MavLinkVars[param].group[0] = 0;
		MavLinkVars[param].value = 0.0;
		MavLinkVars[param].onload = 0.0;
	}
	param = 0;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if ((!xmlStrcasecmp(cur->name, (const xmlChar *)"param"))) {
			model_parseMavlinkParam (doc, cur, param++);
		}
		cur = cur->next;
	}
	return;
}

static void mavlink_html_page (char *content, char *sub) {
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
		if (MavLinkVars[n].name[0] != 0) {
			strcpy(tmp_str, MavLinkVars[n].name);
			if (MavLinkVars[n].group[0] == 0) {
				for (n2 = 0; n2 < strlen(tmp_str) && n2 < 6; n2++) {
					if (tmp_str[n2] == '_') {
						break;
					}
				}
				strncpy(MavLinkVars[n].group, tmp_str, 17);
			}
			flag = 0;
			for (n2 = 0; n2 < MAVLINK_PARAMETER_MAX; n2++) {
				if (strcmp(mavlink_subs[n2], MavLinkVars[n].group) == 0) {
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				if (strcmp(MavLinkVars[n].group, sub) == 0) {
					sprintf(tmp_str2, "<TR class=\"sec\"><TD><A href=\"/mavlink.html?%s\">%s</A></TD></TR>", MavLinkVars[n].group, MavLinkVars[n].group);
				} else {
					sprintf(tmp_str2, "<TR class=\"first\"><TD><A href=\"/mavlink.html?%s\">%s</A></TD></TR>", MavLinkVars[n].group, MavLinkVars[n].group);
				}
				strcat(content, tmp_str2);
				for (n2 = 0; n2 < MAVLINK_PARAMETER_MAX; n2++) {
					if (mavlink_subs[n2][0] == 0) {
						strcpy(mavlink_subs[n2], MavLinkVars[n].group);
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
		if (MavLinkVars[n].name[0] != 0 && (sub[0] == 0 || strncmp(MavLinkVars[n].name, sub, strlen(sub)) == 0 || strcmp(MavLinkVars[n].group, sub) == 0)) {
			lc = 1 - lc;
			if (lc == 0) {
				strcat(content, "<TR class=\"first\">");
			} else {
				strcat(content, "<TR class=\"sec\">");
			}
			sprintf(tmp_str, "<TD>%s (%s)</TD>\n", MavLinkVars[n].name, MavLinkVars[n].display);
			strcat(content, tmp_str);
			if (MavLinkVars[n].values[0] != 0) {
				int n2 = 0;
				sprintf(tmp_str, "<TD><SELECT class=\"form-input\" onchange=\"check_option('%s');\" id=\"%s\">\n", MavLinkVars[n].name, MavLinkVars[n].name);
				strcat(content, tmp_str);
				tmp_str2[0] = 0;
				for (n2 = (int)MavLinkVars[n].min; n2 <= (int)MavLinkVars[n].max; n2++) {
					tmp_str2[0] = 0;
					mavlink_meta_get_option(n2, MavLinkVars[n].name, tmp_str2);
					if (tmp_str2[0] != 0) {
						if (n2 == (int)MavLinkVars[n].value) {
							sprintf(tmp_str, "<OPTION value=\"%i\" selected>%s</OPTION>\n", n2, tmp_str2);
						} else {
							sprintf(tmp_str, "<OPTION value=\"%i\">%s</OPTION>\n", n2, tmp_str2);
						}
						strcat(content, tmp_str);
					}
				}
				strcat(content, "</SELECT></TD>");
			} else if (MavLinkVars[n].bits[0] != 0) {
				sprintf(tmp_str, "<TD>\n");
				strcat(content, tmp_str);
				int n2 = 0;
				strcat(content, "<SCRIPT>\n");
				sprintf(tmp_str, "function check_%s() {\n", MavLinkVars[n].name);
				strcat(content, tmp_str);
				strcat(content, "	var value = 0;\n");
				tmp_str2[0] = 0;
				for (n2 = (int)MavLinkVars[n].min; n2 <= (int)MavLinkVars[n].max; n2++) {
					tmp_str2[0] = 0;
					mavlink_meta_get_bits(n2, MavLinkVars[n].name, tmp_str2);
					if (tmp_str2[0] != 0) {
						sprintf(tmp_str, "	if (document.getElementsByName(\"%s-%s\")[0].checked) {\n", MavLinkVars[n].name, tmp_str2);
						strcat(content, tmp_str);
						sprintf(tmp_str, "		value |= (1<<%i);\n", n2);
						strcat(content, tmp_str);
						strcat(content, "	}\n");
					}
				}
				strcat(content, "	xmlHttp = new XMLHttpRequest();\n");
				sprintf(tmp_str, "	xmlHttp.open(\"GET\", \"/mavlink_value_set?%s=\" + value, true);\n", MavLinkVars[n].name);
				strcat(content, tmp_str);
				strcat(content, "	xmlHttp.send(null);\n");
				strcat(content, "}\n");
				strcat(content, "</SCRIPT>\n");
				tmp_str2[0] = 0;
				for (n2 = (int)MavLinkVars[n].min; n2 <= (int)MavLinkVars[n].max; n2++) {
					tmp_str2[0] = 0;
					mavlink_meta_get_bits(n2, MavLinkVars[n].name, tmp_str2);
					if (tmp_str2[0] != 0) {
						if ((int)MavLinkVars[n].value & (1<<n2)) {
							sprintf(tmp_str, "<NOBR><INPUT class=\"form-input\" onchange=\"check_%s();\" type=\"checkbox\" name=\"%s-%s\" value=\"%i\" checked>%s</NOBR>\n", MavLinkVars[n].name, MavLinkVars[n].name, tmp_str2, n2, tmp_str2);
						} else {
							sprintf(tmp_str, "<NOBR><INPUT class=\"form-input\" onchange=\"check_%s();\" type=\"checkbox\" name=\"%s-%s\" value=\"%i\">%s</NOBR>\n", MavLinkVars[n].name, MavLinkVars[n].name, tmp_str2, n2, tmp_str2);
						}
						strcat(content, tmp_str);
					}
				}
				strcat(content, "</TD>");
			} else {
				sprintf(tmp_str, "<TD><INPUT class=\"form-input\" onchange=\"check_value('%s');\" id=\"%s\" value=\"%f\" type=\"text\"></TD>\n", MavLinkVars[n].name, MavLinkVars[n].name, MavLinkVars[n].value);
				strcat(content, tmp_str);
			}
			sprintf(tmp_str, "<TD>%s&nbsp;</TD><TD>%0.4f</TD><TD>%0.4f</TD><TD>%0.4f</TD></TR>\n", MavLinkVars[n].desc, MavLinkVars[n].min, MavLinkVars[n].max, MavLinkVars[n].onload);
			strcat(content, tmp_str);
		}
	}
	strcat(content, "</TABLE><BR><BR>\n");
	strcat(content, "</TD></TR></TABLE>\n");
	webserv_html_stop(content);
}


void mavlink_web_get (char *url, char *content, char *type) {
	char tmp_str[512];
	if (strncmp(url, "/mavlink_value_set?", 19) == 0) {
		char name[20];
		float value = 0.0;
		int ntype = 0;
		sscanf(url + 19, "%[0-9a-zA-Z_]=%f&%i", name, &value, &ntype);
		mavlink_set_value(name, value, ntype, -1);
		mavlink_send_value(name, value, ntype);
		sprintf(content, "mavlink set value: %s to %f (type:%i)\n", name, value, ntype);
		strcpy(type, "text/plain");
	} else if (strncmp(url, "/mavlink.html?", 14) == 0) {
		char sub[128];
		sscanf(url + 14, "%[0-9a-zA-Z_]", sub);
		mavlink_html_page(content, sub);
		strcpy(type, "text/html");
	} else if (strncmp(url, "/mavlink.html", 13) == 0) {
		mavlink_html_page(content, "");
		strcpy(type, "text/html");
	} else if (strncmp(url, "/mavlink_value_get", 18) == 0) {
		uint16_t n = 0;
		strcpy(content, "# MAV ID  COMPONENT ID  PARAM NAME  VALUE (FLOAT) TYPE (INT)\n");
		for (n = 0; n < MAVLINK_PARAMETER_MAX; n++) {
			if (MavLinkVars[n].name[0] != 0) {
				sprintf(tmp_str, "%i %i %s %f %i\n", ModelData.sysid, ModelData.compid, MavLinkVars[n].name, MavLinkVars[n].value, MavLinkVars[n].type);
				strcat(content, tmp_str);
			}
		}
		strcpy(type, "text/plain");
	}
}

