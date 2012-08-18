

#include <GLES2/gl2.h>

#include "Terrain.h"
#include "Util.h"



static string vShaderStr =
          "attribute vec4 a_position;    \n"
          "attribute vec4 a_color;       \n"
          "varying vec4 v_color;         \n"
          "void main()                   \n"
          "{                             \n"
          "   v_color = a_color;     \n"
          "   gl_Position = a_position;  \n"
          "}                             \n";

static string fShaderStr =
        "#ifdef GL_ES                  \n"
        "precision highp float;        \n"
        "#endif                        \n"
        "                              \n"
        "varying vec4 v_color;         \n"
        "                              \n"
        "void main (void)              \n"
        "{                             \n"
        "    gl_FragColor = v_color;   \n"
        "}";



// InitializeTerrain()
// desc: initializes the heightfield terrain data
void Terrain::InitializeTerrain()
{
	// loop through all of the heightfield points, calculating
	// the coordinates for each point
	/*
	for (int z = 0; z < MAP_Z; z++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			terrain[x][z][0] = float(x)*MAP_SCALE;				
			terrain[x][z][1] = (float)imageData[(z*MAP_Z+x)*3];
			terrain[x][z][2] = -float(z)*MAP_SCALE;
		}
	}*/
}

void Terrain::CleanUp()
{
	free(imageData);
	free(landTexture);
}

// Initialize
// desc: initializes OpenGL
void Terrain::Initialize(float width, float height)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// clear to black

	//glShadeModel(GL_SMOOTH);					   // use smooth shading
	glEnable(GL_DEPTH_TEST);					   // hidden surface removal
	glEnable(GL_CULL_FACE);						   // do not calculate inside of poly's
	glFrontFace(GL_CCW);						      // counter clock-wise polygons are out

	glEnable(GL_TEXTURE_2D);					   // enable 2D texturing

	//imageData = LoadBitmapFile("terrain2.bmp", &bitmapInfoHeader);


	GLuint vertexShader;
	GLuint fragmentShader;
	GLint linked;

	vertexShader = Util::LoadShader(GL_VERTEX_SHADER, vShaderStr);
	fragmentShader = Util::LoadShader(GL_FRAGMENT_SHADER, fShaderStr);

	 __programObject = glCreateProgram();

	 if(__programObject==0 || vertexShader==0 || fragmentShader==0){
	     cerr << "Terrain::Initialize | problem loading shaders and/or creating program!" << endl;
	 }

	 glAttachShader(__programObject, vertexShader);
	 glAttachShader(__programObject, fragmentShader);
	 glLinkProgram(__programObject);
	 glGetProgramiv(__programObject, GL_LINK_STATUS, &linked);
	 if (!linked){
	     cerr << "Terrain::Initialize | problem linking program!" << endl;
	 }

	 //load all attributes
	 //bindShaderVariables();

	 //use the program
	 //glUseProgram(__programObject);

	// initialize the terrain data and load the textures
	InitializeTerrain();
	LoadTextures();




	glViewport(0, 0, width, height);	   // reset the viewport to new dimensions
	//glMatrixMode(GL_PROJECTION);		   // set projection matrix current matrix


	/*
	glLoadIdentity();					      // reset projection matrix
	// calculate aspect ratio of window
	gluPerspective(54.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);
	glMatrixMode(GL_MODELVIEW);			// set modelview matrix
	glLoadIdentity();					      // reset modelview matrix
	*/
}

const GLfloat triangle_vertices[] = { 0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f };


bool Terrain::LoadTextures()
{
	// load the land texture data
	//landTexture = LoadBitmapFile("green.bmp", &landInfo);
	//if (!landTexture)
		//return false;

	// generate the land texture as a mipmap
	//glGenTextures(1, &land);
	//glBindTexture(GL_TEXTURE_2D, land);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, landInfo.biHeight, landInfo.biWidth, GL_RGB, GL_UNSIGNED_BYTE, landTexture);

	return true;
}



void Terrain::Render()
{
	radians =  float(PI*(angle-90.0f)/180.0f);

	// calculate the camera's position
	cameraX = lookX + sin(radians)*mouseY;	   // multiplying by mouseY makes the
	cameraZ = lookZ + cos(radians)*mouseY;    // camera get closer/farther away with mouseY
	cameraY = lookY + mouseY / 2.0f;

	// calculate the camera look-at coordinates as the center of the terrain map
	lookX = (MAP_X*MAP_SCALE)/2.0f;
	lookY = 150.0f;
	lookZ = -(MAP_Z*MAP_SCALE)/2.0f;

	// clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		

    // Do we need it here? glUseProgram(__programObject);

    //glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, triangle_vertices);
	//glEnableVertexAttribArray(gvPositionHandle);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	/*
	glLoadIdentity();

	// set the camera position
	// gluLookAt(cameraX, cameraY, cameraZ, lookX, lookY, lookZ, 0.0, 1.0, 0.0);

	// set the current texture to the land texture
	glBindTexture(GL_TEXTURE_2D, land);

	// we are going to loop through all of our terrain's data points,
	// but we only want to draw one triangle strip for each set along the x-axis.
	for (int z = 0; z < MAP_Z-1; z++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < MAP_X-1; x++)
		{
			// for each vertex, we calculate the grayscale shade color, 
			// we set the texture coordinate, and we draw the vertex.
			/
			   the vertices are drawn in this order:

			   0  ---> 1
			          /
				    /
			     |/
			   2  ---> 3
			/
		
			// draw vertex 0
			glColor3f(terrain[x][z][1]/255.0f, terrain[x][z][1]/255.0f, terrain[x][z][1]/255.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(terrain[x][z][0], terrain[x][z][1], terrain[x][z][2]);

			// draw vertex 1
			glTexCoord2f(1.0f, 0.0f);
			glColor3f(terrain[x+1][z][1]/255.0f, terrain[x+1][z][1]/255.0f, terrain[x+1][z][1]/255.0f);
			glVertex3f(terrain[x+1][z][0], terrain[x+1][z][1], terrain[x+1][z][2]);

			// draw vertex 2
			glTexCoord2f(0.0f, 1.0f);
			glColor3f(terrain[x][z+1][1]/255.0f, terrain[x][z+1][1]/255.0f, terrain[x][z+1][1]/255.0f);
			glVertex3f(terrain[x][z+1][0], terrain[x][z+1][1], terrain[x][z+1][2]);

			// draw vertex 3
			glColor3f(terrain[x+1][z+1][1]/255.0f, terrain[x+1][z+1][1]/255.0f, terrain[x+1][z+1][1]/255.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(terrain[x+1][z+1][0], terrain[x+1][z+1][1], terrain[x+1][z+1][2]);
		}
		glEnd();
	}
	// enable blending
	glEnable(GL_BLEND);

	// enable read-only depth buffer
	glDepthMask(GL_FALSE);

	// set the blend function to what we use for transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	// set back to normal depth buffer mode (writable)
	glDepthMask(GL_TRUE);

	// disable blending
	glDisable(GL_BLEND);

	glFlush();
	//SwapBuffers(g_HDC);			// bring backbuffer to foreground

	 */
}



/*

// LoadBitmapFile
// desc: Returns a pointer to the bitmap image of the bitmap specified
//       by filename. Also returns the bitmap header information.
//		   No support for 8-bit bitmaps.
unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;							      // the file pointer
	BITMAPFILEHEADER	bitmapFileHeader;		// bitmap file header
	unsigned char		*bitmapImage;			// bitmap image data
	int					imageIdx = 0;		   // image index counter
	unsigned char		tempRGB;				   // swap variable

	// open filename in "read binary" mode
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	// read the bitmap file header
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

	// verify that this is a bitmap by checking for the universal bitmap id
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		fclose(filePtr);
		return NULL;
	}

	// read the bitmap information header
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

	// move file pointer to beginning of bitmap data
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// allocate enough memory for the bitmap image data
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

	// verify memory allocation
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	// read in the bitmap image data
	fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

	// make sure bitmap image data was read
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	// swap the R and B values to get RGB since the bitmap color format is in BGR
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	// close the file and return the bitmap image data
	fclose(filePtr);
	return bitmapImage;
} */

