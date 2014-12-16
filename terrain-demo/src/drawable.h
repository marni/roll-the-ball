//
//  drawable.h
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 13/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#ifndef __terrain_demo__drawable__
#define __terrain_demo__drawable__

class Drawable
{
    
public:
    
    Drawable();
    virtual ~Drawable();
    
    virtual void onInit() = 0;
    virtual void draw() = 0;
        
};

#endif /* defined(__terrain_demo__drawable__) */
