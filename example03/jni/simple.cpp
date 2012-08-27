
#include <jni.h>
#include <GLES2/gl2.h>
#include "simple.h"
#include "Origin.h"
#include "Terrain.h"


//Terrain *terrain;
Origin origin;


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_myDrawFrame
  (JNIEnv *env, jclass c)
{
	glClear(GL_COLOR_BUFFER_BIT);
	origin.drawFrame();
}


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_mySurfaceChanged
(JNIEnv *env, jclass c, jint width, jint height)
{
	glViewport(0, 0, width, height);
	origin.init(width, height);
}


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_mySurfaceCreated
(JNIEnv *env, jclass c)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//origin = new Origin();
	//terrain = new Terrain(); // FIXME: clean up the memory when the surface is discarded
}
