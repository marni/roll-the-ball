/*
 * esUtil.h
 */

#ifndef ESUTIL_H_
#define ESUTIL_H_


#ifdef _WIN64 
    // Let us assume it is Windows
    #include <time.h>
    #include <Windows.h>
    //#define GL_GLEXT_PROTOTYPES
    #include <gl/glew.h>
    #include <gl/Glext.h>
    #include <gl/GL.h>
    #include <gl/GLU.h>
    #include <gl/GLUT.h>
    #include <SDL.h>
    #include <SDL_opengl.h>
    #pragma comment(lib, "opengl32.lib")
    #pragma comment(lib, "glu32.lib")
    #pragma comment(lib, "glew32.lib")
    #pragma comment(lib, "SDL2.lib")
    #pragma comment(lib, "SDL2main.lib")

#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE
        // Let us assume it is iOS
        #include "SDL.h"
        #include "SDL_opengles2.h"
        #include <time.h>
        #define TARGET_MOBILE 1
    #elif TARGET_OS_MAC
        // We assume have a Mac OSX
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_opengl.h>
        #include <sys/time.h>
    #endif

#elif __ANDROID__
    #include <SDL.h>
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
    #define TARGET_MOBILE 1
#else
    #error "Unknown platform"
#endif

#include <string>
#include <cmath>



// adopted from the code of esUtil.h, see:
#define ESUTIL_API

#define PI 3.1415926535897932384626433832795f

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif


typedef struct
{
	GLfloat m[4][4];
} ESMatrix;


typedef struct
{
	GLuint programObject; // Handle to a program object

	GLint positionLoc; // Attribute location for position
	GLint colorLoc; // Attribute location for color
	GLint normalsLoc; // Attribute location for normals array

	GLint mvpLoc; // Uniform location
	GLint mvLoc; // Uniform location
	GLint lightPosLoc; // Uniform location


	GLfloat *vertices; // Vertex data
	GLuint *indices;
	int numIndices;
	GLfloat *normals; // Normals

	GLfloat angle; // Rotation angle

	ESMatrix mvpMatrix; // MVP matrix
} UserData;


typedef struct _escontext
{
	UserData* userData;
	GLint width;  // window width
	GLint height; // window height
} ESContext;



GLuint esLoadShader(GLenum, std::string);
GLuint esCreateProgram(std::string pVertexSource, std::string pFragmentSource);

void esNormalize(float v[3]);
void esNorm_crossprod(float v1[3], float v2[3], float out[3]);

void checkGLError(const char* op);
void printGLString(const char *name, GLenum s);

//
/// \brief Initialize ES framework context.  This must be called before calling any other functions.
/// \param esContext Application context
//
void ESUTIL_API esInitContext ( ESContext *esContext );



//
/// \brief Generates geometry for a sphere.  Allocates memory for the vertex data and stores
///        the results in the arrays.  Generate index list for a TRIANGLE_STRIP
/// \param numSlices The number of slices in the sphere
/// \param vertices If not NULL, will contain array of float3 positions
/// \param normals If not NULL, will contain array of float3 normals
/// \param texCoords If not NULL, will contain array of float2 texCoords
/// \param indices If not NULL, will contain the array of indices for the triangle strip
/// \return The number of indices required for rendering the buffers (the number of indices stored in the indices array
///         if it is not NULL ) as a GL_TRIANGLE_STRIP
//
int ESUTIL_API esGenSphere ( int numSlices, float radius, GLfloat **vertices, GLfloat **normals,
                             GLfloat **texCoords, GLuint **indices );

//
/// \brief Generates geometry for a cube.  Allocates memory for the vertex data and stores
///        the results in the arrays.  Generate index list for a TRIANGLES
/// \param scale The size of the cube, use 1.0 for a unit cube.
/// \param vertices If not NULL, will contain array of float3 positions
/// \param normals If not NULL, will contain array of float3 normals
/// \param texCoords If not NULL, will contain array of float2 texCoords
/// \param indices If not NULL, will contain the array of indices for the triangle strip
/// \return The number of indices required for rendering the buffers (the number of indices stored in the indices array
///         if it is not NULL ) as a GL_TRIANGLES
//
int ESUTIL_API esGenCube ( float scale, GLfloat **vertices, GLfloat **normals,
                           GLfloat **texCoords, GLuint **indices );

//
/// \brief Loads a 24-bit TGA image from a file
/// \param fileName Name of the file on disk
/// \param width Width of loaded image in pixels
/// \param height Height of loaded image in pixels
///  \return Pointer to loaded image.  NULL on failure.
//
char* ESUTIL_API esLoadTGA ( char *fileName, int *width, int *height );


//
/// \brief multiply matrix specified by result with a scaling matrix and return new matrix in result
/// \param result Specifies the input matrix.  Scaled matrix is returned in result.
/// \param sx, sy, sz Scale factors along the x, y and z axes respectively
//
void ESUTIL_API esScale(ESMatrix *result, GLfloat sx, GLfloat sy, GLfloat sz);

//
/// \brief multiply matrix specified by result with a translation matrix and return new matrix in result
/// \param result Specifies the input matrix.  Translated matrix is returned in result.
/// \param tx, ty, tz Scale factors along the x, y and z axes respectively
//
void ESUTIL_API esTranslate(ESMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz);

//
/// \brief multiply matrix specified by result with a rotation matrix and return new matrix in result
/// \param result Specifies the input matrix.  Rotated matrix is returned in result.
/// \param angle Specifies the angle of rotation, in degrees.
/// \param x, y, z Specify the x, y and z coordinates of a vector, respectively
//
void ESUTIL_API esRotate(ESMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

//
// \brief multiply matrix specified by result with a perspective matrix and return new matrix in result
/// \param result Specifies the input matrix.  new matrix is returned in result.
/// \param left, right Coordinates for the left and right vertical clipping planes
/// \param bottom, top Coordinates for the bottom and top horizontal clipping planes
/// \param nearZ, farZ Distances to the near and far depth clipping planes.  Both distances must be positive.
//
void ESUTIL_API esFrustum(ESMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);

//
/// \brief multiply matrix specified by result with a perspective matrix and return new matrix in result
/// \param result Specifies the input matrix.  new matrix is returned in result.
/// \param fovy Field of view y angle in degrees
/// \param aspect Aspect ratio of screen
/// \param nearZ Near plane distance
/// \param farZ Far plane distance
//
void ESUTIL_API esPerspective(ESMatrix *result, float fovy, float aspect, float nearZ, float farZ);

//
/// \brief multiply matrix specified by result with a perspective matrix and return new matrix in result
/// \param result Specifies the input matrix.  new matrix is returned in result.
/// \param left, right Coordinates for the left and right vertical clipping planes
/// \param bottom, top Coordinates for the bottom and top horizontal clipping planes
/// \param nearZ, farZ Distances to the near and far depth clipping planes.  These values are negative if plane is behind the viewer
//
void ESUTIL_API esOrtho(ESMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);

//
/// \brief perform the following operation - result matrix = srcA matrix * srcB matrix
/// \param result Returns multiplied matrix
/// \param srcA, srcB Input matrices to be multiplied
//
void ESUTIL_API esMatrixMultiply(ESMatrix *result, ESMatrix *srcA, ESMatrix *srcB);

//
//// \brief return an indentity matrix
//// \param result returns identity matrix
//
void ESUTIL_API esMatrixLoadIdentity(ESMatrix *result);



#endif /* ESUTIL_H_ */
