/*
 * Util.cpp
 *
 *  Created on: Aug 18, 2012
 *      Author: mariusz
 */

#include <iostream>
#include <cmath>

#include "Util.h"



Util::Util() {
}

Util::~Util() {
}



GLuint Util::LoadShader(GLenum shader_type, const string src) {
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

  if (succeeded != GL_TRUE) {
    std::cout << src << std::endl;
    std::cerr << "Error Util::LoadShader | Something went wrong with the shader." << std::endl;
  }

  return sid;
}



// normalize a passed in vector
void Util::normalize( float v[3] )
{
	GLfloat d = sqrt(float(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]));
	if (d==0.0)
	{
		cerr << "Error Util::normilize | got zero length vector" << endl;
		return;
	}
	v[0] /= d;
	v[1] /= d;
	v[2] /= d;
}

// normalized cross product of two vectors
void Util::norm_crossprod( float v1[3], float v2[3], float out[3])
{
	out[0] = v1[1]*v2[2] - v1[2]*v2[1];
	out[1] = v1[2]*v2[0] - v1[0]*v2[2];
	out[2] = v1[0]*v2[1] - v1[1]*v2[0];
	Util::normalize(out);
}
