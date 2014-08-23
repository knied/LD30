//
//  Game.h
//
//  Created by Kristof Niederholtmeyer on 19.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __Game__
#define __Game__

////////////////////////////////////////////////////////////////////////////////

#include "GLClasses.h"
#include "Sprite.h"
#include "Character.h"
#include "GameComponents.h"

////////////////////////////////////////////////////////////////////////////////

class Game {
    std::string _resource_path;
    GLProgram _program;
    GLint _model_view_location;
    GLint _texture0_location;
    
    std::vector<Sprite*> _sprites;
    std::vector<Character*> _characters;
    
    int _control_pos_x, _control_pos_y;
    int _control_neg_x, _control_neg_y;
    int _move_x;
    int _move_y;
    
    Mth::Matrix<float, 3, 3> _projection;
    
    bool handle_inpout(SDLSystem const& system);
    
public:
    Game(SDLSystem const& system);
    ~Game();
    
    bool update(SDLSystem const& system, float dt);
};

////////////////////////////////////////////////////////////////////////////////

#endif /* defined(__Game__) */

////////////////////////////////////////////////////////////////////////////////
