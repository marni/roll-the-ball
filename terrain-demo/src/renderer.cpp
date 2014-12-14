//
//  renderer.cpp
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 13/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#include "renderer.h"

#include "ResourcePath.h"

#include <iostream>
#include <thread>

#include <SFML/OpenGL.hpp>


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}


void Renderer::onInit()
{
}


void Renderer::draw(sf::Window* window, Drawable* drawable)
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
}