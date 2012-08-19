/*
 * Origin.cpp
 *
 *  Created on: Aug 19, 2012
 *      Author: mariusz
 */

#include <GLES2/gl2.h>
#include "Origin.h"
#include "Util.h"


Origin::Origin() {
	programObject = 0;
}

Origin::~Origin() {
}


///
// Initialize the shader and program object
//
int Origin::init ()
{
   char vShaderStr[] =
      "attribute vec4 a_position;                  \n"
      "void main()                                 \n"
      "{                                           \n"
      "   gl_Position = a_position;  \n"
      "}                                           \n";

   char fShaderStr[] =
      "precision mediump float;                            \n"
      "void main()                                         \n"
      "{                                                   \n"
      "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);        \n"
      "}                                                   \n";

   // Load the shaders and get a linked program object
   programObject = esCreateProgram(vShaderStr, fShaderStr);

   // Bind vPosition to attribute 0
   glBindAttribLocation(programObject, 0, "a_position");

   glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );
   return GL_TRUE;
}

void Origin::drawFrame() {
	GLfloat vVertices[] = {
			0.0f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f };

	// clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// use the program object
	glUseProgram(programObject);
	// load the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}
