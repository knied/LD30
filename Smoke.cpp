//
//  Smoke.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 24.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "Smoke.h"
#include "Transformation.h"

Smoke::Smoke(std::vector<Sprite*> sprite)
: _sprite(sprite), time(0.0f), end_time(0.3f) {
    
}

Sprite* Smoke::sprite() const {
    float a = time / end_time;
    int i = a * _sprite.size();
    i = std::min(i, (int)_sprite.size()-1);
    return _sprite[i];
}

Mth::Matrix<float, 3, 3> Smoke::transformation() const {
    return ::transformation(position(0), position(1));
}

void Smoke::update(float dt) {
    time += dt;
}

bool Smoke::dead() const {
    return time > end_time;
}