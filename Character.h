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
    Sprite* _head;
    Sprite* _body;
    Sprite* _gun;
    
    Mth::Matrix<float, 3, 3> transformation(int x, int y) const;
    Mth::Matrix<float, 3, 3> flip(bool x, bool y) const;
    
    float _timer;
    int _animation;
    
protected:
    virtual Mth::CVector<int, 2> head_offset() const;
    virtual Mth::CVector<int, 2> body_offset() const;
    virtual Mth::CVector<int, 2> gun_offset() const;
    
public:
    Character(Sprite* head, Sprite* body, Sprite* gun);
    ~Character();
    
    Mth::CVector<float, 2> position;
    int look_x;
    int look_y;
    
    Mth::Matrix<float, 3, 3> head_transformation() const;
    Mth::Matrix<float, 3, 3> body_transformation() const;
    Mth::Matrix<float, 3, 3> gun_transformation() const;
    
    Sprite* head_sprite() const;
    Sprite* body_sprite() const;
    Sprite* gun_sprite() const;
    
    void set_animation(int i);
    void update(float dt);
};

#endif /* defined(__LD30Xcode__Character__) */
