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
    
    terrainWireframeVertShader = new GLShader();
    terrainWireframeGeomShader = new GLShader();
    terrainWireframeFragShader = new GLShader();
    wireframeProgram = new GLProgram();
    
    terrainColorVertShader = new GLShader();
    terrainColorFragShader = new GLShader();
    colorLightProgram = new GLProgram();
    
    FPS_counter = 0;
    FPS_startTime = std::chrono::high_resolution_clock::now();
}


Renderer::~Renderer()
{
    delete terrainWireframeVertShader;
    delete terrainWireframeFragShader;
    delete terrainWireframeGeomShader;
    delete wireframeProgram;
    
    delete terrainColorVertShader;
    delete terrainColorFragShader;
    delete colorLightProgram;
    
    delete camera;
    delete scene;
}


void Renderer::onInit()
{
    scene = new Scene();
    initWireframeProgram();
    initColorLightProgram();
}


void Renderer::initWireframeProgram() {
    wireframeProgram->create();
    if (!terrainWireframeVertShader->loadFromFile("terrain_wireframe.vert", GL_VERTEX_SHADER)) {
        std::cerr << "[ERROR][Renderer] Failed to load terrain.vert shader." << std::endl;
    }
    if (!terrainWireframeGeomShader->loadFromFile("terrain_wireframe.geom", GL_GEOMETRY_SHADER)) {
        std::cerr << "[ERROR][Renderer] Failed to load terrain.geom shader." << std::endl;
    }
    if (!terrainWireframeFragShader->loadFromFile("terrain_wireframe.frag", GL_FRAGMENT_SHADER)) {
        std::cerr << "[ERROR][Renderer] Failed to load terrain.frag shader." << std::endl;
    }
    wireframeProgram->addShader(terrainWireframeVertShader);
    wireframeProgram->addShader(terrainWireframeGeomShader);
    wireframeProgram->addShader(terrainWireframeFragShader);
    
    if (!wireframeProgram->linkShaders()) {
        std::cerr << "[ERROR][Renderer] Failed to link the program!" << std::endl;
    }
    wireframeProgram->useProgram();
    
    // create the scene
    scene->onInit();
    
    modelMatrix = glm::mat4(1.0);
    //camera->setPosition(glm::vec3(0.0, 1.0, 1.0));
    viewMatrix = camera->getViewMatrix();
    projectionMatrix = glm::mat4(1.0);
    
    wireframeProgram->setUniform("modelMatrix", modelMatrix);
    wireframeProgram->setUniform("viewMatrix", viewMatrix);
    wireframeProgram->setUniform("projectionMatrix", projectionMatrix);
    
    wireframeProgram->setUniform("colorVertexNormal", glm::vec3(1.0, 0.0, 0.0));
    wireframeProgram->setUniform("colorFaceNormal", glm::vec3(1.0, 1.0, 0.0));
}


void Renderer::initColorLightProgram() {
    colorLightProgram->create();

    if (!terrainColorVertShader->loadFromFile("terrain_color.vert", GL_VERTEX_SHADER)) {
        std::cerr << "[ERROR][Renderer] Failed to load terrain_color.vert shader." << std::endl;
    }
    if (!terrainColorFragShader->loadFromFile("terrain_color.frag", GL_FRAGMENT_SHADER)) {
        std::cerr << "[ERROR][Renderer] Failed to load terrain_color.frag shader." << std::endl;
    }

    colorLightProgram->addShader(terrainColorVertShader);
    colorLightProgram->addShader(terrainColorFragShader);
    
    if (!colorLightProgram->linkShaders()) {
        std::cerr << "[ERROR][Renderer] Failed to link the colorLight program!" << std::endl;
    }
    colorLightProgram->useProgram();
    colorLightProgram->setUniform("modelMatrix", modelMatrix);
    colorLightProgram->setUniform("viewMatrix", viewMatrix);
    colorLightProgram->setUniform("projectionMatrix", projectionMatrix);
}


void Renderer::onClose() {
    wireframeProgram->deleteProgram();
    terrainWireframeVertShader->deleteShader();
    terrainWireframeFragShader->deleteShader();
    
    colorLightProgram->deleteProgram();
    terrainColorVertShader->deleteShader();
    terrainColorFragShader->deleteShader();
}


void Renderer::draw(bool isDrawWireframe)
{
    FPS_counter++;
    if (FPS_counter > 200) {
        auto durationTime =
        std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - FPS_startTime).count();
        FPS = FPS_counter * 1000000.0 / durationTime;
        FPS_counter = 0;
        FPS_startTime = std::chrono::high_resolution_clock::now();
    }

    glm::mat4 tmp = modelMatrix;
    tmp = glm::rotate(tmp, 0.005f, glm::vec3(0.0, 1.0, 0.0));
    modelMatrix = tmp;
    if (isDrawWireframe) {
        wireframeProgram->useProgram();
        wireframeProgram->setUniform("modelMatrix", tmp);
    } else {
        colorLightProgram->useProgram();
        colorLightProgram->setUniform("modelMatrix", tmp);
    }
    scene->draw();
}

