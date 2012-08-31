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

#include "Sphere.h"



Sphere::Sphere() : Drawable() {
}

Sphere::~Sphere() {
}


///
// Initialize the shader and program object
//
void Sphere::init(float width, float height)
{
   Drawable::init(width, height);
   char vShaderStr[] =
      "attribute vec4 av4_position;                \n"
	  "uniform mat4 um4_mvp;                       \n"
      "void main()                                 \n"
      "{                                           \n"
      "   gl_Position = um4_mvp * av4_position;    \n"
      "}                                           \n";

   char fShaderStr[] =
      "precision mediump float;                    \n"
      "void main()                                 \n"
      "{                                           \n"
      "  gl_FragColor = vec4(1.0, 1.0, 0.0, 0.5);  \n"
      "}                                           \n";

   esContext.width = width;
   esContext.height = height;

   // Load the shaders and get a linked program object
   userData.programObject = esCreateProgram(vShaderStr, fShaderStr);
   userData.positionLoc = glGetAttribLocation(userData.programObject, "av4_position");
   userData.mvpLoc = glGetUniformLocation(userData.programObject, "um4_mvp");
   userData.numIndices = esGenSphere(40, 1.0f, &userData.vertices,
                                        NULL, NULL, &userData.indices);
}

void Sphere::drawFrame(ESMatrix* perspective) {
	ESMatrix modelview;
	glViewport(0, 0, getESContext()->width, getESContext()->height);
	esMatrixLoadIdentity(&modelview);
	esTranslate(&modelview, 0.0f, 0.0f, -2.0f);
	// Compute the final MVP by multiplying the
	// modelview and perspective matrices together
	esMatrixMultiply(&userData.mvpMatrix, &modelview, perspective);
	// use the program object
	glUseProgram(userData.programObject);
	// Load the vertex position
	glVertexAttribPointer(userData.positionLoc, 3, GL_FLOAT, GL_FALSE,
			3 * sizeof(GLfloat), userData.vertices);
	glEnableVertexAttribArray(userData.positionLoc);

	// Load the MVP matrix
	glUniformMatrix4fv(userData.mvpLoc, 1, GL_FALSE,
			(GLfloat*) &userData.mvpMatrix.m[0][0]);
LOGI("drawFrame drawing, number of indices: %d", userData.numIndices);
	// Draw a sphere
	glDrawElements(GL_TRIANGLE_STRIP, userData.numIndices, GL_UNSIGNED_INT, userData.indices);
}

