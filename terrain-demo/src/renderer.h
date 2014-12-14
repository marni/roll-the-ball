//
//  renderer.h
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 13/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#ifndef __terrain_demo__renderer__
#define __terrain_demo__renderer__

#include <SFML/Graphics.hpp>

#include "drawable.h"
#include "scene.h"



class Renderer
{
    
public:
    
    Renderer();
    ~Renderer();
    
    void onInit();
    void draw(sf::Window*, Drawable*);

};

#endif /* defined(__terrain_demo__renderer__) */
