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
#include "TextFile.h"

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
    
    std::vector<std::string> tokenize(std::string const& line) const;
    void process_line(std::string const& line);
    void process_v(std::vector<std::string> tokens);
    void process_vt(std::vector<std::string> tokens);
    void process_vn(std::vector<std::string> tokens);
    void process_f(std::vector<std::string> tokens);
    void process_g(std::vector<std::string> tokens);
    void process_f_token(std::string const& token, int& v, int& vt, int& vn);
    void new_group(std::string const& name);
    float float_token(std::string const& token);
    int int_token(std::string const& token);
    
public:
    OBJModel(std::string const& filename);
    ~OBJModel();
    
    
};

#endif /* defined(__LD30Xcode__OBJModel__) */
