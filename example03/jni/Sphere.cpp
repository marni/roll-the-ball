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
int Origin::init(float width, float height)
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
      "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);  \n"
      "}                                           \n";

   // show what we have under the bonet
   printGLString("Version", GL_VERSION);
   printGLString("Vendor", GL_VENDOR);
   printGLString("Renderer", GL_RENDERER);
   printGLString("Extensions", GL_EXTENSIONS);

   esContext.width = width;
   esContext.height = height;

   UserData *userData = (UserData*)esContext.userData;
   // Load the shaders and get a linked program object
   userData->programObject = esCreateProgram(vShaderStr, fShaderStr);

   // Get the attribute locations
   userData->positionLoc = glGetAttribLocation(userData->programObject, "a_position");
   userData->colorLoc = glGetAttribLocation(userData->programObject, "a_color");

   // Get the uniform locations
   userData->mvpLoc = glGetUniformLocation(userData->programObject, "mvp_matrix");

   // Generate the vertex data
   userData->numIndices = esGenCube(1.0, &userData->vertices,
                                      NULL, NULL, &userData->indices);
   /*
   userData->numIndices = esGenSphere(40, 1.0f, &userData->vertices,
                                         NULL, NULL, &userData->indices);
   */
   // Starting rotation angle for the cube
   userData->angle = 40.0f;

   glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

   return GL_TRUE;
}

void Origin::drawFrame()
{
	ESMatrix perspective;
	ESMatrix modelview;
	float    aspect;


	UserData *userData = (UserData*)esContext.userData;
	// clear the color buffer
	glViewport(0, 0, esContext.width, esContext.height);
	glClear(GL_COLOR_BUFFER_BIT);

	   // Compute a rotation angle based on time to rotate the cube
	   userData->angle += 1.0f;
	   if( userData->angle >= 360.0f )
	      userData->angle -= 360.0f;


	   // Compute the window aspect ratio
	   aspect = esContext.width / esContext.height;

	   // Generate a perspective matrix with a 60 degree FOV
	   esMatrixLoadIdentity(&perspective);
	   esPerspective(&perspective, 60.0f, aspect, 1.0f, 20.0f);

	   // Generate a model view matrix to rotate/translate the cube
	   esMatrixLoadIdentity(&modelview);

	   // Translate away from the viewer
	   esTranslate(&modelview, 0.0, 0.0, -4.0);

	   // Rotate the cube
	   esRotate(&modelview, userData->angle, 1.0, 0.0, 1.0);

	   // Compute the final MVP by multiplying the
	   // modevleiw and perspective matrices together
	   esMatrixMultiply(&userData->mvpMatrix, &modelview, &perspective);


	// use the program object
	glUseProgram(userData->programObject);
	// Load the vertex position
	glVertexAttribPointer(userData->positionLoc, 3, GL_FLOAT,
	                           GL_FALSE, 3 * sizeof(GLfloat),
	                           userData->vertices);
	glEnableVertexAttribArray(userData->positionLoc);
	// load colors
	glVertexAttribPointer(userData->colorLoc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), vColors);
	glEnableVertexAttribArray(userData->colorLoc);
	// Load the MVP matrix
	glUniformMatrix4fv(userData->mvpLoc, 1, GL_FALSE,
						(GLfloat*) &userData->mvpMatrix.m[0][0]);

	// Draw a sphere
	glDrawElements(GL_TRIANGLE_STRIP, userData->numIndices, GL_UNSIGNED_INT,
							userData->indices);
	
}

void Origin::cleanup() {
	Drawable::cleanup();
}
