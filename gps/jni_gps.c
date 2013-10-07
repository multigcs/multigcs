

#include <all.h>
#include <jni.h>

#define DEG_TO_RAD   ( PI / 180.0 )
#define RAD_TO_DEG   ( 180.0 / PI )

static float jni_gps_lat = 0.0;
static float jni_gps_lon = 0.0;
static float jni_gps_alt = 0.0;
static float jni_gps_speed = 0.0;
static float jni_att_roll = 0.0;
static float jni_att_pitch = 0.0;
static float jni_att_yaw = 0.0;

char bt_devices[100][1023];
uint8_t aserbuffer[2048];
int aserbuffer_pos = 0;


void jni_gpsGetPosition (float *lat, float *lon, float *alt, float *speed) {
	*lat = jni_gps_lat;
	*lon = jni_gps_lon;
	*alt = jni_gps_alt;
	*speed = jni_gps_speed;
	return;
}

void jni_attitudeGetPosition (float *pitch, float *roll, float *yaw) {
	*pitch = jni_att_pitch;
	*roll = jni_att_roll;
	*yaw = jni_att_yaw;
	return;
}

void Java_org_libsdl_app_mylocationlistener_gpsSetPosition (JNIEnv* env, jclass cls, jfloat lat, jfloat lon, jfloat alt, jfloat speed) {
	jni_gps_lat = lat;
	jni_gps_lon = lon;
	jni_gps_alt = alt;
	jni_gps_speed = speed;
	return;
}

void Java_org_libsdl_app_SDLSurface_attitudeSetPosition (JNIEnv* env, jclass cls, jfloat pitch, jfloat roll, jfloat yaw) {
	jni_att_roll = roll * RAD_TO_DEG * -1;
	jni_att_pitch = pitch * RAD_TO_DEG * -1 - 90.0;
	yaw *= RAD_TO_DEG;
	yaw += 90;
	if (yaw < -180) {
		yaw += 360;
	}
	if (yaw > 180) {
		yaw -= 360;
	}
	jni_att_yaw = yaw;
	return;
}

ssize_t bt_read(int fd, void *data, size_t len) {
	ssize_t retlen = aserbuffer_pos;
	memcpy(data, aserbuffer, retlen);
	aserbuffer_pos = 0;
	return retlen;
}

void Java_org_libsdl_app_ConnectBT_serialReceive (JNIEnv* env, jclass cls, jbyte c) {
	int n = 0;
	if (aserbuffer_pos < 2000) {
		aserbuffer[aserbuffer_pos++] = c;
	}
	return;
}

void Java_org_libsdl_app_ConnectBT_deviceList (JNIEnv* env, jclass cls, jstring dlist) {

	const char *nativeString = (*env)->GetStringUTFChars(env, dlist, 0);

	SDL_Log("BT DEVICE_LIST: %s", nativeString);

	int n = 0;
	int nn = 0;
	int num = 0;
	for (n = 0; n < strlen(nativeString); n++) {
		if (nativeString[n] == ';') {
			num++;
			nn = 0;
			bt_devices[num][nn] = 0;
		} else {
			bt_devices[num][nn++] = nativeString[n];
			bt_devices[num][nn] = 0;
		}
	}
	return;
}

