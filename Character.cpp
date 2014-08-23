//
//  Character.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "Character.h"

Character::Character(Sprite* head, Sprite* body, Sprite* gun)
: _head(head), _body(body), _gun(gun), look_x(1), look_y(-1), _timer(0.0f), _animation(0) {
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
    int y = 128;
    return Mth::make_cvector(x, y + a);
}

Mth::CVector<int, 2> Character::body_offset() const {
    return Mth::make_cvector(0, 64);
}

Mth::CVector<int, 2> Character::gun_offset() const {
    int a = 0;
    if (_animation == 1) {
        a = -10.0f * Mth::sin(8.0f * Mth::pi * _timer);
    }
    int x = look_x < 0 ? -32 : 32;
    int y = 44;
    return Mth::make_cvector(x + a, y);
}

Mth::Matrix<float, 3, 3> Character::head_transformation() const {
    Mth::CVector<int, 2> t = Mth::make_cvector<int>(position(0), position(1));
    t += head_offset();
    return transformation(t(0), t(1)) * flip(look_x < 0, false);
}

Mth::Matrix<float, 3, 3> Character::body_transformation() const {
    Mth::CVector<int, 2> t = Mth::make_cvector<int>(position(0), position(1));
    t += body_offset();
    return transformation(t(0), t(1)) * flip(look_x < 0, false);
}

Mth::Matrix<float, 3, 3> Character::gun_transformation() const {
    Mth::CVector<int, 2> t = Mth::make_cvector<int>(position(0), position(1));
    t += gun_offset();
    return transformation(t(0), t(1)) * flip(look_x < 0, false);
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

Mth::Matrix<float, 3, 3> Character::transformation(int x, int y) const {
    return Mth::make_matrix(1.0f, 0.0f, (float)x,
                            0.0f, 1.0f, (float)y,
                            0.0f, 0.0f, 1.0f);
    
}

Mth::Matrix<float, 3, 3> Character::flip(bool x, bool y) const {
    float a = x ? -1.0f : 1.0f;
    float b = y ? -1.0f : 1.0f;
    return Mth::make_matrix(a, 0.0f, 0.0f,
                            0.0f, b, 0.0f,
                            0.0f, 0.0f, 1.0f);
}

void Character::set_animation(int i) {
    _animation = i;
}

void Character::update(float dt) {
    _timer += dt;
    while (_timer > 1.0f) {
        _timer -= 1.0f;
    }
}
