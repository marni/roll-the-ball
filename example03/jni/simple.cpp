
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
Terrain terrain;

ESMatrix perspective;
float aspect;

JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_myCleanup
(JNIEnv *env, jclass c)
{
	SENSORS_ENABLED = 0;
	origin.cleanup();
	sphere.cleanup();
	terrain.cleanup();
}

JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_myStartSensors
  (JNIEnv *, jclass)
{
	SENSORS_ENABLED = 1;
	setup_sensors();
}

JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_myDrawFrame
  (JNIEnv *env, jclass c)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	sphere.drawFrame(&perspective);
	origin.drawFrame(&perspective);
	terrain.drawFrame(&perspective);
}


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_mySurfaceChanged
(JNIEnv *env, jclass c, jint width, jint height)
{
	glViewport(0, 0, width, height);
	aspect = (float)width / (float)height;
	// Generate a perspective matrix with a 60 degree FOV
	esMatrixLoadIdentity(&perspective);
    //LOGI("%f %d %d", aspect, width, height);
	esPerspective(&perspective, 60.0f, aspect, 1.0f, 30.0f);
	esTranslate(&perspective, 0.0f, 0.0f, -5.0f);
	//esRotate(&perspective, 45.0f, 1.0f, 0.0f, 0.0f);
	//esRotate(&perspective, -5.0f, 0.0f, 1.0f, 0.0f);

	origin.init(width, height);
	sphere.init(width, height);
	terrain.init(width, height);
}


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_mySurfaceCreated
(JNIEnv *env, jclass c)
{
	//origin = new Origin();
	//terrain = new Terrain(); // FIXME: clean up the memory when the surface is discarded
}
