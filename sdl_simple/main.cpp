//
//  main.cpp
//  roll-the-ball
//
//  Created by Mariusz Nowostawski on 14/11/13.
//  Copyright (c) 2013 Mariusz Nowostawski. All rights reserved.
//
//


#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "esUtil.hpp"
#include "Origin.hpp"
#include "Sphere.hpp"
#include "Terrain.hpp"


#define WIDTH  640
#define HEIGHT 480


Origin origin;
Terrain terrain;
Sphere sphere;


ESMatrix perspective;

GLfloat yaw = 0.0f;
GLfloat pitch = 0.0f;

float aspect;


void cleanup()
{
	origin.cleanup();
	sphere.cleanup();
	terrain.cleanup();
}

SDL_Window* window;

void drawFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    
    esMatrixLoadIdentity(&perspective);
	esPerspective(&perspective, 60.0f, aspect, 1.0f, 30.0f);
	esTranslate(&perspective, 0.0f, 0.0f, -5.0f);
    esRotate(&perspective, pitch, 1.0f, 0.0f, 0.0f);
	esRotate(&perspective, yaw, 0.0f, 1.0f, 0.0f);
    
	origin.drawFrame(&perspective);
	terrain.drawFrame(&perspective);
    sphere.drawFrame(&perspective);
    
    SDL_GL_SwapWindow(window);
}


void setupWindow(int width, int height)
{
	glViewport(0, 0, width, height);
	aspect = (float)width / (float)height;
	// Generate a perspective matrix with a 60 degree FOV
	esMatrixLoadIdentity(&perspective);
    //LOGI("%f %d %d", aspect, width, height);
	esPerspective(&perspective, 60.0f, aspect, 1.0f, 30.0f);
	esTranslate(&perspective, 0.0f, 0.0f, -5.0f);
	//esRotate(&perspective, 45.0f, 1.0f, 0.0f, 0.0f);
	//esRotate(&perspective, -5.0f, 0.0f, 1.0f, 0.0f);
    
glEnableClientState(GL_VERTEX_ARRAY);
    
	origin.init(width, height);
	sphere.init(width, height);
	terrain.init(width, height);
}



static void setupSDL()
{
    if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVERYTHING) < 0 ) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    
    /* Quit SDL properly on exit */
    atexit(SDL_Quit);
    
    /* Get the current video information */
    window = SDL_CreateWindow("Roll the ball", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        fprintf(stderr, "Couldn't get video information: %s\n", SDL_GetError());
        exit(1);
    }
    
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    /* Set the minimum requirements for the OpenGL window
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    */
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    
    /* Note the SDL_DOUBLEBUF flag is not required to enable double
     * buffering when setting an OpenGL video mode.
     * Double buffering is enabled or disabled using the
     * SDL_GL_DOUBLEBUFFER attribute.
     */
    //glEnableClientState(GL_VERTEX_ARRAY);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_ShowWindow(window);

    // SDL_GL_SetSwapInterval(1);
    // SDL_GL_SwapWindow(window);
}


static void setupOpenGL()
{
    setupWindow(WIDTH, HEIGHT);
}


static void mainLoop()
{
    SDL_Event event;
    
    while (1) {
        /* process pending events */
        while( SDL_PollEvent( &event ) ) {
            switch( event.type ) {
                case SDL_KEYDOWN:
                    switch ( event.key.keysym.sym ) {
                        case SDLK_ESCAPE:
                            exit(0);
                            break;
                            
                        default:
                            //no default key processing
                            //(stops compiler warnings for unhandled SDL keydefs
                            break;
                    }
                    break;
                    
                case SDL_MOUSEMOTION:
                    pitch += event.motion.yrel;
                    yaw += event.motion.xrel;
                    break;
                    
                case SDL_QUIT:
                    exit (0);
                    break;
            }
        }
        
        /* update the screen */
        drawFrame();
        
        /* Wait 50ms to avoid using up all the CPU time */
        SDL_Delay( 50 );
    }
}




int main(int argc, const char * argv[])
{
    setupSDL();
    setupOpenGL();
    mainLoop();
    
    cleanup();
    return 0;
}

