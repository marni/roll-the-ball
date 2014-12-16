//
//  scene.cpp
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 14/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#include "scene.h"
#include "vbo.h"
#include "hgtloader.h"



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
    

    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
    
    prepareVertexData(&data[0][0], rowsCount, colsCount);
    
}




// returns the array to vertices
void Scene::prepareVertexData(int* data, int rowsCount, int colsCount) {

    // container with vertex data
    glm::vec3* vertexData = new glm::vec3[rowsCount * colsCount];
    
    for (int i = 0; i < rowsCount; i++) {
        for (int j = 0; j < colsCount; j++) {
            float scaleC = float(j) / float(colsCount - 1);
            float scaleR = float(i) / float(rowsCount - 1);
            float vertexHeight = float(data[i*rowsCount + j]) / 300.0f; // normalized for the dummy data
            vertexData[i*rowsCount + j] = glm::vec3(-0.5f + scaleC, vertexHeight - 0.5f, -0.5f + scaleR);
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
    
    // generate vertex normals
    
    glm::vec3* vertexNormals = prepareNormals(vertexData, rowsCount, colsCount);
    
    
    VBO vertexVBO;
    vertexVBO.create();
    
    for (int i = 0; i < rowsCount; i++) {
        for (int j = 0; j < colsCount; j++) {
            int index = i*rowsCount + j;
            vertexVBO.addData(&vertexData[index], sizeof(glm::vec3));       // vertex
            vertexVBO.addData(&vertexNormals[index], sizeof(glm::vec3));    // normals
        }
    }
    
    vertexVBO.bind();
    vertexVBO.copyToGPU();
    
    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), 0);
    
    // Normal vectors
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));
    
    GLuint indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);
    
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(PrimitiveRestartIndex);
    
    // dispose of local data
    delete vertexData;
    delete vertexNormals;
}



glm::vec3* Scene::prepareNormals(glm::vec3* vertexData, int rowsCount, int colsCount) {
    glm::vec3* allNormals = new glm::vec3[(rowsCount - 1) * (colsCount - 1) * 2];
    
    for (int i = 0; i < rowsCount - 1; i++) {
        for (int j = 0; j < colsCount - 1; j++) {
            glm::vec3 triangle_A[] =
            {
                vertexData[(i + 0) * rowsCount + j],
                vertexData[(i + 1) * rowsCount + j],
                vertexData[(i + 1) * rowsCount + j + 1]
            };
            glm::vec3 triangle_B[] =
            {
                vertexData[(i + 1) * rowsCount + j + 1],
                vertexData[(i + 0) * rowsCount + j + 1],
                vertexData[(i + 0) * rowsCount + j]
            };
            
            glm::vec3 normal_A = glm::cross(triangle_A[0] - triangle_A[1], triangle_A[1] - triangle_A[2]);
            glm::vec3 normal_B = glm::cross(triangle_B[0] - triangle_B[1], triangle_B[1] - triangle_B[2]);
            
            allNormals[i * rowsCount + j] = glm::normalize(normal_A);
            allNormals[i * rowsCount + j + 1] = glm::normalize(normal_B);
        }
    }
    
    glm::vec3* finalNormals = new glm::vec3[rowsCount * colsCount];
    const int offset = rowsCount*colsCount;
    
    for (int i = 0; i < rowsCount; i++) {
        for (int j = 0; j < colsCount; j++) {
            
            // Now we wanna calculate final normal for [i][j] vertex.
            // We will have a look at all triangles this vertex is part of,
            // and then we will make average vector of all adjacent triangles' normals
        
            glm::vec3 tmp = glm::vec3(0.0f, 0.0f, 0.0f);
            
            // Look for upper-left triangles
            if (j != 0 && i != 0) {
                tmp += allNormals[(i - 1) * rowsCount + (j - 1)] +
                       allNormals[(i - 1) * rowsCount + (j - 1) + offset];
            }

            // Look for upper-right triangles
            if (i != 0 && j != colsCount - 1) {
                tmp += allNormals[(i - 1) * rowsCount + j];
            }
            
            // Look for bottom-right triangles
            if (i != rowsCount - 1 && j != colsCount - 1) {
                tmp  += allNormals[i * rowsCount + j] +
                        allNormals[i * rowsCount + j + offset];
            }
            
            // Look for bottom-left triangles
            if (i != rowsCount - 1 && j != 0) {
                tmp += allNormals[i * rowsCount + j - 1 + offset];
            }
            
            finalNormals[i * rowsCount + j] = glm::normalize(tmp);
        }
    }
    return finalNormals;
}




void Scene::draw() {
    glBindVertexArray(vaoId);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

