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

#include <OpenGL/gl3.h>


class Scene : public Drawable
{
    
public:
    
    Scene();
    ~Scene();
    
    void onInit();
    void draw();
    
private:
    
    const HGT_Array* heightdata;
    
    int indexCount;
    int PrimitiveRestartIndex;
    
    GLuint vaoId;

};

#endif /* defined(__terrain_demo__scene__) */
