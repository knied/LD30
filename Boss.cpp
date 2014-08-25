//
//  Boss.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 25.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "Boss.h"

Boss::Boss(std::vector<Sprite*> const& stand_l, std::vector<Sprite*> const& stand_r,
           std::vector<Sprite*> const& walk_l, std::vector<Sprite*> const& walk_r)
: _stand_l(stand_l), _stand_r(stand_r), _walk_l(walk_l), _walk_r(walk_r), fire_timer_reset(0.2f), fire_timer(0.5f), granade_timer_reset(0.8f), granade_timer(2.0f) {
    
}

Sprite* Boss::sprite() const {
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

Mth::Matrix<float, 3, 3> Boss::transformation() const {
    Mth::Matrix<float, 3, 3> trafo;
    if (in_jump) {
        trafo(1, 2) = 64.0f * Mth::sin(jump_timer * Mth::pi);
    }
    return trafo;
}

void Boss::update(float dt) {
    _timer += dt;
    while (_timer >= 1.0f) {
        _timer = 0.0f;
        state++;
        if (state > 5) {
            state = 0;
        }
    }
    
    if (state == 0) {
        weapon = 0;
    } else if (state == 2) {
        weapon = 0;
    } else if (state == 4) {
        weapon = 1;
    } else {
        fire_timer = fire_timer_reset;
        granade_timer = granade_timer_reset;
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
    
    if (jump_timer > 0.0f) {
        jump_timer -= 4.0f * dt;
    }
    
    if (jump_cooldown > 0.0f) {
        jump_cooldown -= dt;
    }
}

Mth::CVector<float, 2> Boss::fire_position() const {
    return Mth::make_cvector((float)look_x * 64.0f, -20.0f);
}

Mth::CVector<float, 2> Boss::granade_position() const {
    return Mth::make_cvector((float)look_x * 64.0f, -40.0f);
}

void Boss::set_animation(int i) {
    _animation = i;
}

bool Boss::jump() {
    if (jump_cooldown <= 0.0f) {
        in_jump = true;
        jump_timer = 1.0f;
        jump_cooldown = 1.0f;
        return true;
    }
    return false;
}
