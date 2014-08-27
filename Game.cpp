//
//  Game.cpp
//
//  Created by Kristof Niederholtmeyer on 19.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "Game.h"
#include <iostream>
//#include "gl3w.h"
#include "TextFile.h"
#include "Transformation.h"

////////////////////////////////////////////////////////////////////////////////

Game::Game(SDLSystem const& system)
: _resource_path(system.resource_path()),
_control_pos_x(0), _control_neg_x(0), _control_pos_y(0), _control_neg_y(0), _control_fire(0), _move_x(0), _move_y(0), _renderer(system),
_next_entity(1), _shake_x(0.0f), _shake_y(0.0f), _shake_x_feq(0.0f), _shake_y_feq(0.0f), _mixer(system), _footstep_timer(0.0f), _game_state(GS_Title) {
    if (!_mixer.valid()) {
        std::cout << "error" << std::endl;
    }
    
    _projection = Mth::make_matrix(1.0f/512.0f, 0.0f, -1.0f,
                                   0.0f, 1.0f/384.0f, -1.0f,
                                   0.0f, 0.0f, 1.0f);
    
    _logo_musik = new SDLMixerChunk(_mixer, "00_LD30_OST_Intro_v2nn.ogg");
    music_channel = _mixer.play(*_logo_musik, 0, 1);
    
    SDLImage image_loader(system);
    _title.push_back(new Sprite(image_loader, "Title_0.png"));
    
    Mth::Matrix<float, 3, 3> trafo = Mth::make_matrix(1.0f, 0.0f, 512.0f,
                                                      0.0f, 1.0f, 384.0f,
                                                      0.0f, 0.0f, 1.0f);
    _renderer.add(_title[0], _projection * trafo, 0, 0.0f);
    _renderer.flush();
    
    reset_game();
}

void Game::load(SDLSystem const& system) {
    SDLImage image_loader(system);
    _stand_l0.push_back(new Sprite(image_loader, "stand_l_1.png"));
    _stand_l0.push_back(new Sprite(image_loader, "stand_l_2.png"));
    _stand_r0.push_back(new Sprite(image_loader, "stand_r_1.png"));
    _stand_r0.push_back(new Sprite(image_loader, "stand_r_2.png"));
    _walk_l0.push_back(new Sprite(image_loader, "walk_l_1.png"));
    _walk_l0.push_back(new Sprite(image_loader, "walk_l_2.png"));
    _walk_l0.push_back(new Sprite(image_loader, "walk_l_3.png"));
    _walk_l0.push_back(new Sprite(image_loader, "walk_l_4.png"));
    _walk_r0.push_back(new Sprite(image_loader, "walk_r_1.png"));
    _walk_r0.push_back(new Sprite(image_loader, "walk_r_2.png"));
    _walk_r0.push_back(new Sprite(image_loader, "walk_r_3.png"));
    _walk_r0.push_back(new Sprite(image_loader, "walk_r_4.png"));
    _weapon_l0.push_back(new Sprite(image_loader, "weapon_l_1.png"));
    _weapon_l0.push_back(new Sprite(image_loader, "weapon_l_2.png"));
    _weapon_r0.push_back(new Sprite(image_loader, "weapon_r_1.png"));
    _weapon_r0.push_back(new Sprite(image_loader, "weapon_r_2.png"));
    _w1_stand_l0.push_back(new Sprite(image_loader, "w_1_stand_l_0.png"));
    _w1_stand_l0.push_back(new Sprite(image_loader, "w_1_stand_l_1.png"));
    _w1_stand_r0.push_back(new Sprite(image_loader, "w_1_stand_r_0.png"));
    _w1_stand_r0.push_back(new Sprite(image_loader, "w_1_stand_r_1.png"));
    _w1_walk_l0.push_back(new Sprite(image_loader, "w_1_walk_l_0.png"));
    _w1_walk_l0.push_back(new Sprite(image_loader, "w_1_walk_l_1.png"));
    _w1_walk_l0.push_back(new Sprite(image_loader, "w_1_walk_l_2.png"));
    _w1_walk_l0.push_back(new Sprite(image_loader, "w_1_walk_l_3.png"));
    _w1_walk_r0.push_back(new Sprite(image_loader, "w_1_walk_r_0.png"));
    _w1_walk_r0.push_back(new Sprite(image_loader, "w_1_walk_r_1.png"));
    _w1_walk_r0.push_back(new Sprite(image_loader, "w_1_walk_r_2.png"));
    _w1_walk_r0.push_back(new Sprite(image_loader, "w_1_walk_r_3.png"));
    _w1_weapon_l0.push_back(new Sprite(image_loader, "w_1_weapon_l_0.png"));
    _w1_weapon_l0.push_back(new Sprite(image_loader, "w_1_weapon_l_1.png"));
    _w1_weapon_r0.push_back(new Sprite(image_loader, "w_1_weapon_r_0.png"));
    _w1_weapon_r0.push_back(new Sprite(image_loader, "w_1_weapon_r_1.png"));
    _w1_weapon_l1.push_back(new Sprite(image_loader, "w_1_grenade_l_0.png"));
    _w1_weapon_l1.push_back(new Sprite(image_loader, "w_1_grenade_l_1.png"));
    _w1_weapon_r1.push_back(new Sprite(image_loader, "w_1_grenade_r_0.png"));
    _w1_weapon_r1.push_back(new Sprite(image_loader, "w_1_grenade_r_1.png"));
    _bullet0 = new Sprite(image_loader, "Bullet.png");
    _world_f0 = new Sprite(image_loader, "world_1_1.png");
    _world_b0 = new Sprite(image_loader, "world_1_2.png");
    _explosion.push_back(new Sprite(image_loader, "Explo_0.png"));
    _explosion.push_back(new Sprite(image_loader, "Explo_1.png"));
    _explosion.push_back(new Sprite(image_loader, "Explo_2.png"));
    _explosion.push_back(new Sprite(image_loader, "Explo_3.png"));
    _explosion.push_back(new Sprite(image_loader, "Explo_4.png"));
    _granade = new Sprite(image_loader, "granate.png");
    _space_to_start = new Sprite(image_loader, "Title_1.png");
    _title.push_back(new Sprite(image_loader, "Title_2.png"));
    _title.push_back(new Sprite(image_loader, "Title_3.png"));
    _title.push_back(new Sprite(image_loader, "Title_4.png"));
    _title.push_back(new Sprite(image_loader, "Title_5.png"));
    _stage_banner.push_back(new Sprite(image_loader, "Banner_Cleared.png"));
    _stage_banner.push_back(new Sprite(image_loader, "Banner_Stage_1.png"));
    _stage_banner.push_back(new Sprite(image_loader, "Banner_Stage_2.png"));
    _stage_banner.push_back(new Sprite(image_loader, "Banner_Stage_3.png"));
    _stage_banner.push_back(new Sprite(image_loader, "Banner_Stage_4.png"));
    _stage_banner.push_back(new Sprite(image_loader, "Banner_Stage_5.png"));
    _stage_banner.push_back(new Sprite(image_loader, "Banner_Stage_Final.png"));
    _hearts.push_back(new Sprite(image_loader, "heart_0.png"));
    _hearts.push_back(new Sprite(image_loader, "heart_1.png"));
    _hearts.push_back(new Sprite(image_loader, "heart_2.png"));
    _hearts.push_back(new Sprite(image_loader, "heart_3.png"));
    _hearts.push_back(new Sprite(image_loader, "heart_4.png"));
    _prop_sprites.push_back(new Sprite(image_loader, "barrier_0.png"));
    _prop_sprites.push_back(new Sprite(image_loader, "barrier_1.png"));
    _prop_sprites.push_back(new Sprite(image_loader, "barrier_2.png"));
    _prop_sprites.push_back(new Sprite(image_loader, "barrier_3.png"));
    _prop_sprites.push_back(new Sprite(image_loader, "barrier_4.png"));
    _prop_sprites.push_back(new Sprite(image_loader, "barrier_5.png"));
    _prop_sprites.push_back(new Sprite(image_loader, "barrier_6.png"));
    _prop_sprites.push_back(new Sprite(image_loader, "barrier_7.png"));
    _prop_sprites.push_back(new Sprite(image_loader, "barrier_8.png"));
    _arrow_big = new Sprite(image_loader, "arrow_big.png");
    _arrow_small = new Sprite(image_loader, "arrow_small.png");
    _pickup_image = new Sprite(image_loader, "powerup.png");
    _win_screen = new Sprite(image_loader, "screen_win.png");
    _loose_screen = new Sprite(image_loader, "screen_lose.png");
    _boss_stand_l0.push_back(new Sprite(image_loader, "endboss_stand_l_0.png"));
    _boss_stand_l0.push_back(new Sprite(image_loader, "endboss_stand_l_1.png"));
    _boss_stand_r0.push_back(new Sprite(image_loader, "endboss_stand_r_0.png"));
    _boss_stand_r0.push_back(new Sprite(image_loader, "endboss_stand_r_1.png"));
    _boss_walk_l0.push_back(new Sprite(image_loader, "endboss_walk_l_0.png"));
    _boss_walk_l0.push_back(new Sprite(image_loader, "endboss_walk_l_1.png"));
    _boss_walk_l0.push_back(new Sprite(image_loader, "endboss_walk_l_2.png"));
    _boss_walk_l0.push_back(new Sprite(image_loader, "endboss_walk_l_3.png"));
    _boss_walk_r0.push_back(new Sprite(image_loader, "endboss_walk_r_0.png"));
    _boss_walk_r0.push_back(new Sprite(image_loader, "endboss_walk_r_1.png"));
    _boss_walk_r0.push_back(new Sprite(image_loader, "endboss_walk_r_2.png"));
    _boss_walk_r0.push_back(new Sprite(image_loader, "endboss_walk_r_3.png"));
    _controls_image = new Sprite(image_loader, "control.png");
    _boss_jump.push_back(new Sprite(image_loader, "endboss_jump_0.png"));
    _boss_jump.push_back(new Sprite(image_loader, "endboss_jump_1.png"));
    _boss_jump.push_back(new Sprite(image_loader, "endboss_jump_2.png"));
    _boss_jump.push_back(new Sprite(image_loader, "endboss_jump_3.png"));
    _boss_jump.push_back(new Sprite(image_loader, "endboss_jump_4.png"));
    
    _shot.push_back(new SDLMixerChunk(_mixer, "Shot 01.ogg"));
    _shot.push_back(new SDLMixerChunk(_mixer, "Shot 02.ogg"));
    _shot[1]->set_volume(32);
    
    _footstep.push_back(new SDLMixerChunk(_mixer, "FootStep01.ogg"));
    _footstep.push_back(new SDLMixerChunk(_mixer, "FootStep02.ogg"));
    
    _fight_musik = new SDLMixerChunk(_mixer, "01_LD30_OST_Shit_Ahead.ogg");
    _explosion_sound = new SDLMixerChunk(_mixer, "Grenade Explosion01.ogg");
    _hit_soumd = new SDLMixerChunk(_mixer, "BodyHit LD30 v0.ogg");
    _banner_sound = new SDLMixerChunk(_mixer, "STAGESWOOSH01.ogg");
    _pickup_sound = new SDLMixerChunk(_mixer, "PickUp01.ogg");
    _loose_sound = new SDLMixerChunk(_mixer, "DeadFX01.ogg");
    _win_sound = new SDLMixerChunk(_mixer, "Final Stage Logo.ogg");
    _kill_sound = new SDLMixerChunk(_mixer, "Dead01pitch.ogg");
    _kill_sound->set_volume(64);
    
    _continue = false;
}

void Game::reset_game() {
    _colliders.clear();
    _characters.clear();
    _bullets.clear();
    _granades.clear();
    _smokes.clear();
    _props.clear();
    _pickups.clear();
    _bosses.clear();
    
    _next_entity = 1;
    //_player_state = 0;
    
    _prop_cache.clear();
    _prop_cache.push_back(0);
    
    
    
    //_reach_x = 2048.0f;
    //_show_reach = true;
    
    //_game_state = GS_Title;
    //_stage_counter = 0;
    //_title_counter = 0;
    
    _components.clear_all();
}

void Game::init_player() {
    {
        _player_character = _next_entity++;
        Collider& collider = _components.add<ColliderComponent>(_player_character);
        collider.radius = 50.0f;
        collider.position = Mth::make_cvector(0.0f, 300.0f);
        collider.group = CG_P;
        std::shared_ptr<Character>& player = _components.add<CharacterComponent>(_player_character);
        player = std::shared_ptr<Character>(new Character(_stand_l0, _stand_r0,
                                                          _walk_l0, _walk_r0,
                                                          _weapon_l0, _weapon_r0));
        player->health = 10;
        _characters.insert(_player_character);
        _colliders.insert(_player_character);
    }
}

void Game::prepare_next_stage() {
    // store player state
    Collider player_collider = _components.get<ColliderComponent>(_player_character);
    std::shared_ptr<Character> player_character = _components.get<CharacterComponent>(_player_character);
    
    // store props
    std::vector<Collider> prop_colliders;
    std::vector<std::shared_ptr<Prop>> props;
    for (Entity prop : _props) {
        prop_colliders.push_back(_components.get<ColliderComponent>(prop));
        props.push_back(_components.get<PropComponent>(prop));
    }
    
    // store bullets
    std::vector<Collider> bullet_colliders;
    std::vector<std::shared_ptr<Bullet>> bullets;
    for (Entity bullet : _bullets) {
        bullet_colliders.push_back(_components.get<ColliderComponent>(bullet));
        bullets.push_back(_components.get<BulletComponent>(bullet));
    }
    
    // store granades
    std::vector<Collider> granade_colliders;
    std::vector<std::shared_ptr<Granade>> granades;
    for (Entity granade : _granades) {
        granade_colliders.push_back(_components.get<ColliderComponent>(granade));
        granades.push_back(_components.get<GranadeComponent>(granade));
    }
    
    // store pickups
    std::vector<std::shared_ptr<Pickup>> pickups;
    for (Entity pickup : _pickups) {
        pickups.push_back(_components.get<PickupComponent>(pickup));
    }
    
    std::vector<int> prop_cache = _prop_cache;
    //bool show_reach = _show_reach;
    
    reset_game();
    //_show_reach = show_reach;
    
    _prop_cache = prop_cache;
    
    // restore player
    {
        _player_character = _next_entity++;
        _components.add<ColliderComponent>(_player_character) = player_collider;
        _components.add<CharacterComponent>(_player_character) = player_character;
        _characters.insert(_player_character);
        _colliders.insert(_player_character);
    }
    
    // restore pickups
    for (int i = 0; i < pickups.size(); ++i) {
        Entity pickup = _next_entity++;
        _components.add<PickupComponent>(pickup) = pickups[i];
        _pickups.insert(pickup);
    }
    
    // restore props
    for (int i = 0; i < props.size(); ++i) {
        Entity prop = _next_entity++;
        _components.add<ColliderComponent>(prop) = prop_colliders[i];
        _components.add<PropComponent>(prop) = props[i];
        _props.insert(prop);
        _colliders.insert(prop);
    }
    
    // restore bullets
    for (int i = 0; i < bullets.size(); ++i) {
        Entity bullet = _next_entity++;
        _components.add<ColliderComponent>(bullet) = bullet_colliders[i];
        _components.add<BulletComponent>(bullet) = bullets[i];
        _bullets.insert(bullet);
        _colliders.insert(bullet);
    }
    
    // restore granades
    for (int i = 0; i < granades.size(); ++i) {
        Entity granade = _next_entity++;
        _components.add<ColliderComponent>(granade) = granade_colliders[i];
        _components.add<GranadeComponent>(granade) = granades[i];
        _granades.insert(granade);
        _colliders.insert(granade);
    }
}

void Game::init_stage(int stage) {
    prepare_next_stage();
    
    std::cout << "init stage: " << stage << std::endl;
    Collider& player_collider = _components.get<ColliderComponent>(_player_character);
    //std::shared_ptr<Character>& player_character = _components.get<CharacterComponent>(_player_character);
    std::cout << "player x: " << player_collider.position(0) << std::endl;
    if (stage == 0) {
        //show_banner(1);
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f, 300.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l0, _w1_weapon_r0));
            //character->health = 100;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        /*{
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 64.0f;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f, 300.0f);
            collider.group = CG_E;
            std::shared_ptr<Boss>& boss = _components.add<BossComponent>(entity);
            boss = std::shared_ptr<Boss>(new Boss(_boss_stand_l0, _boss_stand_r0,
                                                  _boss_walk_l0, _boss_walk_r0));
            boss->health = 20;
            //character->fire_timer_reset = 0.8f;
            _bosses.insert(entity);
            _colliders.insert(entity);
        }*/
    } else if (stage == 1) {
        //show_banner(2);
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f, 240.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l0, _w1_weapon_r0));
            //character->health = 100;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f, 360.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l0, _w1_weapon_r0));
            //character->health = 100;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        /*for (int i = 0; i < 10; ++i) {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f + 200.0f * i << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f + 200.0f * i, 300.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l0, _w1_weapon_r0));
            character->weapon = i % 2;
            //character->health = 100;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }*/
    } else if (stage == 2) {
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f, 240.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l0, _w1_weapon_r0));
            //character->health = 100;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f, 360.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l0, _w1_weapon_r0));
            //character->health = 100;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f + 200.0f, 200.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l1, _w1_weapon_r1));
            //character->health = 100;
            character->weapon = 1;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f + 200.0f, 400.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l1, _w1_weapon_r1));
            //character->health = 100;
            character->weapon = 1;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
    } else if (stage == 3) {
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f, 240.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l0, _w1_weapon_r0));
            //character->health = 100;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f, 360.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l0, _w1_weapon_r0));
            //character->health = 100;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f + 200.0f, 200.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l1, _w1_weapon_r1));
            //character->health = 100;
            character->weapon = 1;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f + 200.0f, 400.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l1, _w1_weapon_r1));
            //character->health = 100;
            character->weapon = 1;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) - 300.0f, 240.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l0, _w1_weapon_r0));
            //character->health = 100;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) - 300.0f, 360.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l0, _w1_weapon_r0));
            //character->health = 100;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
    } else if (stage == 4) {
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f, 240.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l0, _w1_weapon_r0));
            //character->health = 100;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f, 360.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l0, _w1_weapon_r0));
            //character->health = 100;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f + 200.0f, 200.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l1, _w1_weapon_r1));
            //character->health = 100;
            character->weapon = 1;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f + 200.0f, 400.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l1, _w1_weapon_r1));
            //character->health = 100;
            character->weapon = 1;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) - 300.0f, 240.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l0, _w1_weapon_r0));
            //character->health = 100;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) - 300.0f, 360.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l0, _w1_weapon_r0));
            //character->health = 100;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) - 600.0f, 240.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l1, _w1_weapon_r1));
            //character->health = 100;
            character->weapon = 1;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
        
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 50.0f;
            std::cout << "spawn x: " << player_collider.position(0) + 2048.0f << std::endl;
            collider.position = Mth::make_cvector(player_collider.position(0) - 600.0f, 360.0f);
            collider.group = CG_E;
            std::shared_ptr<Character>& character = _components.add<CharacterComponent>(entity);
            character = std::shared_ptr<Character>(new Character(_w1_stand_l0, _w1_stand_r0,
                                                                 _w1_walk_l0, _w1_walk_r0,
                                                                 _w1_weapon_l1, _w1_weapon_r1));
            //character->health = 100;
            character->weapon = 1;
            character->fire_timer_reset = 0.8f;
            _characters.insert(entity);
            _colliders.insert(entity);
        }
    } else if (stage == 5) {
        {
            Entity entity = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(entity);
            collider.radius = 64.0f;
            collider.position = Mth::make_cvector(player_collider.position(0) + 2048.0f, 300.0f);
            collider.group = CG_E;
            std::shared_ptr<Boss>& boss = _components.add<BossComponent>(entity);
            boss = std::shared_ptr<Boss>(new Boss(_boss_stand_l0, _boss_stand_r0,
                                                  _boss_walk_l0, _boss_walk_r0));
            boss->health = 20;
            //character->fire_timer_reset = 0.8f;
            _bosses.insert(entity);
            _colliders.insert(entity);
        }
    }
}

Game::~Game() {
    
}

void Game::update_menu(float dt) {
    Mth::Matrix<float, 3, 3> trafo = Mth::make_matrix(1.0f, 0.0f, 512.0f,
                                                      0.0f, 1.0f, 384.0f,
                                                      0.0f, 0.0f, 1.0f);
    if (_game_state == GS_Title) {
        _renderer.add(_title[_title_counter], _projection * trafo, 0, 0.0f);
        if (_title_counter == 0) {
            trafo = transformation(790, 170);
            _renderer.add(_space_to_start, _projection * trafo, -1, 0.0f);
        }
    } else if (_game_state == GS_Loose) {
        _renderer.add(_loose_screen, _projection * trafo, 0, 0.0f);
    } else if (_game_state == GS_Win) {
        _renderer.add(_win_screen, _projection * trafo, 0, 0.0f);
    }
}

void Game::update_game(float dt) {
    if (_game_state == GS_Reach && _stage_counter == 0) {
        Mth::Matrix<float, 3, 3> trafo = Mth::make_matrix(1.0f, 0.0f, 750.0f,
                                                          0.0f, 1.0f, 500.0f,
                                                          0.0f, 0.0f, 1.0f);
        _renderer.add(_controls_image, _projection * trafo, -10, 0.0f);
    }
    
    _arrow_timer += dt;
    if (_arrow_timer > 2.0f * Mth::pi) {
        _arrow_timer -= 2.0f * Mth::pi;
    }
    
    if (_move_x != 0 || _move_y != 0) {
        _footstep_timer += dt;
        if (_footstep_timer > 0.25f) {
            _footstep_timer = 0.0f;
            _mixer.play(*_footstep[random_int(0, (int)_footstep.size() - 1)], 0, 3);
        }
    }
    
    std::shared_ptr<Character> player = _components.get<CharacterComponent>(_player_character);
    Collider& player_collider = _components.get<ColliderComponent>(_player_character);
    
    if (_move_x != 0) {
        player->look_x = _move_x;
    }
    
    if (_move_x != 0 || _move_y != 0) {
        player->set_animation(1);
        if (!_did_move) {
            _footstep_timer = 0.4f;
        }
    } else {
        player->set_animation(0);
    }
    
    int i = 0;
    while (i < player->health) {
        Mth::Matrix<float, 3, 3> heart_trafo = Mth::make_matrix(1.0f, 0.0f, 32.0f + i * 32.0f,
                                                                0.0f, 1.0f, 740.0f,
                                                                0.0f, 0.0f, 1.0f);
        _renderer.add(_hearts[i % _hearts.size()], _projection * heart_trafo, -10, 0.0f);
        i++;
    }
    
    if (_game_state == GS_Reach) {
        Mth::Matrix<float, 3, 3> trafo = Mth::make_matrix(1.0f, 0.0f, 900.0f + 30.0f * Mth::sin(8.0f * _arrow_timer),
                                                          0.0f, 1.0f, 100.0f,
                                                          0.0f, 0.0f, 1.0f);
        _renderer.add(_arrow_big, _projection * trafo, -10, 0.0f);
    }
    
    _camera_offset_target = player->look_x * 150.0f;
    _camera_offset += 3.0f * (_camera_offset_target - _camera_offset) * dt;
    _camera_x_f = player_collider.position(0) - 512.0 + _camera_offset;
    _camera_x_b = 0.5f * _camera_x_f;
    
    Mth::Matrix<float, 3, 3> shake = Mth::make_matrix(1.0f, 0.0f, _shake_x * Mth::sin(_shake_x_feq),
                                                      0.0f, 1.0f, _shake_y * Mth::sin(_shake_y_feq),
                                                      0.0f, 0.0f, 1.0f);
    Mth::Matrix<float, 3, 3> camera = shake;
    camera(0, 2) -= _camera_x_f;
    Mth::Matrix<float, 3, 3> camera_back = shake;
    camera_back(0, 2) *= 0.2f;
    camera_back(1, 2) *= 0.2f;
    camera_back(0, 2) -= _camera_x_b;
    
    Mth::CVector<float, 2> direction = Mth::normal(Mth::make_cvector<float>(_move_x, _move_y));
    player_collider.velocity = direction * 800.0f;
    
    if (_control_fire == 1 && player->fire_timer <= 0.0f) {
        player->fire_timer = player->fire_timer_reset;
        Entity bullet = _next_entity++;
        Collider& collider = _components.add<ColliderComponent>(bullet);
        collider.radius = 8.0f;
        collider.position = player_collider.position + player->fire_position();
        collider.group = CG_PB;
        _colliders.insert(bullet);
        _bullets.insert(bullet);
        
        std::shared_ptr<Bullet>& b = _components.add<BulletComponent>(bullet);
        b = std::shared_ptr<Bullet>(new Bullet(_bullet0));
        //b->look_x = player->look_x;
        b->velocity = Mth::make_cvector(1.0f, 0.0f) * Mth::dot(player_collider.velocity, Mth::make_cvector(1.0f, 0.0f)) + Mth::make_cvector(player->look_x * 2000.0f, 0.0f);
        
        _shot[0]->set_volume(random_int(32, 128));
        _mixer.play(*_shot[0], 0, 4);
    }
    
    if (_control_granade == 1 && player->granade_timer <= 0.0f) {
        player->granade_timer = player->granade_timer_reset;
        Entity granade = _next_entity++;
        Collider& collider = _components.add<ColliderComponent>(granade);
        collider.radius = 8.0f;
        collider.position = player_collider.position + player->fire_position();
        collider.group = CG_PG;
        _colliders.insert(granade);
        _granades.insert(granade);
        
        std::shared_ptr<Granade>& b = _components.add<GranadeComponent>(granade);
        b = std::shared_ptr<Granade>(new Granade(_granade));
        b->velocity = Mth::make_cvector(1.0f, 0.0f) * Mth::dot(player_collider.velocity, Mth::make_cvector(1.0f, 0.0f)) + Mth::make_cvector(player->look_x * 400.0f, 0.0f);
        
        //_shot[0]->set_volume(random_int(32, 128));
        //_mixer.play(*_shot[0], 0, -1);
    }
    
    int world_f_pos0 = _camera_x_f / 2048.0f;
    int world_f_pos1 = world_f_pos0 + 1;
    
    if (_camera_x_f < 0.0f) {
        world_f_pos0--;
        world_f_pos1--;
    }
    
    if (world_f_pos0 < _prop_cache.front()) {
        _prop_cache.insert(_prop_cache.begin(), world_f_pos0);
        if (_prop_cache.size() > 8) {
            _prop_cache.erase(_prop_cache.end()-1);
        }
        for (int i = 0; i < 3; ++i) {
            Entity prop = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(prop);
            collider.radius = 64.0f;
            collider.position = Mth::make_cvector<float>(world_f_pos0 * 2048.0f - 800.0f + i * 400.0f, random_int(100, 600));
            //std::cout << "spawn: " << collider.position(0) << " " << collider.position(1) << std::endl;
            collider.group = CG_PR;
            std::shared_ptr<Prop>& b = _components.add<PropComponent>(prop);
            b = std::shared_ptr<Prop>(new Prop(_prop_sprites[random_int(0, (int)_prop_sprites.size()-1)]));
            b->level_bucket = world_f_pos0;
            _colliders.insert(prop);
            _props.insert(prop);
        }
        //std::cout << "props: " << _props.size() << std::endl;
    }
    if (world_f_pos1 > _prop_cache.back()) {
        _prop_cache.insert(_prop_cache.end(), world_f_pos1);
        if (_prop_cache.size() > 8) {
            _prop_cache.erase(_prop_cache.begin());
        }
        for (int i = 0; i < 3; ++i) {
            Entity prop = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(prop);
            collider.radius = 64.0f;
            collider.position = Mth::make_cvector<float>(world_f_pos1 * 2048.0f - 800.0f + i * 400.0f, random_int(100, 600));
            //std::cout << "spawn: " << collider.position(0) << " " << collider.position(1) << std::endl;
            collider.group = CG_PR;
            std::shared_ptr<Prop>& b = _components.add<PropComponent>(prop);
            b = std::shared_ptr<Prop>(new Prop(_prop_sprites[random_int(0, (int)_prop_sprites.size()-1)]));
            b->level_bucket = world_f_pos1;
            _colliders.insert(prop);
            _props.insert(prop);
        }
        //std::cout << "props: " << _props.size() << std::endl;
    }
    
    //_world_f_pos0 = world_f_pos0;
    //_world_f_pos1 = world_f_pos1;
    
    Entities despawn_props;
    for (Entity entity : _props) {
        std::shared_ptr<Prop> prop = _components.get<PropComponent>(entity);
        Collider& collider = _components.get<ColliderComponent>(entity);
        Mth::Matrix<float, 3, 3> translation = transformation(collider.position(0), collider.position(1));
        _renderer.add(prop->sprite(), _projection * camera * translation * prop->transformation(), collider.position(1), 0.0f);
        
        for (Entity sentity : _smokes ) {
            std::shared_ptr<Smoke> smoke = _components.get<SmokeComponent>(sentity);
            if (smoke->deal_damage) {
                Mth::CVector<float, 2> distance = collider.position - smoke->position;
                if (Mth::length(distance) < smoke->damage_radius) {
                    collider.velocity += Mth::normal(distance) * 1000.0f;
                }
            }
        }
        
        bool remove = true;
        for (int c : _prop_cache) {
            if (c == prop->level_bucket) {
                remove = false;
                break;
            }
        }
        if (remove) {
            despawn_props.insert(entity);
        }
    }
    for (Entity entity : despawn_props) {
        _props.erase(_props.find(entity));
        _colliders.erase(_colliders.find(entity));
        _components.remove(entity);
    }
    
    Entities despawn_pickups;
    for (Entity entity : _pickups) {
        std::shared_ptr<Pickup> pickup = _components.get<PickupComponent>(entity);
        _renderer.add(pickup->sprite(), _projection * camera * pickup->transformation(), pickup->position(1), 0.0f);
        
        if (Mth::length(pickup->position - player_collider.position) < 64.0f) {
            player->health += 1;
            despawn_pickups.insert(entity);
            _mixer.play(*_pickup_sound, 0, -1);
        }
    }
    for (Entity entity : despawn_pickups) {
        _pickups.erase(_pickups.find(entity));
        _components.remove(entity);
    }
    
    int world_b_pos0 = _camera_x_b / 2048.0f;
    int world_b_pos1 = world_b_pos0 + 1;
    if (_camera_x_b < 0.0f) {
        world_b_pos0--;
        world_b_pos1--;
    }
    
    Mth::Matrix<float, 3, 3> world_trafo_f = Mth::make_matrix(1.0f, 0.0f, world_f_pos0 * 2048.0f,
                                                              0.0f, 1.0f, 380.0f,
                                                              0.0f, 0.0f, 1.0f);
    _renderer.add(_world_f0, _projection * camera * world_trafo_f, 3000, 0.0f);
    world_trafo_f = Mth::make_matrix(1.0f, 0.0f, world_f_pos1 * 2048.0f,
                                     0.0f, 1.0f, 380.0f,
                                     0.0f, 0.0f, 1.0f);
    _renderer.add(_world_f0, _projection * camera * world_trafo_f, 3000, 0.0f);
    Mth::Matrix<float, 3, 3> world_trafo_b = Mth::make_matrix(1.0f, 0.0f, world_b_pos0 * 2048.0f,
                                                              0.0f, 1.0f, 630.0f,
                                                              0.0f, 0.0f, 1.0f);
    _renderer.add(_world_b0, _projection * camera_back * world_trafo_b, 6000, 0.0f);
    world_trafo_b = Mth::make_matrix(1.0f, 0.0f, world_b_pos1 * 2048.0f,
                                     0.0f, 1.0f, 630.0f,
                                     0.0f, 0.0f, 1.0f);
    _renderer.add(_world_b0, _projection * camera_back * world_trafo_b, 6000, 0.0f);
    
    std::vector<Entity> despawn_bullets;
    for (Entity entity : _bullets ) {
        std::shared_ptr<Bullet> bullet = _components.get<BulletComponent>(entity);
        Collider& collider = _components.get<ColliderComponent>(entity);
        //collider.velocity = (float)bullet->look_x * Mth::make_cvector(2000.0f, 0.0f);
        collider.velocity = bullet->velocity;
        Mth::Matrix<float, 3, 3> translation = transformation(collider.position(0), collider.position(1));
        _renderer.add(bullet->sprite(), _projection * camera * translation * bullet->transformation(), collider.position(1), 0.0f);
        
        for (Entity other : collider.touching) {
            Entities::iterator other_it = _characters.find(other);
            if (other_it != _characters.end()) {
                if (*other_it == _player_character) {
                    start_shake(10.0f);
                    _mixer.play(*_hit_soumd, 0, 5);
                }
                std::shared_ptr<Character> other_char = _components.get<CharacterComponent>(other);
                other_char->health -= 1;
                other_char->fade = 1.0f;
            }
            
            Entities::iterator boss_it = _bosses.find(other);
            if (boss_it != _bosses.end()) {
                std::shared_ptr<Boss> boss = _components.get<BossComponent>(other);
                boss->health -= 1;
                boss->fade = 1.0f;
            }
        }
        
        if (collider.touching.size() > 0) {
            bullet->time = 100.0f;
        }
        
        bullet->update(dt);
        
        if (bullet->dead()) {
            despawn_bullets.push_back(entity);
        }
    }
    
    std::vector<Entity> despawn_granades;
    for (Entity entity : _granades ) {
        std::shared_ptr<Granade> granade = _components.get<GranadeComponent>(entity);
        Collider& collider = _components.get<ColliderComponent>(entity);
        collider.velocity = granade->velocity;
        Mth::Matrix<float, 3, 3> translation = transformation(collider.position(0), collider.position(1));
        _renderer.add(granade->sprite(), _projection * camera * translation * granade->transformation(), collider.position(1), granade->fade);
        
        granade->update(dt);
        
        if (granade->dead()) {
            despawn_granades.push_back(entity);
            
            Entity explosion = _next_entity++;
            std::shared_ptr<Smoke>& smoke = _components.add<SmokeComponent>(explosion);
            smoke = std::shared_ptr<Smoke>(new Smoke(_explosion));
            smoke->position = collider.position;
            smoke->deal_damage = true;
            _smokes.insert(explosion);
            
            start_shake(80.0f);
            
            _mixer.play(*_explosion_sound, 0, 6);
            
            for (Entity centity : _characters) {
                if (!(collider.group == CG_EG && centity != _player_character)) {
                    std::shared_ptr<Character> character = _components.get<CharacterComponent>(centity);
                    Collider& ccollider = _components.get<ColliderComponent>(centity);
                    if (Mth::length(smoke->position - ccollider.position) < smoke->damage_radius) {
                        character->health -= 3;
                        character->fade = 1.0f;
                    }
                }
            }
            
            if (!(collider.group == CG_EG)) {
                for (Entity bentity : _bosses) {
                    std::shared_ptr<Boss> boss = _components.get<BossComponent>(bentity);
                    Collider& bcollider = _components.get<ColliderComponent>(bentity);
                    if (Mth::length(smoke->position - bcollider.position) < smoke->damage_radius) {
                        boss->health -= 3;
                        boss->fade = 1.0f;
                    }
                }
            }
        }
    }
    
    std::vector<Entity> despawn_smoke;
    for (Entity entity : _smokes ) {
        std::shared_ptr<Smoke> smoke = _components.get<SmokeComponent>(entity);
        _renderer.add(smoke->sprite(), _projection * camera * smoke->transformation(), smoke->position(1), 0.0f);
        
        smoke->update(dt);
        
        if (smoke->dead()) {
            despawn_smoke.push_back(entity);
        }
    }
    
    for (Entity entity : despawn_smoke) {
        _smokes.erase(_smokes.find(entity));
        _components.remove(entity);
    }
    
    for (Entity entity : despawn_granades) {
        _granades.erase(_granades.find(entity));
        _colliders.erase(_colliders.find(entity));
        _components.remove(entity);
    }
    
    for (Entity entity : despawn_bullets) {
        _bullets.erase(_bullets.find(entity));
        _colliders.erase(_colliders.find(entity));
        _components.remove(entity);
    }
    
    std::vector<Entity> despawn_characters;
    for (Entity entity : _characters) {
        std::shared_ptr<Character> character = _components.get<CharacterComponent>(entity);
        
        Collider& collider = _components.get<ColliderComponent>(entity);
        Mth::Matrix<float, 3, 3> translation = transformation(collider.position(0), collider.position(1));
        _renderer.add(character->gun_sprite(), _projection * camera * translation * character->gun_transformation(), collider.position(1), character->fade);
        _renderer.add(character->body_sprite(), _projection * camera * translation * character->body_transformation(), collider.position(1), character->fade);
        
        if (collider.position(0) < (_camera_x_f)) {
            Mth::Matrix<float, 3, 3> trafo = transformation(30.0f, collider.position(1));
            _renderer.add(_arrow_small, _projection * trafo * flip(true, false), -5, 0.0f);
        }
        if (collider.position(0) > (_camera_x_f + 1024.0f)) {
            Mth::Matrix<float, 3, 3> trafo = transformation(994.0f, collider.position(1));
            _renderer.add(_arrow_small, _projection * trafo, -5, 0.0f);
        }
        
        if (entity != _player_character) {
            ai(*character, collider, *player, player_collider);
        }
        
        for (Entity sentity : _smokes ) {
            std::shared_ptr<Smoke> smoke = _components.get<SmokeComponent>(sentity);
            if (smoke->deal_damage) {
                Mth::CVector<float, 2> distance = collider.position - smoke->position;
                if (Mth::length(distance) < smoke->damage_radius) {
                    collider.velocity += Mth::normal(distance) * 1000.0f;
                }
            }
        }
        
        character->update(dt);
        
        if (character->health <= 0) {
            if (entity == _player_character) {
                //_stage_timer = 0.0f;
                //_go_to_next_stage = true;
                //_player_state = 1;
                _fail = true;
            } else {
                std::cout << "Kill" << std::endl;
                _mixer.play(*_kill_sound, 0, -1);
                if (random_int(0, 1) == 0) {
                    Entity pickup = _next_entity++;
                    std::shared_ptr<Pickup>& p = _components.add<PickupComponent>(pickup);
                    p = std::shared_ptr<Pickup>(new Pickup(_pickup_image));
                    p->position = collider.position;
                    _pickups.insert(pickup);
                    std::cout << "pickups: " << _pickups.size() << std::endl;
                }
                despawn_characters.push_back(entity);
            }
        }
    }
    for (Entity entity : despawn_characters) {
        _characters.erase(_characters.find(entity));
        _colliders.erase(_colliders.find(entity));
        _components.remove(entity);
    }
    
    std::vector<Entity> despawn_bosses;
    for (Entity entity : _bosses) {
        std::shared_ptr<Boss> boss = _components.get<BossComponent>(entity);
        
        Collider& collider = _components.get<ColliderComponent>(entity);
        Mth::Matrix<float, 3, 3> translation = transformation(collider.position(0), collider.position(1));
        //_renderer.add(character->gun_sprite(), _projection * camera * translation * character->gun_transformation(), collider.position(1), character->fade);
        _renderer.add(boss->sprite(), _projection * camera * translation * boss->transformation(), collider.position(1), boss->fade);
        
        if (collider.position(0) < (_camera_x_f)) {
            Mth::Matrix<float, 3, 3> trafo = transformation(30.0f, collider.position(1));
            _renderer.add(_arrow_small, _projection * trafo * flip(true, false), -5, 0.0f);
        }
        if (collider.position(0) > (_camera_x_f + 1024.0f)) {
            Mth::Matrix<float, 3, 3> trafo = transformation(994.0f, collider.position(1));
            _renderer.add(_arrow_small, _projection * trafo, -5, 0.0f);
        }
        
        boss_ai(*boss, collider, *player, player_collider);
        
        for (Entity sentity : _smokes ) {
            std::shared_ptr<Smoke> smoke = _components.get<SmokeComponent>(sentity);
            if (smoke->deal_damage) {
                Mth::CVector<float, 2> distance = collider.position - smoke->position;
                if (Mth::length(distance) < smoke->damage_radius) {
                    collider.velocity += Mth::normal(distance) * 1000.0f;
                }
            }
        }
        
        if (boss->in_jump) {
            if (boss->jump_timer <= 0.0f) {
                boss->in_jump = false;
                start_shake(80.0f);
                player->health -= 1;
                player->fade = 1.0f;
            }
        }
        
        boss->update(dt);
        
        if (boss->health <= 0) {
            std::cout << "Kill" << std::endl;
            _mixer.play(*_kill_sound, 0, -1);
            despawn_bosses.push_back(entity);
        }
    }
    for (Entity entity : despawn_bosses) {
        _bosses.erase(_bosses.find(entity));
        _colliders.erase(_colliders.find(entity));
        _components.remove(entity);
    }
    
    if (_game_state == GS_Stage && _characters.size() == 1 && _bosses.size() == 0 && *_characters.begin() == _player_character) {
        //std::cout << "clear" << std::endl;
        //_go_to_next_stage = true;
        //_show_reach = true;
        _continue = true;
        _reach_x = player_collider.position(0) + 1024.0f;
        //show_banner(0);
    }
    if (_game_state == GS_Reach && _reach_x < player_collider.position(0)) {
        std::cout << "reach" << std::endl;
        //_go_to_next_stage = true;
        //_show_reach = false;
        _continue = true;
    }
    
    _physics.update(_components, _colliders, dt);
    
    _shake_x *= 0.9f;
    _shake_y *= 0.9f;
    _shake_x_feq *= 0.9f;
    _shake_y_feq *= 0.9f;
}

bool Game::update(SDLSystem const& system, float dt) {
    if (!_mixer.playing(music_channel)) {
        if (_game_state == GS_Title || _game_state == GS_Loose || _game_state == GS_Win) {
            _mixer.play(*_logo_musik, 0, music_channel);
        } else {
            _mixer.play(*_fight_musik, 0, music_channel);
        }
    }
    
    update_banner(dt);
    
    if (_game_state == GS_Title || _game_state == GS_Win || _game_state == GS_Loose) {
        update_menu(dt);
    } else {
        update_game(dt);
    }
    
    if (_continue) {
        std::cout << "continue: ";
        _continue = false;
        
        // next state
        if (_game_state == GS_Reach) {
            std::cout << "stage " << _stage_counter;
            _game_state = GS_Stage;
            show_banner(_stage_counter+1);
            init_stage(_stage_counter);
        } else if (_game_state == GS_Title) {
            if (_title_counter < _title_counter_max) {
                _title_counter++;
                std::cout << "title " << _title_counter;
            } else {
                _mixer.fade_out(music_channel);
                _title_counter = 0;
                _game_state = GS_Reach;
                _reach_x = 2048.0f;
                init_player();
                std::cout << "reach " << _reach_x;
            }
        } else if (_game_state == GS_Stage) {
            if (_stage_counter < _stage_counter_max) {
                show_banner(0);
                _stage_counter++;
                _game_state = GS_Reach;
                std::cout << "reach " << _reach_x;
            } else {
                _mixer.fade_out(music_channel);
                _mixer.play(*_win_sound, 0, -1);
                _game_state = GS_Win;
                _stage_counter = 0;
                std::cout << "win";
            }
        } else if (_game_state == GS_Win) {
            _game_state = GS_Title;
            reset_game();
            std::cout << "title " << _title_counter;
        } else if (_game_state == GS_Loose) {
            _mixer.fade_out(music_channel);
            _game_state = GS_Reach;
            _reach_x = 2048.0f;
            _stage_counter = 0;
            init_player();
            std::cout << "reach " << _reach_x;
        }
        std::cout << std::endl;
    } else if (_fail) {
        _fail = false;
        
        // to loose state
        if (_game_state == GS_Reach || _game_state == GS_Stage) {
            _mixer.fade_out(music_channel);
            reset_game();
            _game_state = GS_Loose;
            _title_counter = 0;
            _stage_counter = 0;
            _mixer.play(*_loose_sound, 0, -1);
        } else if (_game_state == GS_Loose) {
            _game_state = GS_Title;
            _title_counter = 0;
            _stage_counter = 0;
        }
    }
    
    bool done = handle_inpout(system);
    _renderer.flush();
    return done;
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

                case SDLK_k: case SDLK_f:
                    _control_granade = 1;
                    break;
                case SDLK_j: case SDLK_g:
                    _control_fire = 1;
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
                    
                case SDLK_x: case SDLK_SPACE: {
                    if (_game_state == GS_Title || _game_state == GS_Win || _game_state == GS_Loose) {
                        //_go_to_next_stage = true;
                        _continue = true;
                    }
                } break;
                case SDLK_k: case SDLK_f:
                    _control_granade = 0;
                    break;
                case SDLK_j: case SDLK_g:
                    _control_fire = 0;
                    break;
                    
                default:
                    break;
            }
        }
    }
    
    _did_move = (_move_x != 0 || _move_y != 0);
    
    _move_x = _control_pos_x - _control_neg_x;
    _move_y = _control_pos_y - _control_neg_y;
    
    return done;
}

void Game::start_shake(float strength) {
    Mth::CVector<float, 2> d = strength * Mth::normal(Mth::make_cvector(random_float(0.0f, 1.0f), random_float(0.0f, 1.0f)));
    
    _shake_x = d(0);
    _shake_y = d(1);
    _shake_x_feq = 8.0f;
    _shake_y_feq = 8.0f;
}

float Game::random_float(float min, float max) {
    std::normal_distribution<float> dist(min, max);
    return dist(_random_engine);
}

int Game::random_int(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(_random_engine);
}

void Game::ai(Character& monster, Collider& monster_collider,
              Character& player, Collider& player_collider) {
    Mth::CVector<float, 2> up = Mth::make_cvector(0.0f, 1.0f);
    Mth::CVector<float, 2> right = Mth::make_cvector(1.0f, 0.0f);
    Mth::CVector<float, 2> distance = player_collider.position - monster_collider.position;
    float length = Mth::length(distance);
    float length_y = Mth::dot(up, distance);
    Mth::CVector<float, 2> direction = Mth::normal(distance);
    int look_x = 1;
    if (Mth::dot(right, direction) < 0.0f) {
        look_x = -1;
    }
    
    monster.look_x = look_x;
    if (length < 800.0f && length > 300.0f) {
        monster_collider.velocity = direction * 300.0f;
        monster.set_animation(1);
    } else if (length < 500.0f && Mth::abs(length_y) > 32.0f) {
        monster_collider.velocity = up * Mth::signum(length_y) * 150.0f;
        monster.set_animation(1);
    } else {
        monster.set_animation(0);
    }
    
    if (monster.weapon == 0 && monster.fire_timer <= 0.0f && length < 400.0f) {
        monster.fire_timer = monster.fire_timer_reset;
        Entity bullet = _next_entity++;
        Collider& collider = _components.add<ColliderComponent>(bullet);
        collider.radius = 8.0f;
        collider.position = monster_collider.position + monster.fire_position();
        collider.group = CG_EB;
        _colliders.insert(bullet);
        _bullets.insert(bullet);
        
        std::shared_ptr<Bullet>& b = _components.add<BulletComponent>(bullet);
        b = std::shared_ptr<Bullet>(new Bullet(_bullet0));
        b->end_time = 2.0f;
        //b->look_x = monster.look_x;
        b->velocity = Mth::make_cvector(monster.look_x * 1000.0f, 0.0f);
        
        _mixer.play(*_shot[1], 0, 2);
    } else if (monster.weapon == 1 && monster.granade_timer <= 0.0f && length < 400.0f) {
        monster.granade_timer = monster.granade_timer_reset;
        Entity granade = _next_entity++;
        Collider& collider = _components.add<ColliderComponent>(granade);
        collider.radius = 8.0f;
        collider.position = monster_collider.position + monster.fire_position();
        collider.group = CG_EG;
        _colliders.insert(granade);
        _granades.insert(granade);
        
        std::shared_ptr<Granade>& b = _components.add<GranadeComponent>(granade);
        b = std::shared_ptr<Granade>(new Granade(_granade));
        b->velocity = Mth::make_cvector(1.0f, 0.0f) * 0.5f * Mth::dot(monster_collider.velocity, Mth::make_cvector(1.0f, 0.0f)) + Mth::make_cvector(monster.look_x * 400.0f, 0.0f);
        b->explosion_time *= 2.0f;
    }
}

void Game::boss_ai(Boss& monster, Collider& monster_collider,
                   Character& player, Collider& player_collider) {
    Mth::CVector<float, 2> up = Mth::make_cvector(0.0f, 1.0f);
    Mth::CVector<float, 2> right = Mth::make_cvector(1.0f, 0.0f);
    Mth::CVector<float, 2> distance = player_collider.position - monster_collider.position;
    float length = Mth::length(distance);
    float length_y = Mth::dot(up, distance);
    Mth::CVector<float, 2> direction = Mth::normal(distance);
    int look_x = 1;
    if (Mth::dot(right, direction) < 0.0f) {
        look_x = -1;
    }
    
    monster.look_x = look_x;
    if (!monster.in_jump && monster.jump_cooldown <= 0.0f) {
        if (length < 2000.0f && length > 100.0f) {
            monster_collider.velocity = direction * 300.0f;
            monster.set_animation(1);
        } else if (length < 500.0f && Mth::abs(length_y) > 32.0f) {
            monster_collider.velocity = up * Mth::signum(length_y) * 150.0f;
            monster.set_animation(1);
        } else {
            monster.set_animation(0);
        }
    } else {
        monster.set_animation(0);
    }
    
    if (!monster.in_jump && length < 150.0f) {
        if (monster.jump()) {
            Entity explosion = _next_entity++;
            std::shared_ptr<Smoke>& smoke = _components.add<SmokeComponent>(explosion);
            smoke = std::shared_ptr<Smoke>(new Smoke(_boss_jump));
            smoke->position = monster_collider.position - Mth::make_cvector(0.0f, 100.0f);
            smoke->deal_damage = false;
            smoke->end_time = 0.5f;
            _smokes.insert(explosion);
        }
    }
    
    if (!monster.in_jump && monster.jump_cooldown <= 0.0f) {
        if (monster.weapon == 0 && monster.fire_timer <= 0.0f && length < 500.0f) {
            monster.fire_timer = monster.fire_timer_reset;
            Entity bullet = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(bullet);
            collider.radius = 8.0f;
            collider.position = monster_collider.position + monster.fire_position();
            collider.group = CG_EB;
            _colliders.insert(bullet);
            _bullets.insert(bullet);
            
            std::shared_ptr<Bullet>& b = _components.add<BulletComponent>(bullet);
            b = std::shared_ptr<Bullet>(new Bullet(_bullet0));
            b->end_time = 2.0f;
            //b->look_x = monster.look_x;
            b->velocity = Mth::make_cvector(monster.look_x * 1500.0f, 0.0f);
            
            _mixer.play(*_shot[1], 0, 2);
        } else if (monster.weapon == 1 && monster.granade_timer <= 0.0f && length < 500.0f) {
            monster.granade_timer = monster.granade_timer_reset;
            Entity granade = _next_entity++;
            Collider& collider = _components.add<ColliderComponent>(granade);
            collider.radius = 8.0f;
            collider.position = monster_collider.position + monster.fire_position();
            collider.group = CG_EG;
            _colliders.insert(granade);
            _granades.insert(granade);
            
            std::shared_ptr<Granade>& b = _components.add<GranadeComponent>(granade);
            b = std::shared_ptr<Granade>(new Granade(_granade));
            b->velocity = Mth::make_cvector(1.0f, 0.0f) * 0.5f * Mth::dot(monster_collider.velocity, Mth::make_cvector(1.0f, 0.0f)) + Mth::make_cvector(monster.look_x * 400.0f, 0.0f);
            b->explosion_time *= 2.0f;
        }
    }
}

void Game::update_banner(float dt) {
    float const t = 0.3f;
    
    if (_show_banner >= 0) {
        _banner_timer += dt;
        Mth::Matrix<float, 3, 3> trafo = Mth::make_matrix(1.0f, 0.0f, 512.0f,
                                                          0.0f, 1.0f, 384.0f,
                                                          0.0f, 0.0f, 1.0f);
        if (_banner_phase == 0) {
            trafo(1,2) += 500.0f;
        } else if (_banner_phase == 1) {
            trafo(1,2) += (500.0f - (_banner_timer / t * 500.0f));
        } else if (_banner_phase == 4) {
            trafo(1,2) -= (_banner_timer / t * 500.0f);
        }
        _renderer.add(_stage_banner[_show_banner], _projection * trafo, -100, 0.0f);
        
        if (_banner_timer > t) {
            _banner_timer = 0.0f;
            if (_banner_phase < 4) {
                if (_banner_phase == 1) {
                    _mixer.play(*_banner_sound, 0, 7);
                }
                _banner_phase++;
            } else {
                _show_banner = -1;
                _banner_phase = 0;
            }
        }
    }
}

void Game::show_banner(int banner) {
    _banner_phase = 0;
    _show_banner = banner;
    _banner_timer = 0.0f;
}

////////////////////////////////////////////////////////////////////////////////