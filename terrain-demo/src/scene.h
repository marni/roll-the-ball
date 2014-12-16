//
//  scene.h
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 14/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#ifndef __terrain_demo__scene__
#define __terrain_demo__scene__

#include "drawable.h"
#include "hgtloader.h"

#define GLM_FORCE_RADIANS

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>



class Scene : public Drawable
{
    
public:
    
    Scene();
    ~Scene();
    
    void onInit();
    void draw();
    
private:
    
    void prepareVertexData(int* heightData, int rowsCount, int colsCount);
    glm::vec3* prepareNormals(glm::vec3* vertexData, int rowsCount, int colsCount);
    
    const HGT_Array* heightdata;
    
    int indexCount;
    int PrimitiveRestartIndex;
    
    GLuint vaoId;

};

#endif /* defined(__terrain_demo__scene__) */
