//
//  application.cpp
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 13/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#include <SFML/Audio.hpp>
#include "ResourcePath.h"

#include "application.h"



Application::Application()
{
    renderer = new Renderer();
    scene = new Scene();
}

Application::~Application()
{
    delete renderer;
    delete scene;
}


void Application::onInit()
{
    // create the scene
    scene->createScene();
    // initialize the renderer
    renderer->onInit(scene);
}

void Application::onClose()
{
    renderer->notifyClose();
}




void Application::startEventLoop()
{
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }
    
    // Play the music
    music.play();
    
    sf::Window *window = renderer->getWindowHandle();
    
    // Start the event loop
    bool isAppRunning = window->isOpen();
    
    while (isAppRunning) {
        
        // Process events
        sf::Event event;
        while (window->pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                isAppRunning = false;
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                isAppRunning = false;
            }
        }
    }
    // we finished the event loop
}