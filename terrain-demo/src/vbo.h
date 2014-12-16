//
//  vbo.h
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 16/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#ifndef __terrain_demo__vbo__
#define __terrain_demo__vbo__

#include <vector>
#include <OpenGL/gl3.h>


class VBO {

public:
    VBO();
    void create();
    void bind(GLuint aType = GL_ARRAY_BUFFER);
    void addData(void* dataPtr, GLuint dataSize);
    void copyToGPU(GLuint usageHint = GL_STATIC_DRAW);

private:
    GLuint bufferId;
    int size;
    int bufferType;
    std::vector<unsigned char> data;
    
};

#endif /* defined(__terrain_demo__vbo__) */
