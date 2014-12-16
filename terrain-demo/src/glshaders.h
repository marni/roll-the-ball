//
//  ShaderLoader.h
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 14/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#ifndef __terrain_demo__glshaders__
#define __terrain_demo__glshaders__

#include <OpenGl/gl3.h>

#include <string>
#include <vector>


class GLShader {
    
public:
    GLShader();
    bool loadFromFile(std::string filename, int aType);
    void deleteShader();
    
    bool isLoaded;
    GLuint shaderId;
    
};


class GLProgram {
    
public:
    GLProgram();
    void create();
    void deleteProgram();
    bool addShader(GLShader* aShader);
    bool linkShaders();
    void useProgram();
    
    GLuint programId;
    bool isLinked;
};

#endif /* defined(__terrain_demo__glshaders__) */
