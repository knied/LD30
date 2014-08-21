//
//  OBJModel.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 21.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef __LD30Xcode__OBJModel__
#define __LD30Xcode__OBJModel__

#include <iostream>
#include <vector>
#include "MthMatrix.h"

class OBJModel {
    struct Group {
        std::string name;
        std::vector<Mth::CVector<float, 3>> v;
        std::vector<Mth::CVector<float, 2>> vt;
        std::vector<Mth::CVector<float, 3>> vn;
        std::vector<int> fv;
        std::vector<int> fvt;
        std::vector<int> fvn;
    };
    std::vector<Group> _groups;
    
public:
    OBJModel(std::string const& filename) {
        
    }
    ~OBJModel() {
        
    }
};

#endif /* defined(__LD30Xcode__OBJModel__) */
