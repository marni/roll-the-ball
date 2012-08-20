/*
 * Origin.cpp
 *
 * Origin draws a 0.5 long axis along X Y Z dimensions,
 * with RGB colors accordingly.
 *
 *
 * Created on: Aug 19, 2012
 *      Author: mariusz
 */

#include <stdlib.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Origin.h"



Origin::Origin() {
	esInitContext(&esContext);
	esContext.userData = &userData;
}

Origin::~Origin() {
}


///
// Initialize the shader and program object
//
int Origin::init()
{
   char vShaderStr[] =
      "attribute vec4 a_position;                  \n"
	  "attribute vec4 a_color;                     \n"
	  "uniform mat4 mvp_matrix;                    \n"
      "varying vec4 color;                         \n"
      "void main()                                 \n"
      "{                                           \n"
      "   gl_Position = mvp_matrix * a_position;   \n"
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

   UserData *userData = (UserData*)esContext.userData;
   // Load the shaders and get a linked program object
   userData->programObject = esCreateProgram(vShaderStr, fShaderStr);

   // Get the attribute locations
   userData->positionLoc = glGetAttribLocation ( userData->programObject, "a_position" );

   // Get the uniform locations
   userData->mvpLoc = glGetUniformLocation( userData->programObject, "mvp_matrix" );

   // Generate the vertex data
   userData->numIndices = esGenCube( 1.0, &userData->vertices,
                                        NULL, NULL, &userData->indices );

   // Starting rotation angle for the cube
   userData->angle = 45.0f;

   glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );

   return GL_TRUE;
}

void Origin::drawFrame()
{

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

	UserData *userData = (UserData*)esContext.userData;
	// clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// use the program object
	glUseProgram(userData->programObject);
	// Load the vertex position
	glVertexAttribPointer(userData->positionLoc, 3, GL_FLOAT,
	                           GL_FALSE, 3 * sizeof(GLfloat),
	                           userData->vertices);
	glEnableVertexAttribArray(userData->positionLoc);
	// load colors
	glVertexAttribPointer(userData->colorLoc, 4, GL_FLOAT, GL_FALSE, 0, vColors);
	glEnableVertexAttribArray(userData->colorLoc);
	// Load the MVP matrix
	glUniformMatrix4fv(userData->mvpLoc, 1, GL_FALSE,
						(GLfloat*) &userData->mvpMatrix.m[0][0]);
	// Draw the cube
	glDrawElements(GL_TRIANGLES, userData->numIndices, GL_UNSIGNED_SHORT,
						userData->indices);
	/*
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, vColors);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_LINES, 0, 6);*/

}

void Origin::cleanup() {
	UserData *userData = esContext.userData;

	if (userData->vertices != NULL) {
		free(userData->vertices);
	}

	if (userData->indices != NULL) {
		free(userData->indices);
	}

	// Delete program object
	glDeleteProgram(userData->programObject);
}
