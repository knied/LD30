//
//  Prop.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 25.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "Prop.h"

Prop::Prop(Sprite* sprite)
: _sprite(sprite) {
    
}

Sprite* Prop::sprite() const {
    return _sprite;
}

Mth::Matrix<float, 3, 3> Prop::transformation() const {
    return Mth::Matrix<float, 3, 3>();
}