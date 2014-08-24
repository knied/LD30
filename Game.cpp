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
#include "Transformation.h"

////////////////////////////////////////////////////////////////////////////////

Game::Game(SDLSystem const& system)
: _resource_path(system.resource_path()),
_control_pos_x(0), _control_neg_x(0), _control_pos_y(0), _control_neg_y(0), _control_fire(0), _move_x(0), _move_y(0), _renderer(system),
_next_entity(1), _shake_x(0.0f), _shake_y(0.0f), _shake_x_feq(0.0f), _shake_y_feq(0.0f), _mixer(system) {
    if (!_mixer.valid()) {
        std::cout << "error" << std::endl;
    }
    
    _projection = Mth::make_matrix(1.0f/512.0f, 0.0f, -1.0f,
                                   0.0f, 1.0f/384.0f, -1.0f,
                                   0.0f, 0.0f, 1.0f);
    
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
    _bullet0 = new Sprite(image_loader, "bullet.png");
    _world_f0 = new Sprite(image_loader, "world_1_1.png");
    _world_b0 = new Sprite(image_loader, "world_1_2.png");
    
    _shot.push_back(new SDLMixerChunk(_mixer, "Shot 01.ogg"));
    _logo_musik = new SDLMixerChunk(_mixer, "Logo LD03 v1nn.ogg");
    //_shot.push_back(new SDLMixerChunk(_mixer, "Shot 02.ogg"));
    //_shot.push_back(new SDLMixerChunk(_mixer, "Shot 03.ogg"));
    //_shot.push_back(new SDLMixerChunk(_mixer, "Shot 04.ogg"));
    
    _mixer.play(*_logo_musik, 0, -1);
    
    {
        _player_character = _next_entity++;
        Collider& collider = _components.add<ColliderComponent>(_player_character);
        collider.radius = 50.0f;
        collider.position = Mth::make_cvector(300.0f, 300.0f);
        _components.add<CharacterComponent>(_player_character) = std::shared_ptr<Character>(new Character(_stand_l0, _stand_r0,
                                                                                                          _walk_l0, _walk_r0,
                                                                                                          _weapon_l0, _weapon_r0));
        _characters.insert(_player_character);
        _colliders.insert(_player_character);
    }
    
    for (int i = 0; i < 2; ++i) {
        Entity entity = _next_entity++;
        Collider& collider = _components.add<ColliderComponent>(entity);
        collider.radius = 50.0f;
        collider.position = Mth::make_cvector(400.0f + 100.0f * i, 400.0f + 100.0f * i);
        _components.add<CharacterComponent>(entity) = std::shared_ptr<Character>(new Character(_stand_l0, _stand_r0,
                                                                                               _walk_l0, _walk_r0,
                                                                                               _weapon_l0, _weapon_r0));
        _characters.insert(entity);
        _colliders.insert(entity);
    }
}

Game::~Game() {
    
}

bool Game::update(SDLSystem const& system, float dt) {
    Mth::Matrix<float, 3, 3> shake = Mth::make_matrix(1.0f, 0.0f, _shake_x * Mth::sin(_shake_x_feq),
                                                      0.0f, 1.0f, _shake_y * Mth::sin(_shake_y_feq),
                                                      0.0f, 0.0f, 1.0f);
    
    std::shared_ptr<Character> player = _components.get<CharacterComponent>(_player_character);
    Collider& player_collider = _components.get<ColliderComponent>(_player_character);
    
    Mth::CVector<float, 2> direction = Mth::normal(Mth::make_cvector<float>(_move_x, _move_y));
    player_collider.velocity = direction * 800.0f;
    
    if (_fire_timer < 0.1f) {
        _fire_timer += dt;
    }
    
    if (_control_fire == 1 && _fire_timer >= 0.1f) {
        _fire_timer = 0.0f;
        Entity bullet = _next_entity++;
        Collider& collider = _components.add<ColliderComponent>(bullet);
        collider.radius = 8.0f;
        collider.position = player_collider.position + player->fire_position();
        _colliders.insert(bullet);
        _bullets.insert(bullet);
        
        std::shared_ptr<Bullet>& b = _components.add<BulletComponent>(bullet);
        b = std::shared_ptr<Bullet>(new Bullet(_bullet0));
        b->look_x = player->look_x;
        
        _mixer.play(*_shot[0], 0, -1);
    }
    
    Mth::Matrix<float, 3, 3> world_trafo_f = Mth::make_matrix(1.0f, 0.0f, 1024.0f,
                                                              0.0f, 1.0f, 420.0f,
                                                              0.0f, 0.0f, 1.0f);
    _renderer.add(_world_f0, _projection * shake * world_trafo_f, 3000, 0.0f);
    Mth::Matrix<float, 3, 3> world_trafo_b = Mth::make_matrix(1.0f, 0.0f, 1024.0f,
                                                              0.0f, 1.0f, 630.0f,
                                                              0.0f, 0.0f, 1.0f);
    _renderer.add(_world_b0, _projection * shake * world_trafo_b, 6000, 0.0f);
    
    std::vector<Entity> despawn_bullets;
    for (Entity entity : _bullets ) {
        std::shared_ptr<Bullet> bullet = _components.get<BulletComponent>(entity);
        Collider& collider = _components.get<ColliderComponent>(entity);
        collider.velocity = (float)bullet->look_x * Mth::make_cvector(2000.0f, 0.0f);
        Mth::Matrix<float, 3, 3> translation = transformation(collider.position(0), collider.position(1));
        _renderer.add(bullet->sprite(), _projection * shake * translation * bullet->transformation(), collider.position(1), 0.0f);
        
        for (Entity other : collider.touching) {
            Entities::iterator other_it = _characters.find(other);
            if (other_it != _characters.end()) {
                std::shared_ptr<Character> other_char = _components.get<CharacterComponent>(other);
                other_char->health -= 20;
                other_char->fade = 1.0f;
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
        _renderer.add(character->gun_sprite(), _projection * shake * translation * character->gun_transformation(), collider.position(1), character->fade);
        _renderer.add(character->body_sprite(), _projection * shake * translation * character->body_transformation(), collider.position(1), character->fade);
        
        character->update(dt);
        
        if (character->health <= 0) {
            despawn_characters.push_back(entity); 
        }
    }
    for (Entity entity : despawn_characters) {
        _characters.erase(_characters.find(entity));
        _colliders.erase(_colliders.find(entity));
        _components.remove(entity);
    }

    _physics.update(_components, _colliders, dt);
    
    _renderer.flush();
    
    _shake_x *= 0.9f;
    _shake_y *= 0.9f;
    _shake_x_feq *= 0.9f;
    _shake_y_feq *= 0.9f;

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
                    
                case SDLK_x: case SDLK_SPACE:
                    _control_fire = 1;
                    break;
                    
                case SDLK_t:
                    start_shake();
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
                    
                case SDLK_x: case SDLK_SPACE:
                    _control_fire = 0;
                    break;
                    
                default:
                    break;
            }
        }
    }
    
    _move_x = _control_pos_x - _control_neg_x;
    _move_y = _control_pos_y - _control_neg_y;
    
    std::shared_ptr<Character> character = _components.get<CharacterComponent>(_player_character);
    if (_move_x != 0) {
        character->look_x = _move_x;
    }
    
    if (_move_x != 0 || _move_y != 0) {
        character->set_animation(1);
    } else {
        character->set_animation(0);
    }
    
    return done;
}

void Game::start_shake() {
    /*_shake_x = 5.0f + 10.0f * random_float(0.0f, 1.0f);
    _shake_y = 5.0f + 10.0f * random_float(0.0f, 1.0f);
    _shake_x_feq = 5.0f * random_float(0.0f, 1.0f);
    _shake_y_feq = 5.0f * random_float(0.0f, 1.0f);*/
    
    Mth::CVector<float, 2> d = 30.0f * Mth::normal(Mth::make_cvector(random_float(0.0f, 1.0f), random_float(0.0f, 1.0f)));
    
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

////////////////////////////////////////////////////////////////////////////////