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

typedef enum : int {
    GS_Title,
    GS_Game
} GameState;

////////////////////////////////////////////////////////////////////////////////

class Game {
    std::string _resource_path;
    
    std::vector<Sprite*> _stand_l0;
    std::vector<Sprite*> _stand_r0;
    std::vector<Sprite*> _walk_l0;
    std::vector<Sprite*> _walk_r0;
    std::vector<Sprite*> _weapon_l0;
    std::vector<Sprite*> _weapon_r0;
    
    std::vector<Sprite*> _w1_stand_l0;
    std::vector<Sprite*> _w1_stand_r0;
    std::vector<Sprite*> _w1_walk_l0;
    std::vector<Sprite*> _w1_walk_r0;
    std::vector<Sprite*> _w1_weapon_l0;
    std::vector<Sprite*> _w1_weapon_r0;
    
    std::vector<Sprite*> _explosion;
    
    Sprite* _granade;
    
    Sprite* _bullet0;
    
    Sprite* _world_f0;
    Sprite* _world_b0;
    
    Sprite* _title;
    
    int _control_pos_x, _control_pos_y;
    int _control_neg_x, _control_neg_y;
    int _control_fire;
    int _control_granade;
    int _move_x;
    int _move_y;
    
    float _footstep_timer;
    
    float _shake_x;
    float _shake_y;
    float _shake_x_feq;
    float _shake_y_feq;
    
    Mth::Matrix<float, 3, 3> _projection;
    float _camera_x_f;
    float _camera_x_b;
    
    bool handle_inpout(SDLSystem const& system);
    
    GameComponents _components;
    Entities _colliders;
    Entity _player_character;
    Entities _characters;
    Entities _bullets;
    Entities _granades;
    Entities _smokes;
    PhysicsSystem _physics;
    Renderer _renderer;
    
    Entity _next_entity;
    
    void start_shake(float strength);
    
    std::mt19937 _random_engine;
    float random_float(float mean, float std);
    int random_int(int min, int max);
    
    SDLMixer _mixer;
    std::vector<SDLMixerChunk*> _shot;
    std::vector<SDLMixerChunk*> _footstep;
    SDLMixerChunk* _logo_musik;
    SDLMixerChunk* _explosion_sound;
    SDLMixerChunk* _hit_soumd;
    
    void ai(Character& monster, Collider& monster_collider,
            Character& player, Collider& player_collider);
    
    GameState _game_state;
    void reset_game();
    void title_state(float dt);
    void in_game_state(float dt);
    void next_state();
    
public:
    Game(SDLSystem const& system);
    ~Game();
    
    bool update(SDLSystem const& system, float dt);
};

////////////////////////////////////////////////////////////////////////////////

#endif /* defined(__Game__) */

////////////////////////////////////////////////////////////////////////////////
