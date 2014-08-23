//
//  Character.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "Character.h"
#include "Transformation.h"

Character::Character(Sprite* head, Sprite* body, Sprite* gun)
: _head(head), _body(body), _gun(gun), look_x(1), look_y(-1), _timer(0.0f), _animation(0), health(100) {
}

Character::~Character() {
    
}

Mth::CVector<int, 2> Character::head_offset() const {
    int a = 0;
    if (_animation == 0) {
        a = 5.0f * Mth::sin(2.0f * Mth::pi * _timer);
    } else if (_animation == 1) {
        a = 10.0f * Mth::sin(4.0f * Mth::pi * _timer);
    }
    int x = look_x < 0 ? -10 : 10;
    int y = 108;
    return Mth::make_cvector(x, y + a);
}

Mth::CVector<int, 2> Character::body_offset() const {
    return Mth::make_cvector(0, 44);
}

Mth::CVector<int, 2> Character::gun_offset() const {
    int a = 0;
    if (_animation == 1) {
        a = -10.0f * Mth::sin(8.0f * Mth::pi * _timer);
    }
    int x = look_x < 0 ? -32 : 32;
    int y = 24;
    return Mth::make_cvector(x + a, y);
}

Mth::Matrix<float, 3, 3> Character::head_transformation() const {
    Mth::CVector<int, 2> t = head_offset();
    return transformation(t(0), t(1)) * flip(look_x < 0, false);
}

Mth::Matrix<float, 3, 3> Character::body_transformation() const {
    Mth::CVector<int, 2> t = body_offset();
    return transformation(t(0), t(1)) * flip(look_x < 0, false);
}

Mth::Matrix<float, 3, 3> Character::gun_transformation() const {
    Mth::CVector<int, 2> t = gun_offset();
    return transformation(t(0), t(1)) * flip(look_x < 0, false);
}

Mth::CVector<float, 2> Character::fire_position() const {
    return Mth::make_cvector((float)look_x * 64.0f, 40.0f);
}

Sprite* Character::head_sprite() const {
    return _head;
}

Sprite* Character::body_sprite() const {
    return _body;
}

Sprite* Character::gun_sprite() const {
    return _gun;
}

void Character::set_animation(int i) {
    _animation = i;
}

void Character::update(float dt) {
    _timer += dt;
    while (_timer > 1.0f) {
        _timer -= 1.0f;
    }
    
    fade -= 8.0f * dt;
    if (fade < 0.0f) {
        fade = 0.0f;
    }
}
