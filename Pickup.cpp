//
//  Pickup.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 25.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "Pickup.h"
#include "Transformation.h"

Pickup::Pickup(Sprite* sprite)
: _sprite(sprite) {
    
}

Sprite* Pickup::sprite() const {
    return _sprite;
}

Mth::Matrix<float, 3, 3> Pickup::transformation() const {
    return ::transformation(position(0), position(1));
}