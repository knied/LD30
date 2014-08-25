//
//  Prop.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 25.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef __LD30Xcode__Prop__
#define __LD30Xcode__Prop__

#include <iostream>
#include "Sprite.h"

class Prop {
    Sprite* _sprite;
    
public:
    Prop(Sprite* sprite);
    
    int level_bucket;
    
    Sprite* sprite() const;
    Mth::Matrix<float, 3, 3> transformation() const;
};

#endif /* defined(__LD30Xcode__Prop__) */
