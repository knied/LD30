//
//  Granade.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 24.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "Granade.h"
#include "Transformation.h"

Granade::Granade(Sprite* sprite)
: time(0.0f), explosion_time(0.5f), _sprite(sprite), fade(0.0f) {
    
}

Sprite* Granade::sprite() const {
    return _sprite;
}

Mth::Matrix<float, 3, 3> Granade::transformation() const {
    return ::transformation(0, (explosion_time - time) / explosion_time * 64.0f * Mth::abs(Mth::sin(8.0f * time)));
}

void Granade::update(float dt) {
    //fade = 0.5f + 0.5f * Mth::cos(time);
    fade = 0.0f;
    time += dt;
    //velocity *= 0.98f;
}

bool Granade::dead() const {
    return time > explosion_time;
}