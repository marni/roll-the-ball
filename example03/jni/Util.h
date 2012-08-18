/*
 * Util.h
 *
 *  Created on: Aug 18, 2012
 *      Author: mariusz
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <GLES2/gl2.h>

using namespace std;

class Util {

public:
	Util();
	virtual ~Util();

	static GLuint LoadShader(GLenum, const string);
	static void normalize(float v[3]);
	static void norm_crossprod(float v1[3], float v2[3], float out[3]);

};

#endif /* UTIL_H_ */
