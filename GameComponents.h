//
//  GameComponents.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef LD30Xcode_GameComponents_h
#define LD30Xcode_GameComponents_h

#include <vector>
#include "Components.h"
#include "MthMatrix.h"
#include "Character.h"
#include "Bullet.h"

typedef int Entity;
typedef std::set<Entity> Entities;

typedef enum : int {
    CG_P, // player
    CG_E, // enemy
    CG_PB, // player bullet
    CG_EB, // enemy bullet
} ColliderGroup;

struct Collider {
    Mth::CVector<float, 2> position;
    Mth::CVector<float, 2> velocity;
    float radius;
    std::vector<Entity> touching;
    ColliderGroup group;
};

typedef Components<Entity, Collider, std::shared_ptr<Character>, std::shared_ptr<Bullet>> GameComponents;
enum {ColliderComponent = 0, CharacterComponent = 1, BulletComponent = 2};

#endif
