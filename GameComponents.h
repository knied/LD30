//
//  GameComponents.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef LD30Xcode_GameComponents_h
#define LD30Xcode_GameComponents_h

#include "Components.h"
#include "MthMatrix.h"

typedef int Entity;

struct Collider {
    Mth::CVector<float, 2> position;
    Mth::CVector<float, 2> velocity;
    float radius;
};

typedef Components<Entity, Collider> GameComponents;

#endif
