//
//  Bullet.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef __LD30Xcode__Bullet__
#define __LD30Xcode__Bullet__

#include <iostream>
#include "Sprite.h"

class Bullet {
    Sprite* _sprite;
    
public:
    Bullet(Sprite* sprite);
    
    //int look_x;
    //int look_y;
    float time;
    float end_time = 0.3f;
    Mth::CVector<float, 2> velocity;
    
    Mth::Matrix<float, 3, 3> transformation() const;
    
    Sprite* sprite() const;
    
    void update(float dt);
    bool dead() const;
};

#endif /* defined(__LD30Xcode__Bullet__) */
