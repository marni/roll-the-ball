//
//  scene.cpp
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 14/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#include "scene.h"
#include "hgtloader.h"



Scene::Scene()
{
    heightdata = loadHeightArray("N60E010.hgt");
}


Scene::~Scene()
{
    delete heightdata;
}


void Scene::createScene()
{

}