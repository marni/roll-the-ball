//
//  renderer.cpp
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 13/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#include "renderer.h"
#include "glshaders.h"

#include "ResourcePath.h"

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

using std::vector;



Renderer::Renderer()
{
    terrainVertShader = new GLShader();
    terrainFragShader = new GLShader();
    terrainProgram = new GLProgram();
}


Renderer::~Renderer()
{
    delete terrainVertShader;
    delete terrainFragShader;
    delete terrainProgram;
    
    delete scene;
}


void Renderer::onInit()
{
    scene = new Scene();
    terrainProgram->create();
    if (!terrainVertShader->loadFromFile("terrain.vert", GL_VERTEX_SHADER)) {
        std::cerr << "[ERROR][Renderer] Failed to load terrain.vert shader." << std::endl;
    }
    if (!terrainFragShader->loadFromFile("terrain.frag", GL_FRAGMENT_SHADER)) {
        std::cerr << "[ERROR][Renderer] Failed to load terrain.frag shader." << std::endl;
    }
    terrainProgram->addShader(terrainVertShader);
    terrainProgram->addShader(terrainFragShader);
    
    if (!terrainProgram->linkShaders()) {
        std::cerr << "[ERROR][Renderer] Failed to link the program!" << std::endl;
    }
    terrainProgram->useProgram();
    
    // create the scene
    scene->onInit();
}


void Renderer::onClose() {
    terrainProgram->deleteProgram();
    terrainVertShader->deleteShader();
    terrainFragShader->deleteShader();
}


void Renderer::draw()
{
    // terrainProgram->useProgram();
    scene->draw();
}

