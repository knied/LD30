//
//  Game.cpp
//
//  Created by Kristof Niederholtmeyer on 19.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "Game.h"
#include <iostream>
#include "gl3w.h"
#include "TextFile.h"

////////////////////////////////////////////////////////////////////////////////

Game::Game(std::string const& resource_path)
: _resource_path(resource_path) {
    TextFile vert(_resource_path + "basic.vert");
    TextFile frag(_resource_path + "basic.frag");
    
    _program.load_shaders(vert.content(), frag.content(), {}, {});
    _model_view_projection_location = _program.uniform_location("model_view_projection");
    
    {
        GLBindBuffer bind_buffer(_buffer);
        
        std::vector<Mth::CVector<float, 3>> v;
        v.push_back(Mth::make_cvector(-1.0f, -1.0f, 0.0f));
        v.push_back(Mth::make_cvector(1.0f, -1.0f, 0.0f));
        v.push_back(Mth::make_cvector(0.0f, 1.0f, 0.0f));
        
        std::vector<Mth::CVector<uint8_t, 4>> c;
        c.push_back(Mth::make_cvector<uint8_t>(255, 0, 0, 255));
        c.push_back(Mth::make_cvector<uint8_t>(0, 255, 0, 255));
        c.push_back(Mth::make_cvector<uint8_t>(0, 0, 255, 255));
        
        bind_buffer.set(0, (int)v.size(), GL_STATIC_DRAW, v, c);
    }
    
    {
        GLBindVertexArray bind_vertex_array(_vertex_array);
        bind_vertex_array.set(_buffer, {{0,0,true}, {1,1,true}});
    }
}

void Game::update() {
    // draw
    glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    {
        GLBindProgram bind_program(_program);
        GLBindVertexArray bind_vertex_array(_vertex_array);
        
        bind_program.set_uniform(_model_view_projection_location, Mth::Matrix<float, 4, 4>());
        
        bind_vertex_array.draw(GL_TRIANGLES);
    }
}

////////////////////////////////////////////////////////////////////////////////