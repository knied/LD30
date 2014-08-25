//
//  Bullet.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "Bullet.h"
#include "Transformation.h"

Bullet::Bullet(Sprite* sprite)
: _sprite(sprite), time(0.0f) {
    
}

Mth::Matrix<float, 3, 3> Bullet::transformation() const {
    return ::transformation(9, 0) * flip(velocity(0) < 0.0f, false);
}

Sprite* Bullet::sprite() const {
    return _sprite;
}

void Bullet::update(float dt) {
    time += dt;
}

bool Bullet::dead() const {
    return time > end_time;
}