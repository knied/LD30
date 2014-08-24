//
//  Character.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "Character.h"
#include "Transformation.h"

Character::Character(std::vector<Sprite*> const& stand_l,
                     std::vector<Sprite*> const& stand_r,
                     std::vector<Sprite*> const& walk_l,
                     std::vector<Sprite*> const& walk_r,
                     std::vector<Sprite*> const& weapon_l,
                     std::vector<Sprite*> const& weapon_r)
: _stand_l(stand_l), _stand_r(stand_r),
_walk_l(walk_l), _walk_r(walk_r),
_weapon_l(weapon_l), _weapon_r(weapon_r),
look_x(1), look_y(-1), _timer(0.0f), _animation(0), health(1000), fire_timer_reset(0.2f), fire_timer(0.5f), granade_timer_reset(2.0f), granade_timer(2.0f), fade(0.0f) {
    
}

Character::~Character() {
    
}

Mth::CVector<int, 2> Character::body_offset() const {
    return Mth::make_cvector(0, 0);
}

Mth::CVector<int, 2> Character::gun_offset() const {
    int a = 0;
    if (_animation == 1) {
        a = -10.0f * Mth::sin(8.0f * Mth::pi * _timer);
    }
    int x = 0;
    int y = -40;
    return Mth::make_cvector(x + a, y);
}

Mth::Matrix<float, 3, 3> Character::body_transformation() const {
    Mth::CVector<int, 2> t = body_offset();
    return transformation(t(0), t(1));
}

Mth::Matrix<float, 3, 3> Character::gun_transformation() const {
    Mth::CVector<int, 2> t = gun_offset();
    return transformation(t(0), t(1));
}

Mth::CVector<float, 2> Character::fire_position() const {
    return Mth::make_cvector((float)look_x * 64.0f, -20.0f);
}

Mth::CVector<float, 2> Character::granade_position() const {
    return Mth::make_cvector((float)look_x * 64.0f, -40.0f);
}

Sprite* Character::body_sprite() const {
    if (_animation == 0) {
        if (look_x < 0) {
            int i = (int)(_timer * 8) % _stand_l.size();
            return _stand_l[i];
        } else {
            int i = (int)(_timer * 8) % _stand_r.size();
            return _stand_r[i];
        }
    } else {
        if (look_x < 0) {
            int i = (int)(_timer * 16) % _walk_l.size();
            return _walk_l[i];
        } else {
            int i = (int)(_timer * 16) % _walk_r.size();
            return _walk_r[i];
        }
    }
}

Sprite* Character::gun_sprite() const {
    if (look_x < 0) {
        int i = _timer * _weapon_l.size();
        return _weapon_l[i];
    } else {
        int i = _timer * _weapon_r.size();
        return _weapon_r[i];
    }
}

void Character::set_animation(int i) {
    _animation = i;
}

void Character::update(float dt) {
    _timer += dt;
    while (_timer >= 1.0f) {
        _timer = 0.0f;
    }
    
    if (fire_timer > 0.0f) {
        fire_timer -= dt;
    }
    
    if (granade_timer > 0.0f) {
        granade_timer -= dt;
    }
    
    fade -= 8.0f * dt;
    if (fade < 0.0f) {
        fade = 0.0f;
    }
}
