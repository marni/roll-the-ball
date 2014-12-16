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

#define GLM_FORCE_RADIANS
#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

using std::vector;



Renderer::Renderer()
{
    camera = new Camera();
    
    terrainVertShader = new GLShader();
    terrainGeomShader = new GLShader();
    terrainFragShader = new GLShader();
    terrainProgram = new GLProgram();
}


Renderer::~Renderer()
{
    delete terrainVertShader;
    delete terrainFragShader;
    delete terrainGeomShader;
    delete terrainProgram;

    delete camera;
    delete scene;
}


void Renderer::onInit()
{
    scene = new Scene();
    terrainProgram->create();
    if (!terrainVertShader->loadFromFile("terrain.vert", GL_VERTEX_SHADER)) {
        std::cerr << "[ERROR][Renderer] Failed to load terrain.vert shader." << std::endl;
    }
    if (!terrainGeomShader->loadFromFile("terrain.geom", GL_GEOMETRY_SHADER)) {
        std::cerr << "[ERROR][Renderer] Failed to load terrain.geom shader." << std::endl;
    }
    if (!terrainFragShader->loadFromFile("terrain.frag", GL_FRAGMENT_SHADER)) {
        std::cerr << "[ERROR][Renderer] Failed to load terrain.frag shader." << std::endl;
    }
    terrainProgram->addShader(terrainVertShader);
    terrainProgram->addShader(terrainGeomShader);
    terrainProgram->addShader(terrainFragShader);
    
    if (!terrainProgram->linkShaders()) {
        std::cerr << "[ERROR][Renderer] Failed to link the program!" << std::endl;
    }
    terrainProgram->useProgram();
    
    // create the scene
    scene->onInit();
    
    modelMatrix = glm::mat4(1.0);
    //camera->setPosition(glm::vec3(0.0, 1.0, 1.0));
    viewMatrix = camera->getViewMatrix();
    projectionMatrix = glm::mat4(1.0);
    
    terrainProgram->setUniform("modelMatrix", modelMatrix);
    terrainProgram->setUniform("viewMatrix", viewMatrix);
    terrainProgram->setUniform("projectionMatrix", projectionMatrix);
}


void Renderer::onClose() {
    terrainProgram->deleteProgram();
    terrainVertShader->deleteShader();
    terrainFragShader->deleteShader();
}


void Renderer::draw()
{
    // terrainProgram->useProgram();
    glm::mat4 tmp = modelMatrix;
    tmp = glm::rotate(tmp, 0.005f, glm::vec3(0.0, 1.0, 0.0));
    modelMatrix = tmp;
    terrainProgram->setUniform("modelMatrix", tmp);
    scene->draw();
}

