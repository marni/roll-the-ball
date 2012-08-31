
#include <jni.h>
#include <GLES2/gl2.h>
#include "simple.h"
#include "esUtil.h"
#include "Origin.h"
#include "Sphere.h"
#include "Terrain.h"


//Terrain *terrain;
Origin origin;
Sphere sphere;


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_myCleanup
(JNIEnv *env, jclass c)
{
	SENSORS_ENABLED = 0;
	origin.cleanup();
	sphere.cleanup();
}

JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_myStartSensors
  (JNIEnv *, jclass)
{
	SENSORS_ENABLED = 1;
	//setup_sensors();
}

JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_myDrawFrame
  (JNIEnv *env, jclass c)
{
	ESMatrix perspective;
	float aspect = 1.0f;
	// Generate a perspective matrix with a 60 degree FOV
	esMatrixLoadIdentity(&perspective);

	esPerspective(&perspective, 40.0f, aspect, 0.0f, 20.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	origin.drawFrame(&perspective);
	sphere.drawFrame(&perspective);
}


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_mySurfaceChanged
(JNIEnv *env, jclass c, jint width, jint height)
{
	glViewport(0, 0, width, height);
	origin.init(width, height);
	sphere.init(width, height);
}


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_mySurfaceCreated
(JNIEnv *env, jclass c)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//origin = new Origin();
	//terrain = new Terrain(); // FIXME: clean up the memory when the surface is discarded
}
