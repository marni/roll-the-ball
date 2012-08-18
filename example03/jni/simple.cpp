
#include <string.h>
#include <jni.h>
#include <GLES/gl.h>
#include "simple.h"
#include "Terrain.h"


Terrain *terrain;


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_myDrawFrame
  (JNIEnv *env, jclass c)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	terrain->Render();
}


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_mySurfaceChanged
(JNIEnv *env, jclass c, jint width, jint height)
{
	glViewport(0, 0, width, height);

}


JNIEXPORT void JNICALL Java_org_nzdis_example03_GLESView_mySurfaceCreated
(JNIEnv *env, jclass c)
{
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	terrain = new Terrain(); // FIXME: clean up the memory when the surface is discarded
}
