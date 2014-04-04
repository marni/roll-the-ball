//
//  main.cpp
//  roll-the-ball
//
//  Created by Mariusz Nowostawski on 14/11/13.
//  Copyright (c) 2013 Mariusz Nowostawski. All rights reserved.
//
//


#include "esUtil.hpp"

#include "Origin.hpp"
#include "Sphere.hpp"
#include "Terrain.hpp"

//#define WIDTH  640
//#define HEIGHT 480

#define SINT16_MAX ((float)(0x7FFF))

/*  If we aren't on an iPhone, then this definition ought to yield reasonable behavior */
#ifndef SDL_IPHONE_MAX_GFORCE
#define SDL_IPHONE_MAX_GFORCE 5.0f
#endif


Origin origin;
Terrain terrain;
Sphere sphere;


SDL_Window* window;
SDL_Joystick* joystick;




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



void drawFrame()
{
    float ax = SDL_JoystickGetAxis(joystick, 0);
    float ay = SDL_JoystickGetAxis(joystick, 1);

    
    /* update velocity from accelerometer
     the factor SDL_IPHONE_MAX_G_FORCE / SINT16_MAX converts between
     SDL's units reported from the joytick, and units of g-force, as reported by the accelerometer
     */
    
    float axm = 1.0f;
    float aym = 1.0f;
    
#if TARGET_OS_IPHONE || __ANDROID__
    axm = 5 * SDL_IPHONE_MAX_GFORCE / SINT16_MAX;
    aym = 5 * SDL_IPHONE_MAX_GFORCE / SINT16_MAX;
#endif
    
    pitch += ay * aym;
    yaw += ax * axm;

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
#ifdef TARGET_OS_IPHONE
#elif __ANDROID__
#else
    glEnableClientState(GL_VERTEX_ARRAY);
#endif
	origin.init(width, height);
	sphere.init(width, height);
	terrain.init(width, height);
}



static void setupSDL()
{
    if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_JOYSTICK ) < 0 ) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    
    joystick = SDL_JoystickOpen(0);
    if (joystick == NULL) {
        fprintf(stderr, "No joystick found\n");
    }
    
    /* Quit SDL properly on exit */
    atexit(SDL_Quit);
    
    /* Get the current video information */
    Uint32 WINDOW_FLAGS = 0;
    
#ifdef TARGET_MOBILE
    WINDOW_FLAGS = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP;
#else
    WINDOW_FLAGS = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
#endif
    
    window = SDL_CreateWindow("Roll the ball",
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              0, 0, WINDOW_FLAGS);

    if (window == NULL) {
        fprintf(stderr, "Couldn't get video information: %s\n", SDL_GetError());
        exit(1);
    }
    
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    /* 
     Set the minimum requirements for the OpenGL window
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
    SDL_GL_CreateContext(window);
    SDL_ShowWindow(window);

#ifdef _WIN32
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
    }
#endif
    
    // SDL_GL_SetSwapInterval(1);
    // SDL_GL_SwapWindow(window);
}


static void setupOpenGL()
{
    int w,h;
    SDL_GetWindowSize(window, &w, &h);
    setupWindow(w, h);
}


static void mainLoop()
{
    SDL_Event event;
    bool running = true;
    
    while (running) {
        /* process pending events */
        while( SDL_PollEvent( &event ) ) {
            switch( event.type ) {
                case SDL_KEYDOWN:
                    switch ( event.key.keysym.sym ) {
                        case SDLK_AC_BACK:
                        case SDLK_ESCAPE:
                            exit(0);
                            break;
                            
                        default:
                            //no default key processing
                            //(stops compiler warnings for unhandled SDL keydefs
                            break;
                    }
                    break;
            /**
                case SDL_MOUSEMOTION:
                    pitch += event.motion.yrel;
                    yaw += event.motion.xrel;
                    break;
             **/
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        
        /* update the screen */
        drawFrame();
        
        /* Wait 50ms to avoid using up all the CPU time */
        SDL_Delay( 50 );
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
}




int main(int argc, char * argv[])
{
    setupSDL();
    setupOpenGL();
    mainLoop();
    
    cleanup();
    return 0;
}

