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

Game::Game(SDLSystem const& system)
: _resource_path(system.resource_path()),
_control_pos_x(0), _control_neg_x(0), _control_pos_y(0), _control_neg_y(0), _move_x(0), _move_y(0) {
    _projection = Mth::make_matrix(1.0f/800.0f, 0.0f, -1.0f,
                                   0.0f, 1.0f/600.0f, -1.0f,
                                   0.0f, 0.0f, 1.0f);
    
    TextFile vert(_resource_path + "basic.vert");
    TextFile frag(_resource_path + "basic.frag");
    
    _program.load_shaders(vert.content(), frag.content(), {}, {});
    _model_view_location = _program.uniform_location("model_view");
    _texture0_location = _program.uniform_location("texture0");
    
    SDLImage image_loader(system);
    _sprites.push_back(new Sprite(image_loader, "head.png"));
    _sprites.push_back(new Sprite(image_loader, "body.png"));
    _sprites.push_back(new Sprite(image_loader, "gun.png"));
    
    _characters.push_back(new Character(_sprites[0], _sprites[1], _sprites[2]));
}

Game::~Game() {
    for (int i = 0; i < _sprites.size(); ++i) {
        delete _sprites[i];
    }
}

bool Game::update(SDLSystem const& system, float dt) {
    // draw
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    
    {
        GLBindProgram bind_program(_program);
        bind_program.set_uniform(_texture0_location, 0);
        
        for (int i = 0; i < _characters.size(); ++i) {
            bind_program.set_uniform(_model_view_location, _projection * _characters[i]->body_transformation());
            _characters[i]->body_sprite()->draw();
            bind_program.set_uniform(_model_view_location, _projection * _characters[i]->gun_transformation());
            _characters[i]->gun_sprite()->draw();
            bind_program.set_uniform(_model_view_location, _projection * _characters[i]->head_transformation());
            _characters[i]->head_sprite()->draw();
        }
        
    }
    
    Mth::CVector<float, 2> direction = Mth::normal(Mth::make_cvector<float>(_move_x, _move_y));
    _characters[0]->position += direction * 20.0f;
    
    for (int i = 0; i < _characters.size(); ++i) {
        _characters[i]->update(dt);
    }
    
    return handle_inpout(system);
}

bool Game::handle_inpout(SDLSystem const& system) {
    bool done = false;
    SDL_Event event;
    while (system.poll_event(event)) {
        if (event.type == SDL_QUIT) {
            done = true;
        }
        
        
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_w: case SDLK_UP:
                    _control_pos_y = 1;
                    break;
                case SDLK_a: case SDLK_LEFT:
                    _control_neg_x = 1;
                    break;
                case SDLK_s: case SDLK_DOWN:
                    _control_neg_y = 1;
                    break;
                case SDLK_d: case SDLK_RIGHT:
                    _control_pos_x = 1;
                    break;
                    
                default:
                    break;
            }
        }
        if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_w: case SDLK_UP:
                    _control_pos_y = 0;
                    break;
                case SDLK_a: case SDLK_LEFT:
                    _control_neg_x = 0;
                    break;
                case SDLK_s: case SDLK_DOWN:
                    _control_neg_y = 0;
                    break;
                case SDLK_d: case SDLK_RIGHT:
                    _control_pos_x = 0;
                    break;
                    
                default:
                    break;
            }
        }
    }
    
    _move_x = _control_pos_x - _control_neg_x;
    _move_y = _control_pos_y - _control_neg_y;
    
    if (_move_x != 0) {
        _characters[0]->look_x = _move_x;
    }
    
    if (_move_x != 0 || _move_y != 0) {
        _characters[0]->set_animation(1);
    } else {
        _characters[0]->set_animation(0);
    }
    
    return done;
}

////////////////////////////////////////////////////////////////////////////////