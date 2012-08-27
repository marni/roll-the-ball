LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := simple
LOCAL_SRC_FILES := simple.cpp esUtil.c esShapes.c esTransform.c Drawable.cpp Origin.cpp Terrain.cpp 

LOCAL_LDLIBS := -lm -lGLESv2 -ldl -llog

include $(BUILD_SHARED_LIBRARY)


