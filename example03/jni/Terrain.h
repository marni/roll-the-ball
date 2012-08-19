
#ifndef _Included_terrain_h
#define _Included_terrain_h


#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>

using namespace std;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define BITMAP_ID 0x4D42
#define MAP_X	32
#define MAP_Z	32
#define MAP_SCALE	20.0f



class Terrain
{

	//AUX_RGBImageRec
	unsigned char* imageData;		   // the map image data
	unsigned char* landTexture;	   // land texture data
	unsigned int land;			      // the land texture object

	////// Terrain Data
	float terrain[MAP_X][MAP_Z][3];		// heightfield terrain data (0-255); 256x256

	float radians, angle;

	float cameraX, cameraY, cameraZ;
	float lookX, lookY, lookZ;
	float mouseX, mouseY, mouseZ;

	GLuint __programObject;


public:
	void Initialize(float, float);
	void InitializeTerrain();
	void Render();
	bool LoadTextures();
	void CleanUp();


};

#endif

