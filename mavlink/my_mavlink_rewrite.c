
#include <all.h>
#include <mavlink/GCS_MAVLink/include/mavlink/v1.0/autoquad/mavlink_msg_aq_telemetry_f.h>
#include <mavlink/GCS_MAVLink/include/mavlink/v1.0/pixhawk/mavlink_msg_set_netid.h>

uint8_t mavlink_target_rewrite (mavlink_message_t* msg) {
	uint8_t modelid = 0;
	switch (msg->msgid) {
		case 0: {
			break;
		}
#ifdef MAVLINK_MSG_ID_CAMERA_FEEDBACK
		case MAVLINK_MSG_ID_CAMERA_FEEDBACK: {
			mavlink_camera_feedback_t packet;
			mavlink_msg_camera_feedback_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_camera_feedback_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_CAMERA_STATUS
		case MAVLINK_MSG_ID_CAMERA_STATUS: {
			mavlink_camera_status_t packet;
			mavlink_msg_camera_status_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_camera_status_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_DIGICAM_CONFIGURE
		case MAVLINK_MSG_ID_DIGICAM_CONFIGURE: {
			mavlink_digicam_configure_t packet;
			mavlink_msg_digicam_configure_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_digicam_configure_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_DIGICAM_CONTROL
		case MAVLINK_MSG_ID_DIGICAM_CONTROL: {
			mavlink_digicam_control_t packet;
			mavlink_msg_digicam_control_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_digicam_control_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FENCE_FETCH_POINT
		case MAVLINK_MSG_ID_FENCE_FETCH_POINT: {
			mavlink_fence_fetch_point_t packet;
			mavlink_msg_fence_fetch_point_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_fence_fetch_point_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FENCE_POINT
		case MAVLINK_MSG_ID_FENCE_POINT: {
			mavlink_fence_point_t packet;
			mavlink_msg_fence_point_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_fence_point_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MOUNT_CONFIGURE
		case MAVLINK_MSG_ID_MOUNT_CONFIGURE: {
			mavlink_mount_configure_t packet;
			mavlink_msg_mount_configure_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_mount_configure_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MOUNT_CONTROL
		case MAVLINK_MSG_ID_MOUNT_CONTROL: {
			mavlink_mount_control_t packet;
			mavlink_msg_mount_control_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_mount_control_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MOUNT_STATUS
		case MAVLINK_MSG_ID_MOUNT_STATUS: {
			mavlink_mount_status_t packet;
			mavlink_msg_mount_status_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_mount_status_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_RALLY_FETCH_POINT
		case MAVLINK_MSG_ID_RALLY_FETCH_POINT: {
			mavlink_rally_fetch_point_t packet;
			mavlink_msg_rally_fetch_point_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_rally_fetch_point_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_RALLY_POINT
		case MAVLINK_MSG_ID_RALLY_POINT: {
			mavlink_rally_point_t packet;
			mavlink_msg_rally_point_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_rally_point_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_MAG_OFFSETS
		case MAVLINK_MSG_ID_SET_MAG_OFFSETS: {
			mavlink_set_mag_offsets_t packet;
			mavlink_msg_set_mag_offsets_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_set_mag_offsets_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_6DOF_SETPOINT
		case MAVLINK_MSG_ID_6DOF_SETPOINT: {
			mavlink_6dof_setpoint_t packet;
			mavlink_msg_6dof_setpoint_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_6dof_setpoint_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_8DOF_SETPOINT
		case MAVLINK_MSG_ID_8DOF_SETPOINT: {
			mavlink_8dof_setpoint_t packet;
			mavlink_msg_8dof_setpoint_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_8dof_setpoint_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL
		case MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL: {
			mavlink_change_operator_control_t packet;
			mavlink_msg_change_operator_control_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_change_operator_control_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_COMMAND_INT
		case MAVLINK_MSG_ID_COMMAND_INT: {
			mavlink_command_int_t packet;
			mavlink_msg_command_int_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_command_int_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_COMMAND_LONG
		case MAVLINK_MSG_ID_COMMAND_LONG: {
			mavlink_command_long_t packet;
			mavlink_msg_command_long_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_command_long_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FILE_TRANSFER_PROTOCOL
		case MAVLINK_MSG_ID_FILE_TRANSFER_PROTOCOL: {
			mavlink_file_transfer_protocol_t packet;
			mavlink_msg_file_transfer_protocol_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_file_transfer_protocol_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_GPS_INJECT_DATA
		case MAVLINK_MSG_ID_GPS_INJECT_DATA: {
			mavlink_gps_inject_data_t packet;
			mavlink_msg_gps_inject_data_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_gps_inject_data_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LOG_ERASE
		case MAVLINK_MSG_ID_LOG_ERASE: {
			mavlink_log_erase_t packet;
			mavlink_msg_log_erase_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_log_erase_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LOG_REQUEST_DATA
		case MAVLINK_MSG_ID_LOG_REQUEST_DATA: {
			mavlink_log_request_data_t packet;
			mavlink_msg_log_request_data_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_log_request_data_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LOG_REQUEST_END
		case MAVLINK_MSG_ID_LOG_REQUEST_END: {
			mavlink_log_request_end_t packet;
			mavlink_msg_log_request_end_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_log_request_end_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LOG_REQUEST_LIST
		case MAVLINK_MSG_ID_LOG_REQUEST_LIST: {
			mavlink_log_request_list_t packet;
			mavlink_msg_log_request_list_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_log_request_list_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_ACK
		case MAVLINK_MSG_ID_MISSION_ACK: {
			mavlink_mission_ack_t packet;
			mavlink_msg_mission_ack_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_mission_ack_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_CLEAR_ALL
		case MAVLINK_MSG_ID_MISSION_CLEAR_ALL: {
			mavlink_mission_clear_all_t packet;
			mavlink_msg_mission_clear_all_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_mission_clear_all_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_COUNT
		case MAVLINK_MSG_ID_MISSION_COUNT: {
			mavlink_mission_count_t packet;
			mavlink_msg_mission_count_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_mission_count_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_ITEM
		case MAVLINK_MSG_ID_MISSION_ITEM: {
			mavlink_mission_item_t packet;
			mavlink_msg_mission_item_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_mission_item_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_ITEM_INT
		case MAVLINK_MSG_ID_MISSION_ITEM_INT: {
			mavlink_mission_item_int_t packet;
			mavlink_msg_mission_item_int_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_mission_item_int_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_REQUEST
		case MAVLINK_MSG_ID_MISSION_REQUEST: {
			mavlink_mission_request_t packet;
			mavlink_msg_mission_request_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_mission_request_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_REQUEST_LIST
		case MAVLINK_MSG_ID_MISSION_REQUEST_LIST: {
			mavlink_mission_request_list_t packet;
			mavlink_msg_mission_request_list_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_mission_request_list_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_REQUEST_PARTIAL_LIST
		case MAVLINK_MSG_ID_MISSION_REQUEST_PARTIAL_LIST: {
			mavlink_mission_request_partial_list_t packet;
			mavlink_msg_mission_request_partial_list_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_mission_request_partial_list_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_SET_CURRENT
		case MAVLINK_MSG_ID_MISSION_SET_CURRENT: {
			mavlink_mission_set_current_t packet;
			mavlink_msg_mission_set_current_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_mission_set_current_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_WRITE_PARTIAL_LIST
		case MAVLINK_MSG_ID_MISSION_WRITE_PARTIAL_LIST: {
			mavlink_mission_write_partial_list_t packet;
			mavlink_msg_mission_write_partial_list_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_mission_write_partial_list_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_PARAM_REQUEST_LIST
		case MAVLINK_MSG_ID_PARAM_REQUEST_LIST: {
			mavlink_param_request_list_t packet;
			mavlink_msg_param_request_list_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_param_request_list_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_PARAM_REQUEST_READ
		case MAVLINK_MSG_ID_PARAM_REQUEST_READ: {
			mavlink_param_request_read_t packet;
			mavlink_msg_param_request_read_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_param_request_read_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_PARAM_SET
		case MAVLINK_MSG_ID_PARAM_SET: {
			mavlink_param_set_t packet;
			mavlink_msg_param_set_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_param_set_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_PING
		case MAVLINK_MSG_ID_PING: {
			mavlink_ping_t packet;
			mavlink_msg_ping_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_ping_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_RC_CHANNELS_OVERRIDE
		case MAVLINK_MSG_ID_RC_CHANNELS_OVERRIDE: {
			mavlink_rc_channels_override_t packet;
			mavlink_msg_rc_channels_override_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_rc_channels_override_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_REQUEST_DATA_STREAM
		case MAVLINK_MSG_ID_REQUEST_DATA_STREAM: {
			mavlink_request_data_stream_t packet;
			mavlink_msg_request_data_stream_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_request_data_stream_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SAFETY_SET_ALLOWED_AREA
		case MAVLINK_MSG_ID_SAFETY_SET_ALLOWED_AREA: {
			mavlink_safety_set_allowed_area_t packet;
			mavlink_msg_safety_set_allowed_area_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_safety_set_allowed_area_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_ATTITUDE_TARGET
		case MAVLINK_MSG_ID_SET_ATTITUDE_TARGET: {
			mavlink_set_attitude_target_t packet;
			mavlink_msg_set_attitude_target_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_set_attitude_target_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_GPS_GLOBAL_ORIGIN
		case MAVLINK_MSG_ID_SET_GPS_GLOBAL_ORIGIN: {
			mavlink_set_gps_global_origin_t packet;
			mavlink_msg_set_gps_global_origin_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_set_gps_global_origin_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_LOCAL_POSITION_SETPOINT
		case MAVLINK_MSG_ID_SET_LOCAL_POSITION_SETPOINT: {
			mavlink_set_local_position_setpoint_t packet;
			mavlink_msg_set_local_position_setpoint_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_set_local_position_setpoint_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_MODE
		case MAVLINK_MSG_ID_SET_MODE: {
			mavlink_set_mode_t packet;
			mavlink_msg_set_mode_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_set_mode_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SETPOINT_6DOF
		case MAVLINK_MSG_ID_SETPOINT_6DOF: {
			mavlink_setpoint_6dof_t packet;
			mavlink_msg_setpoint_6dof_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_setpoint_6dof_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SETPOINT_8DOF
		case MAVLINK_MSG_ID_SETPOINT_8DOF: {
			mavlink_setpoint_8dof_t packet;
			mavlink_msg_setpoint_8dof_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_setpoint_8dof_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_POSITION_TARGET_GLOBAL_INT
		case MAVLINK_MSG_ID_SET_POSITION_TARGET_GLOBAL_INT: {
			mavlink_set_position_target_global_int_t packet;
			mavlink_msg_set_position_target_global_int_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_set_position_target_global_int_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_POSITION_TARGET_LOCAL_NED
		case MAVLINK_MSG_ID_SET_POSITION_TARGET_LOCAL_NED: {
			mavlink_set_position_target_local_ned_t packet;
			mavlink_msg_set_position_target_local_ned_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_set_position_target_local_ned_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_QUAD_MOTORS_SETPOINT
		case MAVLINK_MSG_ID_SET_QUAD_MOTORS_SETPOINT: {
			mavlink_set_quad_motors_setpoint_t packet;
			mavlink_msg_set_quad_motors_setpoint_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_set_quad_motors_setpoint_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_SPEED_THRUST
		case MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_SPEED_THRUST: {
			mavlink_set_roll_pitch_yaw_speed_thrust_t packet;
			mavlink_msg_set_roll_pitch_yaw_speed_thrust_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_set_roll_pitch_yaw_speed_thrust_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST
		case MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST: {
			mavlink_set_roll_pitch_yaw_thrust_t packet;
			mavlink_msg_set_roll_pitch_yaw_thrust_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_set_roll_pitch_yaw_thrust_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_V2_EXTENSION
		case MAVLINK_MSG_ID_V2_EXTENSION: {
			mavlink_v2_extension_t packet;
			mavlink_msg_v2_extension_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_v2_extension_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FLEXIFUNCTION_BUFFER_FUNCTION_ACK
		case MAVLINK_MSG_ID_FLEXIFUNCTION_BUFFER_FUNCTION_ACK: {
			mavlink_flexifunction_buffer_function_ack_t packet;
			mavlink_msg_flexifunction_buffer_function_ack_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_flexifunction_buffer_function_ack_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FLEXIFUNCTION_BUFFER_FUNCTION
		case MAVLINK_MSG_ID_FLEXIFUNCTION_BUFFER_FUNCTION: {
			mavlink_flexifunction_buffer_function_t packet;
			mavlink_msg_flexifunction_buffer_function_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_flexifunction_buffer_function_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FLEXIFUNCTION_COMMAND
		case MAVLINK_MSG_ID_FLEXIFUNCTION_COMMAND: {
			mavlink_flexifunction_command_t packet;
			mavlink_msg_flexifunction_command_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_flexifunction_command_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY_ACK
		case MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY_ACK: {
			mavlink_flexifunction_directory_ack_t packet;
			mavlink_msg_flexifunction_directory_ack_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_flexifunction_directory_ack_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY
		case MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY: {
			mavlink_flexifunction_directory_t packet;
			mavlink_msg_flexifunction_directory_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_flexifunction_directory_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FLEXIFUNCTION_READ_REQ
		case MAVLINK_MSG_ID_FLEXIFUNCTION_READ_REQ: {
			mavlink_flexifunction_read_req_t packet;
			mavlink_msg_flexifunction_read_req_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_flexifunction_read_req_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FLEXIFUNCTION_SET
		case MAVLINK_MSG_ID_FLEXIFUNCTION_SET: {
			mavlink_flexifunction_set_t packet;
			mavlink_msg_flexifunction_set_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_flexifunction_set_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_POSITION_CONTROL_OFFSET
		case MAVLINK_MSG_ID_SET_POSITION_CONTROL_OFFSET: {
			mavlink_set_position_control_offset_t packet;
			mavlink_msg_set_position_control_offset_decode(msg, &packet);
			modelid = packet.target_system - 1;
			packet.target_system = ModelData[modelid].mavlink_org_sysid;
			mavlink_msg_set_position_control_offset_encode(msg->sysid, msg->compid, msg, &packet);
			return modelid;
			break;
		}
#endif
		default: {
			SDL_Log("mavlink_rewrite: ## BROADCAST MSG_ID == %i ##\n", msg->msgid);
			break;
		}
	}
	return 255;
}

uint8_t mavlink_source_rewrite (uint8_t modelid, mavlink_message_t* msg) {
	switch (msg->msgid) {
#ifdef MAVLINK_MSG_ID_AHRS2
		case MAVLINK_MSG_ID_AHRS2: {
			mavlink_ahrs2_t packet;
			mavlink_msg_ahrs2_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_ahrs2_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_AHRS
		case MAVLINK_MSG_ID_AHRS: {
			mavlink_ahrs_t packet;
			mavlink_msg_ahrs_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_ahrs_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_AIRSPEED_AUTOCAL
		case MAVLINK_MSG_ID_AIRSPEED_AUTOCAL: {
			mavlink_airspeed_autocal_t packet;
			mavlink_msg_airspeed_autocal_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_airspeed_autocal_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_AP_ADC
		case MAVLINK_MSG_ID_AP_ADC: {
			mavlink_ap_adc_t packet;
			mavlink_msg_ap_adc_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_ap_adc_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_BATTERY2
		case MAVLINK_MSG_ID_BATTERY2: {
			mavlink_battery2_t packet;
			mavlink_msg_battery2_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_battery2_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_CAMERA_FEEDBACK
		case MAVLINK_MSG_ID_CAMERA_FEEDBACK: {
			mavlink_camera_feedback_t packet;
			mavlink_msg_camera_feedback_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_camera_feedback_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_CAMERA_STATUS
		case MAVLINK_MSG_ID_CAMERA_STATUS: {
			mavlink_camera_status_t packet;
			mavlink_msg_camera_status_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_camera_status_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_COMPASSMOT_STATUS
		case MAVLINK_MSG_ID_COMPASSMOT_STATUS: {
			mavlink_compassmot_status_t packet;
			mavlink_msg_compassmot_status_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_compassmot_status_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_DATA16
		case MAVLINK_MSG_ID_DATA16: {
			mavlink_data16_t packet;
			mavlink_msg_data16_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_data16_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_DATA32
		case MAVLINK_MSG_ID_DATA32: {
			mavlink_data32_t packet;
			mavlink_msg_data32_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_data32_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_DATA64
		case MAVLINK_MSG_ID_DATA64: {
			mavlink_data64_t packet;
			mavlink_msg_data64_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_data64_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_DATA96
		case MAVLINK_MSG_ID_DATA96: {
			mavlink_data96_t packet;
			mavlink_msg_data96_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_data96_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_DIGICAM_CONFIGURE
		case MAVLINK_MSG_ID_DIGICAM_CONFIGURE: {
			mavlink_digicam_configure_t packet;
			mavlink_msg_digicam_configure_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_digicam_configure_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_DIGICAM_CONTROL
		case MAVLINK_MSG_ID_DIGICAM_CONTROL: {
			mavlink_digicam_control_t packet;
			mavlink_msg_digicam_control_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_digicam_control_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_EKF
		case MAVLINK_MSG_ID_EKF: {
			mavlink_ekf_t packet;
			mavlink_msg_ekf_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_ekf_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FENCE_FETCH_POINT
		case MAVLINK_MSG_ID_FENCE_FETCH_POINT: {
			mavlink_fence_fetch_point_t packet;
			mavlink_msg_fence_fetch_point_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_fence_fetch_point_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FENCE_POINT
		case MAVLINK_MSG_ID_FENCE_POINT: {
			mavlink_fence_point_t packet;
			mavlink_msg_fence_point_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_fence_point_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FENCE_STATUS
		case MAVLINK_MSG_ID_FENCE_STATUS: {
			mavlink_fence_status_t packet;
			mavlink_msg_fence_status_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_fence_status_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_HWSTATUS
		case MAVLINK_MSG_ID_HWSTATUS: {
			mavlink_hwstatus_t packet;
			mavlink_msg_hwstatus_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_hwstatus_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LIMITS_STATUS
		case MAVLINK_MSG_ID_LIMITS_STATUS: {
			mavlink_limits_status_t packet;
			mavlink_msg_limits_status_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_limits_status_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MEMINFO
		case MAVLINK_MSG_ID_MEMINFO: {
			mavlink_meminfo_t packet;
			mavlink_msg_meminfo_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_meminfo_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MOUNT_CONFIGURE
		case MAVLINK_MSG_ID_MOUNT_CONFIGURE: {
			mavlink_mount_configure_t packet;
			mavlink_msg_mount_configure_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mount_configure_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MOUNT_CONTROL
		case MAVLINK_MSG_ID_MOUNT_CONTROL: {
			mavlink_mount_control_t packet;
			mavlink_msg_mount_control_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mount_control_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MOUNT_STATUS
		case MAVLINK_MSG_ID_MOUNT_STATUS: {
			mavlink_mount_status_t packet;
			mavlink_msg_mount_status_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mount_status_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_RADIO
		case MAVLINK_MSG_ID_RADIO: {
			mavlink_radio_t packet;
			mavlink_msg_radio_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_radio_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_RALLY_FETCH_POINT
		case MAVLINK_MSG_ID_RALLY_FETCH_POINT: {
			mavlink_rally_fetch_point_t packet;
			mavlink_msg_rally_fetch_point_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_rally_fetch_point_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_RALLY_POINT
		case MAVLINK_MSG_ID_RALLY_POINT: {
			mavlink_rally_point_t packet;
			mavlink_msg_rally_point_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_rally_point_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_RANGEFINDER
		case MAVLINK_MSG_ID_RANGEFINDER: {
			mavlink_rangefinder_t packet;
			mavlink_msg_rangefinder_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_rangefinder_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SENSOR_OFFSETS
		case MAVLINK_MSG_ID_SENSOR_OFFSETS: {
			mavlink_sensor_offsets_t packet;
			mavlink_msg_sensor_offsets_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_sensor_offsets_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_MAG_OFFSETS
		case MAVLINK_MSG_ID_SET_MAG_OFFSETS: {
			mavlink_set_mag_offsets_t packet;
			mavlink_msg_set_mag_offsets_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_set_mag_offsets_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SIMSTATE
		case MAVLINK_MSG_ID_SIMSTATE: {
			mavlink_simstate_t packet;
			mavlink_msg_simstate_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_simstate_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_WIND
		case MAVLINK_MSG_ID_WIND: {
			mavlink_wind_t packet;
			mavlink_msg_wind_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_wind_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_ATTITUDE
		case MAVLINK_MSG_ID_ATTITUDE: {
			mavlink_attitude_t packet;
			mavlink_msg_attitude_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_attitude_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_ATTITUDE_QUATERNION_COV
		case MAVLINK_MSG_ID_ATTITUDE_QUATERNION_COV: {
			mavlink_attitude_quaternion_cov_t packet;
			mavlink_msg_attitude_quaternion_cov_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_attitude_quaternion_cov_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_ATTITUDE_QUATERNION
		case MAVLINK_MSG_ID_ATTITUDE_QUATERNION: {
			mavlink_attitude_quaternion_t packet;
			mavlink_msg_attitude_quaternion_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_attitude_quaternion_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_ATTITUDE_TARGET
		case MAVLINK_MSG_ID_ATTITUDE_TARGET: {
			mavlink_attitude_target_t packet;
			mavlink_msg_attitude_target_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_attitude_target_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_AUTH_KEY
		case MAVLINK_MSG_ID_AUTH_KEY: {
			mavlink_auth_key_t packet;
			mavlink_msg_auth_key_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_auth_key_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_AUTOPILOT_VERSION
		case MAVLINK_MSG_ID_AUTOPILOT_VERSION: {
			mavlink_autopilot_version_t packet;
			mavlink_msg_autopilot_version_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_autopilot_version_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_BATTERY_STATUS
		case MAVLINK_MSG_ID_BATTERY_STATUS: {
			mavlink_battery_status_t packet;
			mavlink_msg_battery_status_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_battery_status_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK
		case MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL_ACK: {
			mavlink_change_operator_control_ack_t packet;
			mavlink_msg_change_operator_control_ack_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_change_operator_control_ack_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL
		case MAVLINK_MSG_ID_CHANGE_OPERATOR_CONTROL: {
			mavlink_change_operator_control_t packet;
			mavlink_msg_change_operator_control_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_change_operator_control_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_COMMAND_ACK
		case MAVLINK_MSG_ID_COMMAND_ACK: {
			mavlink_command_ack_t packet;
			mavlink_msg_command_ack_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_command_ack_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_COMMAND_INT
		case MAVLINK_MSG_ID_COMMAND_INT: {
			mavlink_command_int_t packet;
			mavlink_msg_command_int_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_command_int_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_COMMAND_LONG
		case MAVLINK_MSG_ID_COMMAND_LONG: {
			mavlink_command_long_t packet;
			mavlink_msg_command_long_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_command_long_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_DATA_STREAM
		case MAVLINK_MSG_ID_DATA_STREAM: {
			mavlink_data_stream_t packet;
			mavlink_msg_data_stream_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_data_stream_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_DATA_TRANSMISSION_HANDSHAKE
		case MAVLINK_MSG_ID_DATA_TRANSMISSION_HANDSHAKE: {
			mavlink_data_transmission_handshake_t packet;
			mavlink_msg_data_transmission_handshake_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_data_transmission_handshake_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_DEBUG
		case MAVLINK_MSG_ID_DEBUG: {
			mavlink_debug_t packet;
			mavlink_msg_debug_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_debug_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_DEBUG_VECT
		case MAVLINK_MSG_ID_DEBUG_VECT: {
			mavlink_debug_vect_t packet;
			mavlink_msg_debug_vect_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_debug_vect_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_DISTANCE_SENSOR
		case MAVLINK_MSG_ID_DISTANCE_SENSOR: {
			mavlink_distance_sensor_t packet;
			mavlink_msg_distance_sensor_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_distance_sensor_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_ENCAPSULATED_DATA
		case MAVLINK_MSG_ID_ENCAPSULATED_DATA: {
			mavlink_encapsulated_data_t packet;
			mavlink_msg_encapsulated_data_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_encapsulated_data_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FILE_TRANSFER_DIR_LIST
		case MAVLINK_MSG_ID_FILE_TRANSFER_DIR_LIST: {
			mavlink_file_transfer_dir_list_t packet;
			mavlink_msg_file_transfer_dir_list_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_file_transfer_dir_list_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FILE_TRANSFER_PROTOCOL
		case MAVLINK_MSG_ID_FILE_TRANSFER_PROTOCOL: {
			mavlink_file_transfer_protocol_t packet;
			mavlink_msg_file_transfer_protocol_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_file_transfer_protocol_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FILE_TRANSFER_RES
		case MAVLINK_MSG_ID_FILE_TRANSFER_RES: {
			mavlink_file_transfer_res_t packet;
			mavlink_msg_file_transfer_res_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_file_transfer_res_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_FILE_TRANSFER_START
		case MAVLINK_MSG_ID_FILE_TRANSFER_START: {
			mavlink_file_transfer_start_t packet;
			mavlink_msg_file_transfer_start_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_file_transfer_start_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_GLOBAL_POSITION_INT_COV
		case MAVLINK_MSG_ID_GLOBAL_POSITION_INT_COV: {
			mavlink_global_position_int_cov_t packet;
			mavlink_msg_global_position_int_cov_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_global_position_int_cov_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_GLOBAL_POSITION_INT
		case MAVLINK_MSG_ID_GLOBAL_POSITION_INT: {
			mavlink_global_position_int_t packet;
			mavlink_msg_global_position_int_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_global_position_int_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_GLOBAL_POSITION_SETPOINT_INT
		case MAVLINK_MSG_ID_GLOBAL_POSITION_SETPOINT_INT: {
			mavlink_global_position_setpoint_int_t packet;
			mavlink_msg_global_position_setpoint_int_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_global_position_setpoint_int_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_GLOBAL_VISION_POSITION_ESTIMATE
		case MAVLINK_MSG_ID_GLOBAL_VISION_POSITION_ESTIMATE: {
			mavlink_global_vision_position_estimate_t packet;
			mavlink_msg_global_vision_position_estimate_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_global_vision_position_estimate_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_GPS2_RAW
		case MAVLINK_MSG_ID_GPS2_RAW: {
			mavlink_gps2_raw_t packet;
			mavlink_msg_gps2_raw_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_gps2_raw_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_GPS2_RTK
		case MAVLINK_MSG_ID_GPS2_RTK: {
			mavlink_gps2_rtk_t packet;
			mavlink_msg_gps2_rtk_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_gps2_rtk_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN
		case MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN: {
			mavlink_gps_global_origin_t packet;
			mavlink_msg_gps_global_origin_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_gps_global_origin_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_GPS_INJECT_DATA
		case MAVLINK_MSG_ID_GPS_INJECT_DATA: {
			mavlink_gps_inject_data_t packet;
			mavlink_msg_gps_inject_data_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_gps_inject_data_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_GPS_RAW_INT
		case MAVLINK_MSG_ID_GPS_RAW_INT: {
			mavlink_gps_raw_int_t packet;
			mavlink_msg_gps_raw_int_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_gps_raw_int_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_GPS_RTK
		case MAVLINK_MSG_ID_GPS_RTK: {
			mavlink_gps_rtk_t packet;
			mavlink_msg_gps_rtk_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_gps_rtk_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_GPS_STATUS
		case MAVLINK_MSG_ID_GPS_STATUS: {
			mavlink_gps_status_t packet;
			mavlink_msg_gps_status_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_gps_status_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_HEARTBEAT
		case MAVLINK_MSG_ID_HEARTBEAT: {
			mavlink_heartbeat_t packet;
			mavlink_msg_heartbeat_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_heartbeat_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_HIGHRES_IMU
		case MAVLINK_MSG_ID_HIGHRES_IMU: {
			mavlink_highres_imu_t packet;
			mavlink_msg_highres_imu_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_highres_imu_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_HIL_CONTROLS
		case MAVLINK_MSG_ID_HIL_CONTROLS: {
			mavlink_hil_controls_t packet;
			mavlink_msg_hil_controls_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_hil_controls_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_HIL_GPS
		case MAVLINK_MSG_ID_HIL_GPS: {
			mavlink_hil_gps_t packet;
			mavlink_msg_hil_gps_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_hil_gps_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_HIL_OPTICAL_FLOW
		case MAVLINK_MSG_ID_HIL_OPTICAL_FLOW: {
			mavlink_hil_optical_flow_t packet;
			mavlink_msg_hil_optical_flow_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_hil_optical_flow_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_HIL_RC_INPUTS_RAW
		case MAVLINK_MSG_ID_HIL_RC_INPUTS_RAW: {
			mavlink_hil_rc_inputs_raw_t packet;
			mavlink_msg_hil_rc_inputs_raw_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_hil_rc_inputs_raw_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_HIL_SENSOR
		case MAVLINK_MSG_ID_HIL_SENSOR: {
			mavlink_hil_sensor_t packet;
			mavlink_msg_hil_sensor_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_hil_sensor_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_HIL_STATE
		case MAVLINK_MSG_ID_HIL_STATE: {
			mavlink_hil_state_t packet;
			mavlink_msg_hil_state_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_hil_state_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_HIL_STATE_QUATERNION
		case MAVLINK_MSG_ID_HIL_STATE_QUATERNION: {
			mavlink_hil_state_quaternion_t packet;
			mavlink_msg_hil_state_quaternion_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_hil_state_quaternion_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LOCAL_POSITION_NED_COV
		case MAVLINK_MSG_ID_LOCAL_POSITION_NED_COV: {
			mavlink_local_position_ned_cov_t packet;
			mavlink_msg_local_position_ned_cov_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_local_position_ned_cov_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LOCAL_POSITION_NED
		case MAVLINK_MSG_ID_LOCAL_POSITION_NED: {
			mavlink_local_position_ned_t packet;
			mavlink_msg_local_position_ned_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_local_position_ned_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LOCAL_POSITION_NED_SYSTEM_GLOBAL_OFFSET
		case MAVLINK_MSG_ID_LOCAL_POSITION_NED_SYSTEM_GLOBAL_OFFSET: {
			mavlink_local_position_ned_system_global_offset_t packet;
			mavlink_msg_local_position_ned_system_global_offset_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_local_position_ned_system_global_offset_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LOCAL_POSITION_SETPOINT
		case MAVLINK_MSG_ID_LOCAL_POSITION_SETPOINT: {
			mavlink_local_position_setpoint_t packet;
			mavlink_msg_local_position_setpoint_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_local_position_setpoint_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LOG_DATA
		case MAVLINK_MSG_ID_LOG_DATA: {
			mavlink_log_data_t packet;
			mavlink_msg_log_data_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_log_data_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LOG_ENTRY
		case MAVLINK_MSG_ID_LOG_ENTRY: {
			mavlink_log_entry_t packet;
			mavlink_msg_log_entry_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_log_entry_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LOG_ERASE
		case MAVLINK_MSG_ID_LOG_ERASE: {
			mavlink_log_erase_t packet;
			mavlink_msg_log_erase_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_log_erase_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LOG_REQUEST_DATA
		case MAVLINK_MSG_ID_LOG_REQUEST_DATA: {
			mavlink_log_request_data_t packet;
			mavlink_msg_log_request_data_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_log_request_data_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LOG_REQUEST_END
		case MAVLINK_MSG_ID_LOG_REQUEST_END: {
			mavlink_log_request_end_t packet;
			mavlink_msg_log_request_end_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_log_request_end_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_LOG_REQUEST_LIST
		case MAVLINK_MSG_ID_LOG_REQUEST_LIST: {
			mavlink_log_request_list_t packet;
			mavlink_msg_log_request_list_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_log_request_list_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MANUAL_CONTROL
		case MAVLINK_MSG_ID_MANUAL_CONTROL: {
			mavlink_manual_control_t packet;
			mavlink_msg_manual_control_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_manual_control_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MANUAL_SETPOINT
		case MAVLINK_MSG_ID_MANUAL_SETPOINT: {
			mavlink_manual_setpoint_t packet;
			mavlink_msg_manual_setpoint_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_manual_setpoint_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MEMORY_VECT
		case MAVLINK_MSG_ID_MEMORY_VECT: {
			mavlink_memory_vect_t packet;
			mavlink_msg_memory_vect_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_memory_vect_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_ACK
		case MAVLINK_MSG_ID_MISSION_ACK: {
			mavlink_mission_ack_t packet;
			mavlink_msg_mission_ack_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mission_ack_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_CLEAR_ALL
		case MAVLINK_MSG_ID_MISSION_CLEAR_ALL: {
			mavlink_mission_clear_all_t packet;
			mavlink_msg_mission_clear_all_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mission_clear_all_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_COUNT
		case MAVLINK_MSG_ID_MISSION_COUNT: {
			mavlink_mission_count_t packet;
			mavlink_msg_mission_count_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mission_count_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_CURRENT
		case MAVLINK_MSG_ID_MISSION_CURRENT: {
			mavlink_mission_current_t packet;
			mavlink_msg_mission_current_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mission_current_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_ITEM
		case MAVLINK_MSG_ID_MISSION_ITEM: {
			mavlink_mission_item_t packet;
			mavlink_msg_mission_item_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mission_item_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_ITEM_INT
		case MAVLINK_MSG_ID_MISSION_ITEM_INT: {
			mavlink_mission_item_int_t packet;
			mavlink_msg_mission_item_int_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mission_item_int_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_ITEM_REACHED
		case MAVLINK_MSG_ID_MISSION_ITEM_REACHED: {
			mavlink_mission_item_reached_t packet;
			mavlink_msg_mission_item_reached_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mission_item_reached_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_REQUEST
		case MAVLINK_MSG_ID_MISSION_REQUEST: {
			mavlink_mission_request_t packet;
			mavlink_msg_mission_request_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mission_request_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_REQUEST_LIST
		case MAVLINK_MSG_ID_MISSION_REQUEST_LIST: {
			mavlink_mission_request_list_t packet;
			mavlink_msg_mission_request_list_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mission_request_list_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_REQUEST_PARTIAL_LIST
		case MAVLINK_MSG_ID_MISSION_REQUEST_PARTIAL_LIST: {
			mavlink_mission_request_partial_list_t packet;
			mavlink_msg_mission_request_partial_list_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mission_request_partial_list_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_SET_CURRENT
		case MAVLINK_MSG_ID_MISSION_SET_CURRENT: {
			mavlink_mission_set_current_t packet;
			mavlink_msg_mission_set_current_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mission_set_current_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_MISSION_WRITE_PARTIAL_LIST
		case MAVLINK_MSG_ID_MISSION_WRITE_PARTIAL_LIST: {
			mavlink_mission_write_partial_list_t packet;
			mavlink_msg_mission_write_partial_list_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_mission_write_partial_list_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_NAMED_VALUE_FLOAT
		case MAVLINK_MSG_ID_NAMED_VALUE_FLOAT: {
			mavlink_named_value_float_t packet;
			mavlink_msg_named_value_float_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_named_value_float_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_NAMED_VALUE_INT
		case MAVLINK_MSG_ID_NAMED_VALUE_INT: {
			mavlink_named_value_int_t packet;
			mavlink_msg_named_value_int_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_named_value_int_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT
		case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT: {
			mavlink_nav_controller_output_t packet;
			mavlink_msg_nav_controller_output_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_nav_controller_output_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_OMNIDIRECTIONAL_FLOW
		case MAVLINK_MSG_ID_OMNIDIRECTIONAL_FLOW: {
			mavlink_omnidirectional_flow_t packet;
			mavlink_msg_omnidirectional_flow_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_omnidirectional_flow_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_OPTICAL_FLOW
		case MAVLINK_MSG_ID_OPTICAL_FLOW: {
			mavlink_optical_flow_t packet;
			mavlink_msg_optical_flow_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_optical_flow_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_OPTICAL_FLOW_RAD
		case MAVLINK_MSG_ID_OPTICAL_FLOW_RAD: {
			mavlink_optical_flow_rad_t packet;
			mavlink_msg_optical_flow_rad_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_optical_flow_rad_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_PARAM_REQUEST_LIST
		case MAVLINK_MSG_ID_PARAM_REQUEST_LIST: {
			mavlink_param_request_list_t packet;
			mavlink_msg_param_request_list_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_param_request_list_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_PARAM_REQUEST_READ
		case MAVLINK_MSG_ID_PARAM_REQUEST_READ: {
			mavlink_param_request_read_t packet;
			mavlink_msg_param_request_read_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_param_request_read_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_PARAM_SET
		case MAVLINK_MSG_ID_PARAM_SET: {
			mavlink_param_set_t packet;
			mavlink_msg_param_set_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_param_set_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_PARAM_VALUE
		case MAVLINK_MSG_ID_PARAM_VALUE: {
			mavlink_param_value_t packet;
			mavlink_msg_param_value_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_param_value_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_PING
		case MAVLINK_MSG_ID_PING: {
			mavlink_ping_t packet;
			mavlink_msg_ping_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_ping_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT
		case MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT: {
			mavlink_position_target_global_int_t packet;
			mavlink_msg_position_target_global_int_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_position_target_global_int_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_POSITION_TARGET_LOCAL_NED
		case MAVLINK_MSG_ID_POSITION_TARGET_LOCAL_NED: {
			mavlink_position_target_local_ned_t packet;
			mavlink_msg_position_target_local_ned_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_position_target_local_ned_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_POWER_STATUS
		case MAVLINK_MSG_ID_POWER_STATUS: {
			mavlink_power_status_t packet;
			mavlink_msg_power_status_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_power_status_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_RADIO_STATUS
		case MAVLINK_MSG_ID_RADIO_STATUS: {
			mavlink_radio_status_t packet;
			mavlink_msg_radio_status_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_radio_status_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_RAW_IMU
		case MAVLINK_MSG_ID_RAW_IMU: {
			mavlink_raw_imu_t packet;
			mavlink_msg_raw_imu_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_raw_imu_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_RAW_PRESSURE
		case MAVLINK_MSG_ID_RAW_PRESSURE: {
			mavlink_raw_pressure_t packet;
			mavlink_msg_raw_pressure_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_raw_pressure_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_RC_CHANNELS
		case MAVLINK_MSG_ID_RC_CHANNELS: {
			mavlink_rc_channels_t packet;
			mavlink_msg_rc_channels_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_rc_channels_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_RC_CHANNELS_OVERRIDE
		case MAVLINK_MSG_ID_RC_CHANNELS_OVERRIDE: {
			mavlink_rc_channels_override_t packet;
			mavlink_msg_rc_channels_override_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_rc_channels_override_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_RC_CHANNELS_RAW
		case MAVLINK_MSG_ID_RC_CHANNELS_RAW: {
			mavlink_rc_channels_raw_t packet;
			mavlink_msg_rc_channels_raw_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_rc_channels_raw_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_RC_CHANNELS_SCALED
		case MAVLINK_MSG_ID_RC_CHANNELS_SCALED: {
			mavlink_rc_channels_scaled_t packet;
			mavlink_msg_rc_channels_scaled_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_rc_channels_scaled_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_REQUEST_DATA_STREAM
		case MAVLINK_MSG_ID_REQUEST_DATA_STREAM: {
			mavlink_request_data_stream_t packet;
			mavlink_msg_request_data_stream_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_request_data_stream_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_ROLL_PITCH_YAW_RATES_THRUST_SETPOINT
		case MAVLINK_MSG_ID_ROLL_PITCH_YAW_RATES_THRUST_SETPOINT: {
			mavlink_roll_pitch_yaw_rates_thrust_setpoint_t packet;
			mavlink_msg_roll_pitch_yaw_rates_thrust_setpoint_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_roll_pitch_yaw_rates_thrust_setpoint_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_ROLL_PITCH_YAW_SPEED_THRUST_SETPOINT
		case MAVLINK_MSG_ID_ROLL_PITCH_YAW_SPEED_THRUST_SETPOINT: {
			mavlink_roll_pitch_yaw_speed_thrust_setpoint_t packet;
			mavlink_msg_roll_pitch_yaw_speed_thrust_setpoint_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_roll_pitch_yaw_speed_thrust_setpoint_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_ROLL_PITCH_YAW_THRUST_SETPOINT
		case MAVLINK_MSG_ID_ROLL_PITCH_YAW_THRUST_SETPOINT: {
			mavlink_roll_pitch_yaw_thrust_setpoint_t packet;
			mavlink_msg_roll_pitch_yaw_thrust_setpoint_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_roll_pitch_yaw_thrust_setpoint_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SAFETY_ALLOWED_AREA
		case MAVLINK_MSG_ID_SAFETY_ALLOWED_AREA: {
			mavlink_safety_allowed_area_t packet;
			mavlink_msg_safety_allowed_area_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_safety_allowed_area_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SAFETY_SET_ALLOWED_AREA
		case MAVLINK_MSG_ID_SAFETY_SET_ALLOWED_AREA: {
			mavlink_safety_set_allowed_area_t packet;
			mavlink_msg_safety_set_allowed_area_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_safety_set_allowed_area_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SCALED_IMU2
		case MAVLINK_MSG_ID_SCALED_IMU2: {
			mavlink_scaled_imu2_t packet;
			mavlink_msg_scaled_imu2_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_scaled_imu2_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SCALED_IMU
		case MAVLINK_MSG_ID_SCALED_IMU: {
			mavlink_scaled_imu_t packet;
			mavlink_msg_scaled_imu_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_scaled_imu_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SCALED_PRESSURE
		case MAVLINK_MSG_ID_SCALED_PRESSURE: {
			mavlink_scaled_pressure_t packet;
			mavlink_msg_scaled_pressure_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_scaled_pressure_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SERIAL_CONTROL
		case MAVLINK_MSG_ID_SERIAL_CONTROL: {
			mavlink_serial_control_t packet;
			mavlink_msg_serial_control_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_serial_control_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SERVO_OUTPUT_RAW
		case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW: {
			mavlink_servo_output_raw_t packet;
			mavlink_msg_servo_output_raw_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_servo_output_raw_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_ATTITUDE_TARGET
		case MAVLINK_MSG_ID_SET_ATTITUDE_TARGET: {
			mavlink_set_attitude_target_t packet;
			mavlink_msg_set_attitude_target_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_set_attitude_target_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_GLOBAL_POSITION_SETPOINT_INT
		case MAVLINK_MSG_ID_SET_GLOBAL_POSITION_SETPOINT_INT: {
			mavlink_set_global_position_setpoint_int_t packet;
			mavlink_msg_set_global_position_setpoint_int_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_set_global_position_setpoint_int_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_GPS_GLOBAL_ORIGIN
		case MAVLINK_MSG_ID_SET_GPS_GLOBAL_ORIGIN: {
			mavlink_set_gps_global_origin_t packet;
			mavlink_msg_set_gps_global_origin_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_set_gps_global_origin_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_LOCAL_POSITION_SETPOINT
		case MAVLINK_MSG_ID_SET_LOCAL_POSITION_SETPOINT: {
			mavlink_set_local_position_setpoint_t packet;
			mavlink_msg_set_local_position_setpoint_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_set_local_position_setpoint_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_MODE
		case MAVLINK_MSG_ID_SET_MODE: {
			mavlink_set_mode_t packet;
			mavlink_msg_set_mode_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_set_mode_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SETPOINT_6DOF
		case MAVLINK_MSG_ID_SETPOINT_6DOF: {
			mavlink_setpoint_6dof_t packet;
			mavlink_msg_setpoint_6dof_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_setpoint_6dof_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SETPOINT_8DOF
		case MAVLINK_MSG_ID_SETPOINT_8DOF: {
			mavlink_setpoint_8dof_t packet;
			mavlink_msg_setpoint_8dof_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_setpoint_8dof_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_POSITION_TARGET_GLOBAL_INT
		case MAVLINK_MSG_ID_SET_POSITION_TARGET_GLOBAL_INT: {
			mavlink_set_position_target_global_int_t packet;
			mavlink_msg_set_position_target_global_int_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_set_position_target_global_int_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_POSITION_TARGET_LOCAL_NED
		case MAVLINK_MSG_ID_SET_POSITION_TARGET_LOCAL_NED: {
			mavlink_set_position_target_local_ned_t packet;
			mavlink_msg_set_position_target_local_ned_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_set_position_target_local_ned_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_QUAD_MOTORS_SETPOINT
		case MAVLINK_MSG_ID_SET_QUAD_MOTORS_SETPOINT: {
			mavlink_set_quad_motors_setpoint_t packet;
			mavlink_msg_set_quad_motors_setpoint_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_set_quad_motors_setpoint_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_QUAD_SWARM_LED_ROLL_PITCH_YAW_THRUST
		case MAVLINK_MSG_ID_SET_QUAD_SWARM_LED_ROLL_PITCH_YAW_THRUST: {
			mavlink_set_quad_swarm_led_roll_pitch_yaw_thrust_t packet;
			mavlink_msg_set_quad_swarm_led_roll_pitch_yaw_thrust_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_set_quad_swarm_led_roll_pitch_yaw_thrust_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_QUAD_SWARM_ROLL_PITCH_YAW_THRUST
		case MAVLINK_MSG_ID_SET_QUAD_SWARM_ROLL_PITCH_YAW_THRUST: {
			mavlink_set_quad_swarm_roll_pitch_yaw_thrust_t packet;
			mavlink_msg_set_quad_swarm_roll_pitch_yaw_thrust_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_set_quad_swarm_roll_pitch_yaw_thrust_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_SPEED_THRUST
		case MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_SPEED_THRUST: {
			mavlink_set_roll_pitch_yaw_speed_thrust_t packet;
			mavlink_msg_set_roll_pitch_yaw_speed_thrust_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_set_roll_pitch_yaw_speed_thrust_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST
		case MAVLINK_MSG_ID_SET_ROLL_PITCH_YAW_THRUST: {
			mavlink_set_roll_pitch_yaw_thrust_t packet;
			mavlink_msg_set_roll_pitch_yaw_thrust_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_set_roll_pitch_yaw_thrust_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SIM_STATE
		case MAVLINK_MSG_ID_SIM_STATE: {
			mavlink_sim_state_t packet;
			mavlink_msg_sim_state_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_sim_state_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_STATE_CORRECTION
		case MAVLINK_MSG_ID_STATE_CORRECTION: {
			mavlink_state_correction_t packet;
			mavlink_msg_state_correction_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_state_correction_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_STATUSTEXT
		case MAVLINK_MSG_ID_STATUSTEXT: {
			mavlink_statustext_t packet;
			mavlink_msg_statustext_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_statustext_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SYS_STATUS
		case MAVLINK_MSG_ID_SYS_STATUS: {
			mavlink_sys_status_t packet;
			mavlink_msg_sys_status_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_sys_status_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_SYSTEM_TIME
		case MAVLINK_MSG_ID_SYSTEM_TIME: {
			mavlink_system_time_t packet;
			mavlink_msg_system_time_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_system_time_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_TERRAIN_CHECK
		case MAVLINK_MSG_ID_TERRAIN_CHECK: {
			mavlink_terrain_check_t packet;
			mavlink_msg_terrain_check_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_terrain_check_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_TERRAIN_DATA
		case MAVLINK_MSG_ID_TERRAIN_DATA: {
			mavlink_terrain_data_t packet;
			mavlink_msg_terrain_data_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_terrain_data_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_TERRAIN_REPORT
		case MAVLINK_MSG_ID_TERRAIN_REPORT: {
			mavlink_terrain_report_t packet;
			mavlink_msg_terrain_report_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_terrain_report_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_TERRAIN_REQUEST
		case MAVLINK_MSG_ID_TERRAIN_REQUEST: {
			mavlink_terrain_request_t packet;
			mavlink_msg_terrain_request_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_terrain_request_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_TIMESYNC
		case MAVLINK_MSG_ID_TIMESYNC: {
			mavlink_timesync_t packet;
			mavlink_msg_timesync_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_timesync_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_V2_EXTENSION
		case MAVLINK_MSG_ID_V2_EXTENSION: {
			mavlink_v2_extension_t packet;
			mavlink_msg_v2_extension_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_v2_extension_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_VFR_HUD
		case MAVLINK_MSG_ID_VFR_HUD: {
			mavlink_vfr_hud_t packet;
			mavlink_msg_vfr_hud_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_vfr_hud_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_VICON_POSITION_ESTIMATE
		case MAVLINK_MSG_ID_VICON_POSITION_ESTIMATE: {
			mavlink_vicon_position_estimate_t packet;
			mavlink_msg_vicon_position_estimate_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_vicon_position_estimate_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_VISION_POSITION_ESTIMATE
		case MAVLINK_MSG_ID_VISION_POSITION_ESTIMATE: {
			mavlink_vision_position_estimate_t packet;
			mavlink_msg_vision_position_estimate_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_vision_position_estimate_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
#ifdef MAVLINK_MSG_ID_VISION_SPEED_ESTIMATE
		case MAVLINK_MSG_ID_VISION_SPEED_ESTIMATE: {
			mavlink_vision_speed_estimate_t packet;
			mavlink_msg_vision_speed_estimate_decode(msg, &packet);
			ModelData[modelid].mavlink_org_sysid = msg->sysid;
			msg->sysid = modelid + 1;
			mavlink_msg_vision_speed_estimate_encode(msg->sysid, msg->compid, msg, &packet);
			return ModelData[modelid].mavlink_org_sysid;
			break;
		}
#endif
		default: {
			SDL_Log("mavlink_rewrite: ## UNSUPPORTED MSG_ID == %i (mavlink/get_case_by_file.sh %i) ##\n", msg->msgid, msg->msgid);
			break;
		}
	}
	return 255;
}



