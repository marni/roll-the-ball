//
//  hgtloader.h
//  terrain-demo
//
//  Those are utility functions for loading NASA HGT height
//  data files. Work in progress: most things are hardcoded
//  for simple demop purposes.
//
//
//  Created by Mariusz Nowostawski on 14/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#ifndef __terrain_demo__hgtloader__
#define __terrain_demo__hgtloader__

#include <string>

// 3601 for 1 degree resolution files
// 1201 for 3 degree resolution
#define SRTM_VERSION 3601


typedef struct { int height[SRTM_VERSION][SRTM_VERSION]; } HGT_Array;


const HGT_Array* loadHeightArray(std::string hgt_filename);



#endif /* defined(__terrain_demo__hgtloader__) */
