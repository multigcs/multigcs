
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <serial.h>
#include <model.h>
#include <userdata.h>
#include <main.h>
#include <my_mavlink.h>
#include <screen_map.h>


#define UDP_BUFLEN 2042
#define UDP_PORT 14550

int16_t mission_max = -1;
int serial_fd_mavlink = -1;
ValueList MavLinkVars[500];
ValueList selMavLinkVars[500];
ValueList mainMavLinkVars[500];
uint8_t mavlink_update_yaw = 0;
uint8_t droneType = 1;
uint8_t autoPilot = 3;
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


int mavlink_update (void) {
	gcs_update();
	return(0);
}

uint8_t mavlink_init (char *port, uint32_t baud) {
	int n = 0;
	mavlink_maxparam = 0;
	mavlink_foundparam = 0;
	printf("init mavlink serial port...\n");
	serial_fd_mavlink = serial_open(port, baud);
	for (n = 0; n < 500; n++) {
		MavLinkVars[n].name[0] = 0;
		MavLinkVars[n].value = 0.0;
		MavLinkVars[n].id = -1;

		selMavLinkVars[n].name[0] = 0;
		selMavLinkVars[n].value = 0.0;
		selMavLinkVars[n].id = -1;

		mainMavLinkVars[n].name[0] = 0;
		mainMavLinkVars[n].value = 0.0;
		mainMavLinkVars[n].id = -1;
	}

	thread_udp = SDL_CreateThread(mavlink_udp, NULL);
	if ( thread_udp == NULL ) {
		fprintf(stderr, "Thread konnte nicht gestartet werden (mavlink_udp): %s\n", SDL_GetError());
		return 0;
	}

	return 0;
}

void mavlink_exit (void) {
	printf("* udp-thread kill\n");
	SDL_KillThread(thread_udp);

	if (serial_fd_mavlink >= 0) {
		close(serial_fd_mavlink);
		serial_fd_mavlink = -1;
	}
}

void stop_feeds (void) {
	printf("Stopping feeds!\n");
	mavlink_message_t msg1;
	mavlink_msg_request_data_stream_pack(127, 0, &msg1, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_ALL, 0, 0);
	send_message(&msg1);
}

void mavlink_send_value (char *name, float val) {
	mavlink_message_t msg;
	mavlink_msg_param_set_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, name, val, 9);
	send_message(&msg);
}

void gcs_handleMessage(mavlink_message_t* msg) {
	mavlink_message_t msg2;
	char sysmsg_str[1024];
	switch (msg->msgid) {
		case MAVLINK_MSG_ID_HEARTBEAT: {
			mavlink_heartbeat_t packet;
			mavlink_msg_heartbeat_decode(msg, &packet);
			droneType = packet.type;
			autoPilot = packet.autopilot;

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
//			printf("Heartbeat: %i, %i, %i\n", ModelData.armed, ModelData.mode, ModelData.status);
			ModelData.heartbeat = 100;
//			sprintf(sysmsg_str, "Heartbeat: %i", (int)time(0));
			if ((*msg).sysid != 0xff) {
				ModelData.sysid = (*msg).sysid;
				ModelData.compid = (*msg).compid;
				if (mavlink_maxparam == 0) {
					start_feeds();
				}
			}
			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_RC_CHANNELS_SCALED: {
			mavlink_rc_channels_scaled_t packet;
			mavlink_msg_rc_channels_scaled_decode(msg, &packet);
//			printf("Radio: %i,%i,%i\n", packet.chan1_scaled, packet.chan2_scaled, packet.chan3_scaled);

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

			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_SCALED_PRESSURE: {
			mavlink_scaled_pressure_t packet;
			mavlink_msg_scaled_pressure_decode(msg, &packet);
//			printf("BAR;%i;%0.2f;%0.2f;%0.2f\n", time(0), packet.press_abs, packet.press_diff, packet.temperature / 100.0);
//			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_ATTITUDE: {
			mavlink_attitude_t packet;
			mavlink_msg_attitude_decode(msg, &packet);
			ModelData.roll = toDeg(packet.roll);
			ModelData.pitch = toDeg(packet.pitch);
			if (toDeg(packet.yaw) < 0.0) {
				ModelData.yaw = 360.0 + toDeg(packet.yaw);
			} else {
				ModelData.yaw = toDeg(packet.yaw);
			}
			mavlink_update_yaw = 1;
//			printf("ATT;%i;%0.2f;%0.2f;%0.2f\n", time(0), toDeg(packet.roll), toDeg(packet.pitch), toDeg(packet.yaw));

			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_SCALED_IMU: {
//			printf("SCALED_IMU\n");
			break;
		}
		case MAVLINK_MSG_ID_GPS_RAW_INT: {
			mavlink_gps_raw_int_t packet;
			mavlink_msg_gps_raw_int_decode(msg, &packet);
			if (packet.lat != 0.0) {
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
//			printf("RC_CHANNELS_RAW\n");
			break;
		}
		case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW: {
//			printf("SERVO_OUTPUT_RAW\n");
			break;
		}
		case MAVLINK_MSG_ID_SYS_STATUS: {
			mavlink_sys_status_t packet;
			mavlink_msg_sys_status_decode(msg, &packet);
//			printf("%0.1f %%, %0.3f V)\n", packet.load / 10.0, packet.voltage_battery / 1000.0);
			ModelData.voltage = packet.voltage_battery / 1000.0;
			ModelData.load = packet.load / 10.0;
			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_STATUSTEXT: {
			mavlink_statustext_t packet;
			mavlink_msg_statustext_decode(msg, &packet);
			printf("## %s ##\n", packet.text);
			sys_message((char *)packet.text);
			redraw_flag = 1;
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
			sprintf(sysmsg_str, "PARAM_VALUE (%i/%i): #%s# = %f", packet.param_index + 1, packet.param_count, var, packet.param_value);
			printf("%s\n", sysmsg_str);
			sys_message(sysmsg_str);
			mavlink_maxparam = packet.param_count;
			mavlink_timeout = 0;
			uint16_t n = 0;
			uint8_t flag = 0;
			for (n = 0; n < 500; n++) {
				if (strcmp(MavLinkVars[n].name, var) == 0 && (MavLinkVars[n].id == packet.param_index || MavLinkVars[n].id == -1)) {
					MavLinkVars[n].value = packet.param_value;
					MavLinkVars[n].id = packet.param_index;
					flag = 1;
					break;
				}
			}
			if (flag == 0) {
				for (n = 0; n < 500; n++) {
					if (MavLinkVars[n].name[0] == 0) {
						strcpy(MavLinkVars[n].name, var);
						MavLinkVars[n].value = packet.param_value;
						MavLinkVars[n].id = packet.param_index;
						break;
					}
				}
			}
			redraw_flag = 1;
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
				send_message(&msg2);
			}
			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_MISSION_ACK: {
			printf("Mission-Transfer ACK\n");
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
					printf("WORKAROUND: first WP == HOME ?\n");
				}
			}

			sprintf(sysmsg_str, "sending Waypoint (%i): %s\n", id, WayPoints[1 + id2].name);
			sys_message(sysmsg_str);
			if (strcmp(WayPoints[1 + id2].command, "WAYPOINT") == 0) {
				printf("Type: MAV_CMD_NAV_WAYPOINT\n");
				type = MAV_CMD_NAV_WAYPOINT;
			} else if (strcmp(WayPoints[1 + id2].command, "RTL") == 0) {
				printf("Type: MAV_CMD_NAV_RETURN_TO_LAUNCH\n");
				type = MAV_CMD_NAV_RETURN_TO_LAUNCH;
			} else if (strcmp(WayPoints[1 + id2].command, "LAND") == 0) {
				printf("Type: MAV_CMD_NAV_LAND\n");
				type = MAV_CMD_NAV_LAND;
			} else if (strcmp(WayPoints[1 + id2].command, "TAKEOFF") == 0) {
				printf("Type: MAV_CMD_NAV_TAKEOFF\n");
				type = MAV_CMD_NAV_TAKEOFF;
			} else {
				printf("Type: UNKNOWN\n");
				type = MAV_CMD_NAV_WAYPOINT;
			}

			sprintf(sysmsg_str, "SENDING MISSION_ITEM: %i: %f, %f, %f\n", id, WayPoints[1 + id2].p_lat, WayPoints[1 + id2].p_long, WayPoints[1 + id2].p_alt);
			printf("%s\n", sysmsg_str);


			mavlink_msg_mission_item_pack(127, 0, &msg2, ModelData.sysid, ModelData.compid, id, 0, type, 0.0, 0.0, WayPoints[1 + id2].radius, WayPoints[1 + id2].wait, WayPoints[1 + id2].orbit, WayPoints[1 + id2].yaw, WayPoints[1 + id2].p_lat, WayPoints[1 + id2].p_long, WayPoints[1 + id2].p_alt);
			send_message(&msg2);
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

			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_MISSION_ITEM: {
			mavlink_mission_item_t packet;
			mavlink_msg_mission_item_decode(msg, &packet);

			sprintf(sysmsg_str, "RECEIVED MISSION_ITEM: %i/%i: %f, %f, %f (%i)\n", packet.seq, mission_max, packet.x, packet.y, packet.z, packet.frame);
			printf("%s\n", sysmsg_str);
			sys_message(sysmsg_str);

			if (packet.seq < mission_max - 1) {
				mavlink_msg_mission_request_pack(127, 0, &msg2, ModelData.sysid, ModelData.compid, packet.seq + 1);
				send_message(&msg2);
			} else {
				mavlink_msg_mission_ack_pack(127, 0, &msg2, ModelData.sysid, ModelData.compid, 15);
				send_message(&msg2);
			}

			if (ModelData.teletype == TELETYPE_MEGAPIRATE_NG || ModelData.teletype == TELETYPE_ARDUPILOT) {
				if (packet.seq > 0) {
					packet.seq = packet.seq - 1;
				} else {
					printf("WORKAROUND: ignore first WP\n");
					break;
				}
			}

			printf("getting WP(%i): %f, %f\n", packet.seq, packet.x, packet.y);

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
			strcpy(WayPoints[1 + packet.seq + 1].name, "");
			strcpy(WayPoints[1 + packet.seq + 1].command, "");



/*
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

GCS_MAVLink/message_definitions_v1.0/common.xml:               <entry value="0" name="MAV_FRAME_GLOBAL">
GCS_MAVLink/message_definitions_v1.0/common.xml:               <entry value="1" name="MAV_FRAME_LOCAL_NED">
GCS_MAVLink/message_definitions_v1.0/common.xml:               <entry value="2" name="MAV_FRAME_MISSION">
GCS_MAVLink/message_definitions_v1.0/common.xml:               <entry value="3" name="MAV_FRAME_GLOBAL_RELATIVE_ALT">
GCS_MAVLink/message_definitions_v1.0/common.xml:               <entry value="4" name="MAV_FRAME_LOCAL_ENU">
*/

			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_MISSION_CURRENT: {
			mavlink_mission_current_t packet;
			mavlink_msg_mission_current_decode(msg, &packet);
//			printf("## Active_WP %f ##\n", packet.seq);
			uav_active_waypoint = (uint8_t)packet.seq;
			break;
		}
		case MAVLINK_MSG_ID_RAW_IMU: {
			mavlink_raw_imu_t packet;
			mavlink_msg_raw_imu_decode(msg, &packet);
/*
			printf("## IMU_RAW_ACC_X %i ##\n", packet.xacc);
			printf("## IMU_RAW_ACC_Y %i ##\n", packet.yacc);
			printf("## IMU_RAW_ACC_Z %i ##\n", packet.zacc);
			printf("## IMU_RAW_GYRO_X %i ##\n", packet.xgyro);
			printf("## IMU_RAW_GYRO_Y %i ##\n", packet.ygyro);
			printf("## IMU_RAW_GYRO_Z %i ##\n", packet.zgyro);
			printf("## IMU_RAW_MAG_X %i ##\n", packet.xmag);
			printf("## IMU_RAW_MAG_Y %i ##\n", packet.ymag);
			printf("## IMU_RAW_MAG_Z %i ##\n", packet.zmag);
*/
			ModelData.acc_x = (float)packet.xacc / 1000.0;
			ModelData.acc_y = (float)packet.yacc / 1000.0;
			ModelData.acc_z = (float)packet.zacc / 1000.0;
			ModelData.gyro_x = (float)packet.zgyro;
			ModelData.gyro_y = (float)packet.zgyro;
			ModelData.gyro_z = (float)packet.zgyro;
			redraw_flag = 1;
			break;
		}
		case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT: {
			mavlink_nav_controller_output_t packet;
			mavlink_msg_nav_controller_output_decode(msg, &packet);
/*
nav_roll
nav_pitch
alt_error
aspd_error
xtrack_error
nav_bearing
target_bearing
wp_dist
*/

			break;
		}
		case MAVLINK_MSG_ID_VFR_HUD: {
			mavlink_vfr_hud_t packet;
			mavlink_msg_vfr_hud_decode(msg, &packet);

//			printf("## pa %f ##\n", packet.airspeed);
//			printf("## pg %f ##\n", packet.groundspeed);
//			printf("## palt %f ##\n", packet.alt);

			if (GPS_found == 0) {
				ModelData.p_alt = packet.alt;
			}

//			printf("## pc %f ##\n", packet.climb);
//			printf("## ph %i ##\n", packet.heading);
//			printf("## pt %i ##\n", packet.throttle);

			break;
		}


		case MAVLINK_MSG_ID_RADIO: {
			mavlink_radio_t packet;
			mavlink_msg_radio_decode(msg, &packet);

			printf("## rxerrors %i ##\n", packet.rxerrors);
			printf("## fixed %i ##\n", packet.fixed);
			printf("## rssi %i ##\n", packet.rssi);
			printf("## remrssi %i ##\n", packet.remrssi);
			printf("## txbuf %i ##\n", packet.txbuf);
			printf("## noise %i ##\n", packet.noise);
			printf("## remnoise %i ##\n", packet.remnoise);

			break;
		}



		default: {
//			printf("	## MSG_ID == %i ##\n", msg->msgid);
			break;
		}
	}
}

void read_waypoints (void) {
	printf("reading Waypoints\n");
	mavlink_message_t msg;
	mavlink_msg_mission_request_list_pack(127, 0, &msg, ModelData.sysid, ModelData.compid);
	send_message(&msg);
}

void save_to_flash (void) {
	printf("save values to flash\n");
	mavlink_message_t msg;
	mavlink_msg_command_long_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_CMD_PREFLIGHT_STORAGE, 0, 1.0f, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	send_message(&msg);
}

void send_waypoints (void) {
	mavlink_message_t msg;
	mavlink_msg_mission_clear_all_pack(127, 0, &msg, ModelData.sysid, ModelData.compid);
	send_message(&msg);
	usleep(100000);
	uint16_t n = 0;
	for (n = 1; n < MAX_WAYPOINTS; n++) {
		if (WayPoints[n].p_lat == 0.0) {
			break;
		}
	}

	if (ModelData.teletype == TELETYPE_MEGAPIRATE_NG || ModelData.teletype == TELETYPE_ARDUPILOT) {
		printf("WORKAROUND: MEGAPIRATE_NG: fake one WP\n");
		n++;
	}

	printf("sending Waypoints (%i)\n", n - 1);
	mavlink_msg_mission_count_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, n - 1);
	send_message(&msg);
}


static struct sockaddr_in si_me, si_other;
static int s, slen = sizeof(si_other) , recv_len;

void send_message (mavlink_message_t* msg) {
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	printf("send_msg...\n");

	uint16_t len = mavlink_msg_to_send_buffer(buf, msg);
	uint16_t i = 0;
	for(i = 0; i < len; i++) {
		uint8_t c = buf[i];
		write(serial_fd_mavlink, &c, 1);
	}

	if (mavlink_udp_active == 1) {
		if (sendto(s, buf, len, 0, (struct sockaddr *)&si_other, slen) == -1) {
			printf("error: sendto udp()\n");
		}
	}

}

uint8_t mavlink_connection_status (void) {
	if (serial_fd_mavlink == -1) {
		return 0;
	}
	return last_connection;
}

void gcs_update (void) {
	if (serial_fd_mavlink == -1) {
		return;
	}
	uint8_t c = 0;
	uint16_t n = 0;
//	uint16_t id = 0;
	mavlink_message_t msg;
	mavlink_status_t status;
	while ((res = read(serial_fd_mavlink, serial_buf, 200)) > 0) {
		last_connection = time(0);
		for (n = 0; n < res; n++) {
			c = serial_buf[n];
			//printf("%i", c);
			if(mavlink_parse_char(0, c, &msg, &status)) {
				gcs_handleMessage(&msg);
			}
		}

	}
/*
	if (mavlink_timeout++ > 100 && mavlink_foundparam != mavlink_maxparam) {
		// checking missing parameters
		mavlink_foundparam = 0;
		for (id = 0; id < mavlink_maxparam; id++) {
			c = 0;
			for (n = 0; n < 500; n++) {
				if (MavLinkVars[n].id == id) {
					c = 1;
					mavlink_foundparam++;
					break;
				}
			}
			if (c == 0) {
				printf("missing id: %i\n", id);
				param_get_id(id);
				mavlink_timeout = 0;
			}
		}
		printf("parameters found: %i/%i\n", mavlink_foundparam, mavlink_maxparam);
	}
*/
}

void param_get_id (uint16_t id) {
	printf("mavlink: get id: %i\n", id);
	mavlink_message_t msg;
	mavlink_msg_param_request_read_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, NULL, id);
	send_message(&msg);
}

#define MAV_DATA_STREAM_POSITION_ACTIVE 1
#define MAV_DATA_STREAM_RAW_SENSORS_ACTIVE 1
#define MAV_DATA_STREAM_EXTENDED_STATUS_ACTIVE 1
#define MAV_DATA_STREAM_RAW_CONTROLLER_ACTIVE 1
#define MAV_DATA_STREAM_EXTRA1_ACTIVE 1
#define MAV_DATA_STREAM_EXTRA2_ACTIVE 1

#define MAV_DATA_STREAM_POSITION_RATE 10
#define MAV_DATA_STREAM_RAW_SENSORS_RATE 10
#define MAV_DATA_STREAM_EXTENDED_STATUS_RATE 10
#define MAV_DATA_STREAM_RAW_CONTROLLER_RATE 10
#define MAV_DATA_STREAM_EXTRA1_RATE 10
#define MAV_DATA_STREAM_EXTRA2_RATE 10

void start_feeds (void) {
	mavlink_message_t msg;
	mavlink_timeout = 0;
	printf("Starting feeds!\n");
	mavlink_msg_param_request_list_pack(127, 0, &msg, ModelData.sysid, ModelData.compid);
	send_message(&msg);
	SDL_Delay(10);

	mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_RAW_SENSORS, MAV_DATA_STREAM_RAW_SENSORS_RATE, MAV_DATA_STREAM_RAW_SENSORS_ACTIVE);
	send_message(&msg);
	SDL_Delay(10);

	if (ModelData.teletype == TELETYPE_MEGAPIRATE_NG || ModelData.teletype == TELETYPE_ARDUPILOT) {
		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_EXTENDED_STATUS, MAV_DATA_STREAM_EXTENDED_STATUS_RATE, MAV_DATA_STREAM_EXTENDED_STATUS_ACTIVE);
		send_message(&msg);
		SDL_Delay(10);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_RAW_CONTROLLER, MAV_DATA_STREAM_RAW_CONTROLLER_RATE, MAV_DATA_STREAM_RAW_CONTROLLER_ACTIVE);
		send_message(&msg);
		SDL_Delay(10);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_POSITION, MAV_DATA_STREAM_POSITION_RATE, MAV_DATA_STREAM_POSITION_ACTIVE);
		send_message(&msg);
		SDL_Delay(10);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_EXTRA1, MAV_DATA_STREAM_EXTRA1_RATE, MAV_DATA_STREAM_EXTRA1_ACTIVE);
		send_message(&msg);
		SDL_Delay(10);

		mavlink_msg_request_data_stream_pack(127, 0, &msg, ModelData.sysid, ModelData.compid, MAV_DATA_STREAM_EXTRA2, MAV_DATA_STREAM_EXTRA2_RATE, MAV_DATA_STREAM_EXTRA2_ACTIVE);
		send_message(&msg);
		SDL_Delay(10);
	}
}

int mavlink_udp (void *data) {
	printf("starting udp thread\n");
	mavlink_message_t msg;
	mavlink_status_t status;
	char buf[UDP_BUFLEN];
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		printf("socket\n");
		return 0;
	}
	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(UDP_PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1) {
		printf("bind\n");
		return 0;
	}
	while (gui_running == 1) {
		fflush(stdout);
		if ((recv_len = recvfrom(s, buf, UDP_BUFLEN, 0, (struct sockaddr *)&si_other, (socklen_t *)&slen)) == -1) {
			printf("recvfrom()\n");
			return 0;
		}
		int n = 0;
		for (n = 0; n < recv_len; n++) {
			if(mavlink_parse_char(1, buf[n], &msg, &status)) {
				gcs_handleMessage(&msg);
				mavlink_udp_active = 1;
			}
		}
	}
	close(s);
	return 0;
}

