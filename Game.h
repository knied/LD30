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
    GS_Stage,
    GS_Reach,
    GS_Win,
    GS_Loose
} GameState;

////////////////////////////////////////////////////////////////////////////////

class Game {
    int _title_counter = 0;
    int _title_counter_max = 4;
    int _stage_counter = 0;
    int _stage_counter_max = 5;
    bool _continue = false;
    bool _fail = false;
    
    void update_menu(float dt);
    void update_game(float dt);
    
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
    
    std::vector<Sprite*> _boss_stand_l0;
    std::vector<Sprite*> _boss_stand_r0;
    std::vector<Sprite*> _boss_walk_l0;
    std::vector<Sprite*> _boss_walk_r0;
    
    std::vector<Sprite*> _stage_banner;
    
    std::vector<Sprite*> _explosion;
    
    std::vector<Sprite*> _hearts;
    
    std::vector<Sprite*> _prop_sprites;
    
    Sprite* _loose_screen;
    
    Sprite* _granade;
    
    Sprite* _bullet0;
    
    Sprite* _world_f0;
    Sprite* _world_b0;
    
    Sprite* _arrow_big;
    Sprite* _arrow_small;
    
    Sprite* _pickup_image;
    
    std::vector<Sprite*> _title;
    
    bool _did_move = false;
    int _control_pos_x, _control_pos_y;
    int _control_neg_x, _control_neg_y;
    int _control_fire;
    int _control_granade;
    int _move_x;
    int _move_y;
    
    float _footstep_timer;
    float _arrow_timer = 0.0f;
    
    float _shake_x;
    float _shake_y;
    float _shake_x_feq;
    float _shake_y_feq;
    
    Mth::Matrix<float, 3, 3> _projection;
    float _camera_x_f;
    float _camera_x_b;
    float _camera_offset = 0.0f;
    float _camera_offset_target = 0.0f;
    
    float _reach_x = 2048.0f;
    //bool _show_reach = true;
    
    //int _world_f_pos0 = -10;
    //int _world_f_pos1 = -11;
    std::vector<int> _prop_cache;
    
    bool handle_inpout(SDLSystem const& system);
    
    GameComponents _components;
    Entities _colliders;
    Entity _player_character;
    Entities _characters;
    Entities _bullets;
    Entities _granades;
    Entities _smokes;
    Entities _props;
    Entities _pickups;
    Entities _bosses;
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
    SDLMixerChunk* _fight_musik;
    SDLMixerChunk* _explosion_sound;
    SDLMixerChunk* _hit_soumd;
    SDLMixerChunk* _banner_sound;
    SDLMixerChunk* _pickup_sound;
    SDLMixerChunk* _loose_sound;
    SDLMixerChunk* _win_sound;
    SDLMixerChunk* _kill_sound;
    
    void ai(Character& monster, Collider& monster_collider,
            Character& player, Collider& player_collider);
    void boss_ai(Boss& monster, Collider& monster_collider,
                 Character& player, Collider& player_collider);
    
    GameState _game_state = GS_Title;
    //int _stage = -1;
    //int _title_screen = 0;
    //float _stage_timer = 0.0f;
    //bool _go_to_next_stage = false;
    void reset_game();
    void init_player();
    void prepare_next_stage();
    void init_stage(int stage);
    void title_state(float dt);
    void update_banner(float dt);
    int _show_banner = -1;
    float _banner_timer = 0.0f;
    int _banner_phase = 0;
    void in_game_state(float dt);
    void next_state();
    void show_banner(int banner);
    
    //int _player_state = 0;
    
    int music_channel = -1;
    
public:
    Game(SDLSystem const& system);
    ~Game();
    
    void load(SDLSystem const& system);
    
    bool update(SDLSystem const& system, float dt);
};

////////////////////////////////////////////////////////////////////////////////

#endif /* defined(__Game__) */

////////////////////////////////////////////////////////////////////////////////
