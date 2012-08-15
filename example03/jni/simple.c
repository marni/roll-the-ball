
#include <string.h>
#include <jni.h>
#include <gles/gl.h>
#include "simple.h"



JNIEXPORT void JNICALL Java_org_nzdis_example03_ExampleView_myDrawFrame
  (JNIEnv *env, jclass c)
{
	glClear(GL_COLOR_BUFFER_BIT);
}


JNIEXPORT void JNICALL Java_org_nzdis_example03_ExampleView_mySurfaceChanged
(JNIEnv *env, jclass c, jint width, jint height)
{
	glViewport(0, 0, width, height);

}


JNIEXPORT void JNICALL Java_org_nzdis_example03_ExampleView_mySurfaceCreated
(JNIEnv *env, jclass c)
{
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
}
