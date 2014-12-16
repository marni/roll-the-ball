//
//  application.cpp
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 13/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#include <iostream>
#include <SFML/Audio.hpp>
#include <OpenGL/gl3.h>

#include "ResourcePath.h"

#include "application.h"



Application::Application()
{
    renderer = new Renderer();
}

Application::~Application()
{
    delete renderer;
    delete window;
}


void Application::onInit()
{
    // setup Open GL context, and window
    initializeWindow();

    // initialize the renderer
    renderer->onInit();
}


void Application::onClose()
{
    renderer->onClose();
}


void Application::startMainLoop()
{
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }
    
    // Play the music
    //music.play();
    
    // Start the event loop
    bool isAppRunning = window->isOpen();
    
    glClearColor(0.65f, 0.65f, 0.65f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    while (isAppRunning) {        
        // Process events
        sf::Event event;
        while (window->pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                isAppRunning = false;
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                // Escape pressed: exit
                isAppRunning = false;
            } else if (event.type == sf::Event::Resized) {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }
        
        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT);
        
        // RENDER THE SCENE
        renderer->draw();
        
        // swap the buffers
        window->display();
    }
    
    // we finished the event loop, so we shut down the app
    window->close();
}



void Application::initializeWindow()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 2;
    
    // Create the main window
    window = new sf::RenderWindow(sf::VideoMode(800, 600, 24), "Terrain Demo", sf::Style::Titlebar | sf::Style::Close, settings);
    window->setVerticalSyncEnabled(true);
    window->setActive();
    
    settings = window->getSettings();
    
    std::cout << "depth bits:" << settings.depthBits << std::endl;
    std::cout << "stencil bits:" << settings.stencilBits << std::endl;
    std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
    std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;
    
    // attach the application icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

}

