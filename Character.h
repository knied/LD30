//
//  Character.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef __LD30Xcode__Character__
#define __LD30Xcode__Character__

#include <iostream>
#include "Sprite.h"
#include "GLClasses.h"

class Character {
    std::vector<Sprite*> _stand_l;
    std::vector<Sprite*> _stand_r;
    std::vector<Sprite*> _walk_l;
    std::vector<Sprite*> _walk_r;
    std::vector<Sprite*> _weapon_l;
    std::vector<Sprite*> _weapon_r;
    
    float _timer;
    int _animation;
    
protected:
    virtual Mth::CVector<int, 2> body_offset() const;
    virtual Mth::CVector<int, 2> gun_offset() const;
    
public:
    Character(std::vector<Sprite*> const& stand_l,
              std::vector<Sprite*> const& stand_r,
              std::vector<Sprite*> const& walk_l,
              std::vector<Sprite*> const& walk_r,
              std::vector<Sprite*> const& weapon_l,
              std::vector<Sprite*> const& weapon_r);
    ~Character();
    
    int look_x;
    int look_y;
    int health;
    float fade;
    float fire_timer_reset;
    float fire_timer;
    float granade_timer_reset;
    float granade_timer;
    
    Mth::Matrix<float, 3, 3> body_transformation() const;
    Mth::Matrix<float, 3, 3> gun_transformation() const;
    
    Mth::CVector<float, 2> fire_position() const;
    Mth::CVector<float, 2> granade_position() const;
    
    Sprite* body_sprite() const;
    Sprite* gun_sprite() const;
    
    void set_animation(int i);
    void update(float dt);
};

#endif /* defined(__LD30Xcode__Character__) */
