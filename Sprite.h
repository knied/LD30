//
//  Sprite.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef __LD30Xcode__Sprite__
#define __LD30Xcode__Sprite__

#include <iostream>
#include <vector>
#include "GLClasses.h"
#include "SDLClasses.h"
#include "MthMatrix.h"

class Sprite {
    GLVertexArray _vertex_array;
    GLBuffer _buffer;
    GLTexture _texture;
    int _width;
    int _height;
    
public:
    typedef Mth::CVector<uint8_t, 4> Color;
    
    Sprite(SDLImage const& image_loader, std::string const& filename);
    ~Sprite();
    
    void draw();
    
}; // Sprite

#endif /* defined(__LD30Xcode__Sprite__) */
