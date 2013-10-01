LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL2
SDL_IMAGE_PATH := ../SDL2_image

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/$(SDL_IMAGE_PATH)

LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c main.c SDL_test_common.c

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image

LOCAL_LDLIBS := -lGLESv1_CM -llog
#LOCAL_LDLIBS := -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
