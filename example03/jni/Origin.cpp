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
	  "attribute vec4 a_color;                     \n"
      "varying vec4 color;                         \n"
      "void main()                                 \n"
      "{                                           \n"
      "   gl_Position = a_position;                \n"
	  "   color = a_color;                         \n"
      "}                                           \n";

   char fShaderStr[] =
      "precision mediump float;                    \n"
	  "varying vec4 color;                         \n"
      "void main()                                 \n"
      "{                                           \n"
      "  gl_FragColor = color;                     \n"
//    "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);        \n"
      "}                                           \n";

   // Load the shaders and get a linked program object
   programObject = esCreateProgram(vShaderStr, fShaderStr);

   // Bind vPosition to attribute 0
   glBindAttribLocation(programObject, 0, "a_position");
   glBindAttribLocation(programObject, 1, "a_color");

   glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );

   return GL_TRUE;
}

void Origin::drawFrame() {

	GLfloat vVertices[] = {
			0.0f, 0.0f, 0.0f,
			0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f};

	GLfloat vColors[] = {
				0.0f, 0.5f, 0.0f, 1.0f,
				0.0f, 0.5f, 0.0f, 1.0f,
				0.5f, 0.0f, 0.0f, 1.0f,
				0.5f, 0.0f, 0.0f, 1.0f,
				0.0f, 0.0f, 0.5f, 1.0f,
				0.0f, 0.0f, 0.5f, 1.0f};


	// clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// use the program object
	glUseProgram(programObject);
	// load the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, vColors);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_LINES, 0, 6);

}
