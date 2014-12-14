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



Renderer::Renderer()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    
    // Create the main window
    window = new sf::Window(sf::VideoMode(800, 600), "Terrain Demo", sf::Style::Default, settings);
    window->setVerticalSyncEnabled(true);
    settings = window->getSettings();
    
    std::cout << "depth bits:" << settings.depthBits << std::endl;
    std::cout << "stencil bits:" << settings.stencilBits << std::endl;
    std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
    std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

    isAppRunning = true;
}


Renderer::~Renderer()
{
    delete window;
}


void renderingLoop(Renderer* r)
{
    while(r->isAppRunning) {
        r->drawScene();
    }
}


void Renderer::onInit(Scene* aScene)
{
    scene = aScene;
    // attach the application icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    std::thread* r = new std::thread(renderingLoop, this);
}


void Renderer::notifyClose()
{
    isAppRunning = false;
}


sf::Window* Renderer::getWindowHandle()
{
    return window;
}


void Renderer::onClose()
{

}


void Renderer::drawScene()
{
    window->display();
}


void Renderer::draw(Drawable* drawable)
{

}