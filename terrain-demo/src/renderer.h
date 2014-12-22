//
//  renderer.h
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 13/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#ifndef __terrain_demo__renderer__
#define __terrain_demo__renderer__

#include "drawable.h"
#include "scene.h"
#include "camera.h"
#include "glshaders.h"

#include <chrono>


class Renderer
{
    
public:
    
    Renderer();
    ~Renderer();
    
    void onInit();
    void onClose();
    
    void draw(bool isDrawWireframe = true);
    
    float FPS; // the actual current value of FPS
    
    
private:
    
    Scene* scene;
    Camera* camera;
    
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    
    GLProgram* wireframeProgram;
    void initWireframeProgram();

    GLProgram* colorLightProgram;
    void initColorLightProgram();
    
    GLShader* terrainWireframeVertShader;
    GLShader* terrainWireframeGeomShader;
    GLShader* terrainWireframeFragShader;
    
    GLShader* terrainColorVertShader;
    GLShader* terrainColorFragShader;

    
    
    unsigned long FPS_counter;
    std::chrono::time_point<std::chrono::high_resolution_clock> FPS_startTime;

};

#endif /* defined(__terrain_demo__renderer__) */
