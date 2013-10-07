

#include <all.h>
#include <jni.h>

static float jni_gps_lat = 0.0;
static float jni_gps_lon = 0.0;
static float jni_gps_alt = 0.0;
static float jni_gps_speed = 0.0;
static float jni_att_roll = 0.0;
static float jni_att_pitch = 0.0;
static float jni_att_yaw = 0.0;

char jni_text2speak[1024];


#define DEG_TO_RAD   ( PI / 180.0 )
#define RAD_TO_DEG   ( 180.0 / PI )


void jni_gpsGetPosition (float *lat, float *lon, float *alt, float *speed) {
	*lat = jni_gps_lat;
	*lon = jni_gps_lat;
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

jstring Java_org_libsdl_app_SDLSurface_getTextToSpeak (JNIEnv* env, jclass cls) {
	static char text[1024];
	strcpy(text, jni_text2speak);
	jni_text2speak[0] = 0;
	return (*env)->NewStringUTF(env, text);
}

