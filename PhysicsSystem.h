//
//  PhysicsSystem.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef __LD30Xcode__PhysicsSystem__
#define __LD30Xcode__PhysicsSystem__

#include <iostream>
#include "GameComponents.h"

class PhysicsSystem {
public:
    void update(GameComponents& components, Entities const& entities,  float dt);
};

#endif /* defined(__LD30Xcode__PhysicsSystem__) */
