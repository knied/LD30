//
//  Boss.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 25.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef __LD30Xcode__Boss__
#define __LD30Xcode__Boss__

#include <iostream>
#include "Sprite.h"

class Boss {
    std::vector<Sprite*> _stand_l;
    std::vector<Sprite*> _stand_r;
    std::vector<Sprite*> _walk_l;
    std::vector<Sprite*> _walk_r;
    int _animation = 0;
    
public:
    Boss(std::vector<Sprite*> const& stand_l, std::vector<Sprite*> const& stand_r,
         std::vector<Sprite*> const& walk_l, std::vector<Sprite*> const& walk_r);
    
    int health = 20;
    float fade = 0.0f;
    int look_x = 1;
    int look_y = -1;
    int weapon = 0;
    float fire_timer_reset;
    float fire_timer;
    float granade_timer_reset;
    float granade_timer;
    
    float jump_timer = 0.0f;
    float jump_cooldown = 0.0f;
    bool in_jump = false;
    
    float _timer = 0.0f;
    int state = 0;
    
    Sprite* sprite() const;
    Mth::Matrix<float, 3, 3> transformation() const;
    
    Mth::CVector<float, 2> fire_position() const;
    Mth::CVector<float, 2> granade_position() const;
    
    bool jump();
    void update(float dt);
    void set_animation(int i);
};

#endif /* defined(__LD30Xcode__Boss__) */
