//
//  application.h
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 13/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#ifndef __terrain_demo__application__
#define __terrain_demo__application__

#include "renderer.h"


class Application
{
    
public:
    Application();
    virtual ~Application();
    
    void onInit();
    void startEventLoop();
    void onClose();

private:
    Renderer* renderer;
    Scene* scene;
    
};

#endif /* defined(__terrain_demo__application__) */
