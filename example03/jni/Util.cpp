/*
 * Util.cpp
 *
 *  Created on: Aug 18, 2012
 *      Author: mariusz
 */

#include <iostream>
#include <cmath>
#include <GLES2/gl2.h>

#include "Util.h"




GLuint esLoadShader(GLenum shader_type, const char* src) {
  GLint succeeded;
  GLuint sid;

  sid = glCreateShader(shader_type);
  glShaderSource(sid, 1, (const GLchar **) &src, NULL);
  glCompileShader(sid);
  glGetShaderiv(sid, GL_COMPILE_STATUS, &succeeded);

  GLint log_length;
  glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &log_length);

  if (log_length > 1) {
    char *log = new char[log_length];
    GLint chars_written;
    glGetShaderInfoLog(sid, log_length, &chars_written, log);
    cout << "error log: " << log << std::endl;
    delete[] log;
  }

  checkGLError("Error esLoadShader: Something went wrong with the shader.");


  return sid;
}


GLuint esCreateProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = esLoadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = esLoadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint glProgram = glCreateProgram();
    if (glProgram) {
        glAttachShader(glProgram, vertexShader);
        checkGLError("glAttachShader");
        glAttachShader(glProgram, pixelShader);
        checkGLError("glAttachShader");

        glLinkProgram(glProgram);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(glProgram, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(glProgram, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(glProgram, bufLength, NULL, buf);
                    LOGE("Could not link glProgram:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(glProgram);
            glProgram = 0;
        }
    }
    checkGLError("create Program end");
    return glProgram;
}

/////////// printGLString ////////////
void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}


void checkGLError(const char* op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

// normalize a passed in vector
void esNormalize(float v[3])
{
	GLfloat d = sqrt(float(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]));
	if (d==0.0)
	{
		cerr << "Error esNormalize: got zero length vector" << endl;
		return;
	}
	v[0] /= d;
	v[1] /= d;
	v[2] /= d;
}

// normalized cross product of two vectors
void esNorm_crossprod(float v1[3], float v2[3], float out[3])
{
	out[0] = v1[1]*v2[2] - v1[2]*v2[1];
	out[1] = v1[2]*v2[0] - v1[0]*v2[2];
	out[2] = v1[0]*v2[1] - v1[1]*v2[0];
	esNormalize(out);
}

