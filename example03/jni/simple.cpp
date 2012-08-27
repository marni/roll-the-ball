
#include <jni.h>
#include <GLES2/gl2.h>
#include "simple.h"
#include "esUtil.h"
#include "Origin.h"
#include "Terrain.h"


//Terrain *terrain;
Origin origin;


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_myCleanup
(JNIEnv *env, jclass c)
{
	SENSORS_ENABLED = 0;
}


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_myDrawFrame
  (JNIEnv *env, jclass c)
{
	ESMatrix perspective;
	float aspect;
	// Generate a perspective matrix with a 60 degree FOV
	esMatrixLoadIdentity(&perspective);
	aspect = origin.getESContext()->width / origin.getESContext()->height;
	esPerspective(&perspective, 60.0f, aspect, 0.0f, 10.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	origin.drawFrame(&perspective);
}


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_mySurfaceChanged
(JNIEnv *env, jclass c, jint width, jint height)
{
	glViewport(0, 0, width, height);
	origin.init(width, height);
	setup_sensors();
}


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_mySurfaceCreated
(JNIEnv *env, jclass c)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//origin = new Origin();
	//terrain = new Terrain(); // FIXME: clean up the memory when the surface is discarded
}
