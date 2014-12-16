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



class Renderer
{
    
public:
    
    Renderer();
    ~Renderer();
    
    void onInit();
    void onClose();
    
    void draw();
    
private:
    
    Scene* scene;
    Camera* camera;
    
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    
    GLProgram* terrainProgram;
    GLShader* terrainVertShader;
    GLShader* terrainFragShader;

};

#endif /* defined(__terrain_demo__renderer__) */
