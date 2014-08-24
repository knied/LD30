//
//  Smoke.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 24.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef __LD30Xcode__Smoke__
#define __LD30Xcode__Smoke__

#include <iostream>
#include "Sprite.h"

class Smoke {
    std::vector<Sprite*> _sprite;
    
public:
    Smoke(std::vector<Sprite*> sprite);
    
    float time;
    float end_time;
    Mth::CVector<float, 2> position;
    float damage_radius = 150.0f;
    bool deal_damage = false;
    
    Sprite* sprite() const;
    Mth::Matrix<float, 3, 3> transformation() const;
    
    void update(float dt);
    bool dead() const;
};

#endif /* defined(__LD30Xcode__Smoke__) */
