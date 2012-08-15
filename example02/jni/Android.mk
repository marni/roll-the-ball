LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := simple
LOCAL_SRC_FILES := simple.c

LOCAL_LDLIBS := -lGLESv2 -ldl -llog

include $(BUILD_SHARED_LIBRARY)
