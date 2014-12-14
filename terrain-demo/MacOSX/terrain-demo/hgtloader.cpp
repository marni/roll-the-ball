//
//  hgtloader.cpp
//  terrain-demo
//
//  Created by Mariusz Nowostawski on 14/12/14.
//  Copyright (c) 2014 Mariusz Nowostawski. All rights reserved.
//

#include "hgtloader.h"

#include "ResourcePath.h"

#include <fstream>


const HGT_Array* loadHeightArray(std::string hgtFilename)
{

    HGT_Array* heightdata = new HGT_Array();

    std::ifstream::pos_type size;
    char memblock[2];
    
    std::ifstream file (resourcePath() + hgtFilename, std::ios::in|std::ios::binary|std::ios::ate);
    
    if (file.is_open())
    {
        file.seekg (0, std::ios::beg);
        file.read (memblock, 2);

        for ( int r = 0; r < SRTM_VERSION ; r++ ) {
            for ( int c = 0 ; c < SRTM_VERSION; c++ ) {
                int value = ((((unsigned char)memblock[0]) << 8) | (unsigned char)memblock[1]);
                heightdata->height[r][c] = value;
                file.read (memblock, 2);
            }
        }
    
        file.close();
    }
    return heightdata;
}