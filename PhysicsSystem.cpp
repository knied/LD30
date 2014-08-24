//
//  PhysicsSystem.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "PhysicsSystem.h"

struct Contact {
    float distance;
    Mth::CVector<float, 2> normal;
    Collider* collider0;
    Collider* collider1;
    Entity entity0;
    Entity entity1;
    float impuls;
};

struct StaticContact {
    float distance;
    Mth::CVector<float, 2> normal;
    Collider* collider;
    Entity entity;
    float impuls;
};

void PhysicsSystem::update(GameComponents& components, Entities const& entities, float dt) {
    std::vector<Contact> contacts;
    std::vector<StaticContact> static_contacts;
    std::vector<Collider*> colliders(entities.size());
    int collider_index = 0;
    
    float top = 600.0f;
    float bottom = 40.0f;
    
    // find contacts
    for (Entities::const_iterator it0 = entities.begin(); it0 != entities.end(); ++it0) {
        Entity entity0 = *it0;
        Collider* collider0 = &components.get<ColliderComponent>(entity0);
        collider0->touching.clear();
        colliders[collider_index++] = collider0;
        
        static_contacts.push_back({
            top - collider0->position(1) - collider0->radius,
            Mth::make_cvector(0.0f, 1.0f),
            collider0,
            entity0,
            0.0f
        });
        static_contacts.push_back({
            collider0->position(1) - bottom - collider0->radius,
            Mth::make_cvector(0.0f, -1.0f),
            collider0,
            entity0,
            0.0f
        });
        
        Entities::const_iterator it1 = it0; ++it1;
        for (; it1 != entities.end(); ++it1) {
            Entity entity1 = *it1;
            Collider* collider1 = &components.get<ColliderComponent>(entity1);
            
            if ((collider0->group == CG_PB && collider1->group == CG_PB) ||
                (collider0->group == CG_EB && collider1->group == CG_EB) ||
                (collider0->group == CG_PB && collider1->group == CG_EB) ||
                (collider0->group == CG_EB && collider1->group == CG_PB) ||
                (collider0->group == CG_P && collider1->group == CG_PB) ||
                (collider0->group == CG_PB && collider1->group == CG_P) ||
                (collider0->group == CG_E && collider1->group == CG_EB) ||
                (collider0->group == CG_EB && collider1->group == CG_E)) {
                continue;
            }
            
            Mth::CVector<float, 2> d = collider1->position - collider0->position;
            
            Contact c {
                Mth::length(d) - collider0->radius - collider1->radius,
                Mth::normal(d),
                collider0,
                collider1,
                entity0,
                entity1,
                0.0f
            };
            
            contacts.push_back(c);
        }
    }
    
    // solve contacts
    int iterations = 4;
    for (int i = 0; i < iterations; ++i) {
        for (auto& contact : static_contacts) {
            float relative_velocity = Mth::dot(-contact.collider->velocity, contact.normal);
            float remove_impuls = contact.distance / dt + relative_velocity;
            float new_impuls = std::min(contact.impuls + remove_impuls, 0.0f);
            float impuls_change = new_impuls - contact.impuls;
            contact.impuls = new_impuls;
            contact.collider->velocity += contact.normal * impuls_change;
        }
        
        for (auto& contact : contacts) {
            float relative_velocity = Mth::dot(contact.collider1->velocity - contact.collider0->velocity, contact.normal);
            float remove = contact.distance / dt + relative_velocity;
            float remove_impuls = remove / 2.0f;
            float new_impuls = std::min(contact.impuls + remove_impuls, 0.0f);
            float impuls_change = new_impuls - contact.impuls;
            
            contact.impuls = new_impuls;
            contact.collider0->velocity += contact.normal * impuls_change;
            contact.collider1->velocity -= contact.normal * impuls_change;
            
            if (i == iterations-1) {
                if (new_impuls < 0.0f) {
                    contact.collider0->touching.push_back(contact.entity1);
                    contact.collider1->touching.push_back(contact.entity0);
                }
            }
        }
    }
    
    // evaluate simulation
    for (Collider* collider : colliders) {
        collider->position += collider->velocity * dt;
        collider->velocity = Mth::make_cvector(0.0f, 0.0f);
    }
}