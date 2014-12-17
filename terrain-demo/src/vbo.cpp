//
//  vbo.cpp
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 16/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#include "vbo.h"



VBO::VBO() {
    size = 0;
    bufferId = 0;
}


void VBO::create() {
    glGenBuffers(1, &bufferId);
}


void VBO::bind(GLuint aType) {
    bufferType = aType;
    glBindBuffer(bufferType, bufferId);
}


void VBO::addData(void* dataPtr, GLuint dataSize) {
    data.insert(data.end(), (unsigned char*)dataPtr, ((unsigned char*)dataPtr) + dataSize);
    size += dataSize;
}


void VBO::copyToGPU(GLuint usageHint) {
    unsigned char* raw = new unsigned char[data.size()];
    for (int i=0; i < data.size(); i++) {
        raw[i] = data[i];
    }
    glBufferData(bufferType, data.size(), raw, usageHint);
    
    data.clear();
    delete raw;
}

