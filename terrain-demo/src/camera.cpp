//
//  camera.cpp
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 16/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>



Camera::Camera() {
    position = glm::vec3(0.0, 0.0, 0.0);
    upVector = glm::vec3(0.0, 1.0, 0.0);
    viewVector = glm::vec3(0.0, 0.0, -1.0);
}

void Camera::setPosition(glm::vec3 aPosition) {
    position = aPosition;
}

void Camera::setViewVector(glm::vec3 aVector) {
    viewVector = aVector;
}

void Camera::setUpVector(glm::vec3 aVector) {
    upVector = aVector;
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, viewVector, upVector);
}
