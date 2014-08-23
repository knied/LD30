//
//  Renderer.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "Renderer.h"
#include "TextFile.h"

Renderer::Renderer(SDLSystem const& system) {
    TextFile vert(system.resource_path() + "basic.vert");
    TextFile frag(system.resource_path() + "basic.frag");
    
    _program.load_shaders(vert.content(), frag.content(), {}, {});
    _model_view_location = _program.uniform_location("model_view");
    _texture0_location = _program.uniform_location("texture0");
    _fade_location = _program.uniform_location("fade");
}

void Renderer::add(Sprite* sprite, Mth::Matrix<float, 3, 3> const& trafo, int layer, float fade) {
    std::vector<DrawCall>::iterator it = _drawcalls.begin();
    while (it != _drawcalls.end() && it->layer > layer) {
        it++;
    }
    _drawcalls.insert(it, {
        sprite, trafo, layer, fade
    });
}

void Renderer::flush() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    
    GLBindProgram bind_program(_program);
    bind_program.set_uniform(_texture0_location, 0);
    
    for (DrawCall& dc : _drawcalls) {
        bind_program.set_uniform(_model_view_location, dc.trafo);
        bind_program.set_uniform(_fade_location, dc.fade);
        dc.sprite->draw();
    }
    
    _drawcalls.clear();
}