LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
SRC_PATH := ../../..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include:$(SRC_PATH)

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	$(SRC_PATH)/Drawable.cpp \
	$(SRC_PATH)/esShapes.cpp \
	$(SRC_PATH)/esTransform.cpp \
	$(SRC_PATH)/esUtil.cpp \
	$(SRC_PATH)/main.cpp \
	$(SRC_PATH)/Origin.cpp \
	$(SRC_PATH)/Sphere.cpp \
	$(SRC_PATH)/Terrain.cpp

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
