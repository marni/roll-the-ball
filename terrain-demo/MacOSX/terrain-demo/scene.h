//
//  scene.h
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 14/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#ifndef __terrain_demo__scene__
#define __terrain_demo__scene__

#include "hgtloader.h"

class Scene
{
    
public:
    
    Scene();
    ~Scene();
    
    void createScene();
    
private:
    
    const HGT_Array* heightdata;
    
};

#endif /* defined(__terrain_demo__scene__) */
