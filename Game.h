//
//  Game.h
//
//  Created by Kristof Niederholtmeyer on 19.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __Game__
#define __Game__

////////////////////////////////////////////////////////////////////////////////

#include "GLClasses.h"
#include "Sprite.h"
#include "Character.h"
#include "GameComponents.h"
#include "PhysicsSystem.h"
#include "Renderer.h"
#include <random>

////////////////////////////////////////////////////////////////////////////////

class Game {
    std::string _resource_path;
    
    std::vector<Sprite*> _stand_l0;
    std::vector<Sprite*> _stand_r0;
    std::vector<Sprite*> _walk_l0;
    std::vector<Sprite*> _walk_r0;
    std::vector<Sprite*> _weapon_l0;
    std::vector<Sprite*> _weapon_r0;
    Sprite* _bullet0;
    
    Sprite* _world_f0;
    Sprite* _world_b0;
    
    int _control_pos_x, _control_pos_y;
    int _control_neg_x, _control_neg_y;
    int _control_fire;
    int _move_x;
    int _move_y;
    
    float _fire_timer;
    
    float _shake_x;
    float _shake_y;
    float _shake_x_feq;
    float _shake_y_feq;
    
    Mth::Matrix<float, 3, 3> _projection;
    
    bool handle_inpout(SDLSystem const& system);
    
    GameComponents _components;
    Entities _colliders;
    Entity _player_character;
    Entities _characters;
    Entities _bullets;
    PhysicsSystem _physics;
    Renderer _renderer;
    
    Entity _next_entity;
    
    void start_shake();
    
    std::mt19937 _random_engine;
    float random_float(float mean, float std);
    int random_int(int min, int max);
    
    SDLMixer _mixer;
    std::vector<SDLMixerChunk*> _shot;
    SDLMixerChunk* _logo_musik;
    
public:
    Game(SDLSystem const& system);
    ~Game();
    
    bool update(SDLSystem const& system, float dt);
};

////////////////////////////////////////////////////////////////////////////////

#endif /* defined(__Game__) */

////////////////////////////////////////////////////////////////////////////////
