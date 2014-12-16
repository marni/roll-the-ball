//
//  scene.cpp
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 14/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#include "scene.h"
#include "hgtloader.h"

#include <glm/glm.hpp>

#include <vector>

using std::vector;




Scene::Scene()
{
}


Scene::~Scene()
{
    delete heightdata;
}


void Scene::onInit()
{
    heightdata = loadHeightArray("N60E010.hgt");
    
    // let us ignore the height data for a bit, and use hardcoded
    // 4x4 lattice of height points as defined below:
    const int rowsCount = 4;
    const int colsCount = 4;
    
    int data[rowsCount][colsCount] = {
        100, 100, 100, 100,
        200, 100, 100, 100,
        100, 100, 300, 100,
        100, 100, 100, 100 };
    
    // container with vertex data
    glm::vec3 vertexData[rowsCount][colsCount];
    
    for (int i = 0; i < rowsCount; i++) {
        for (int j = 0; j < colsCount; j++) {
            float scaleC = float(j) / float(colsCount - 1);
            float scaleR = float(i) / float(rowsCount - 1);
            float vertexHeight = float(data[i][j]) / 300.0f; // normalized for the dummy data
            vertexData[i][j] = glm::vec3(-0.5f + scaleC, vertexHeight - 0.5f, -0.5f + scaleR);
        }
    }
    
    // container with indexes
    this->indexCount = (rowsCount - 1) * colsCount * 2 + rowsCount - 1;
    GLuint vertexIndices[indexCount];
    this->PrimitiveRestartIndex = rowsCount * colsCount;
    int n = 0;
    for (int i = 0; i < rowsCount - 1; i++) {
        for (int j = 0; j < colsCount; j++) {
            for (int k = 0; k < 2; k++) {
                int row = i + (1-k);
                int index = row * colsCount + j;
                vertexIndices[n++] = (GLuint)index;
            }
        }
        // Restart triangle strips
        vertexIndices[n++] = PrimitiveRestartIndex;
    }
    
    
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
    
    // This will identify our GPU buffers
    // 0 - vertex buffer
    // 1 - vertex indexes
    GLuint gpuBuffers[2];
    glGenBuffers(2, gpuBuffers);
    
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, gpuBuffers[0]);
    // Push the vertices to GPU
    glBufferData(GL_ARRAY_BUFFER, rowsCount * colsCount * sizeof(glm::vec3), vertexData, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gpuBuffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(PrimitiveRestartIndex);

}


void Scene::draw() {
    glBindVertexArray(vaoId);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

