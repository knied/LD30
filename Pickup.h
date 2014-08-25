//
//  Pickup.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 25.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef __LD30Xcode__Pickup__
#define __LD30Xcode__Pickup__

#include <iostream>
#include "Sprite.h"

class Pickup {
    Sprite* _sprite;
    
public:
    Pickup(Sprite* sprite);
    
    Mth::CVector<float, 2> position;
    
    Sprite* sprite() const;
    Mth::Matrix<float, 3, 3> transformation() const;
};

#endif /* defined(__LD30Xcode__Pickup__) */
