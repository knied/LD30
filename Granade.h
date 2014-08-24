//
//  Granade.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 24.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef __LD30Xcode__Granade__
#define __LD30Xcode__Granade__

#include <iostream>
#include "Sprite.h"

class Granade {
    Sprite* _sprite;
    
public:
    Granade(Sprite* sprite);
    
    float time;
    float explosion_time;
    float fade;
    Mth::CVector<float, 2> velocity;
    
    Sprite* sprite() const;
    Mth::Matrix<float, 3, 3> transformation() const;
    
    void update(float dt);
    bool dead() const;
};

#endif /* defined(__LD30Xcode__Granade__) */
