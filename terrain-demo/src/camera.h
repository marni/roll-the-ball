//
//  camera.h
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 16/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#ifndef __terrain_demo__camera__
#define __terrain_demo__camera__

#include <glm/glm.hpp>



class Camera {

public:
    Camera();
    
    void setPosition(glm::vec3 aPosition);
    void setViewVector(glm::vec3 aVector);
    void setUpVector(glm::vec3 aVector);
    
    glm::mat4 getViewMatrix();


public:
    glm::vec3 position;
    glm::vec3 viewVector;
    glm::vec3 upVector;

    
    
};

#endif /* defined(__terrain_demo__camera__) */
