/*
 * Util.h
 *
 *  Created on: Aug 18, 2012
 *      Author: mariusz
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/log.h>

using namespace std;


#define LOG_TAG "OpenGL Util Logger"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#define PI 3.1415926535897932384626433832795f

typedef struct
{

   GLuint programObject; // Handle to a program object


} UserData;

typedef struct {
        GLfloat m[4][4];
} ESMatrix;




GLuint esLoadShader(GLenum, const char*);
GLuint esCreateProgram(const char* pVertexSource, const char* pFragmentSource);

void esNormalize(float v[3]);
void esNorm_crossprod(float v1[3], float v2[3], float out[3]);

void checkGLError(const char* op);
void printGLString(const char *name, GLenum s);

#endif /* UTIL_H_ */
