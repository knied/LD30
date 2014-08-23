//
//  Renderer.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef __LD30Xcode__Renderer__
#define __LD30Xcode__Renderer__

#include <iostream>
#include "Sprite.h"

struct DrawCall {
    Sprite* sprite;
    Mth::Matrix<float, 3, 3> trafo;
    int layer;
    float fade;
};

class Renderer {
    GLProgram _program;
    GLint _model_view_location;
    GLint _texture0_location;
    GLint _fade_location;
    
    std::vector<DrawCall> _drawcalls;
    
public:
    Renderer(SDLSystem const& system);
    
    void add(Sprite* sprite, Mth::Matrix<float, 3, 3> const& trafo, int layer, float fade);
    void flush();
};

#endif /* defined(__LD30Xcode__Renderer__) */
