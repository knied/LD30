//
//  OBJModel.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 21.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "OBJModel.h"
#include <sstream>

OBJModel::OBJModel(std::string const& filename) {
    TextFile file(filename);
    if (file.is_open()) {
        while (!file.end_of_file()) {
            process_line(file.next_line());
        }
    } else {
        std::cout << "ERROR: Unable to open file: " << filename << std::endl;
    }
}

OBJModel::~OBJModel() {
    
}

std::vector<std::string> OBJModel::tokenize(std::string const& line) const {
    std::vector<std::string> tokens;
    std::string current_token;
    for (int i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == ' ' || c == '\t' || c == '\r') {
            if (current_token.length() > 0) {
                tokens.push_back(current_token);
                current_token = "";
            }
        } else if (c == '#') {
            break;
        } else {
            current_token += c;
        }
    }
    if (current_token.length() > 0) {
        tokens.push_back(current_token);
    }
    return tokens;
}

void OBJModel::process_line(std::string const& line) {
    std::vector<std::string> tokens = tokenize(line);
    if (tokens.size() > 0) {
        std::string token = tokens[0];
        tokens.erase(tokens.begin());
        if (token == "v") {
            process_v(tokens);
        } else if (token == "vt") {
            process_vt(tokens);
        } else if (token == "vn") {
            process_vn(tokens);
        } else if (token == "f") {
            process_f(tokens);
        } else if (token == "g") {
            process_g(tokens);
        }
    }
}

void OBJModel::process_v(std::vector<std::string> tokens) {
    if (tokens.size() != 3) {
        std::cout << "WARNING: Unexpected tokens in v command." << std::endl;
        return;
    }
    if (_groups.size() == 0) {
        new_group("");
    }
    Group& group = _groups.back();
    
    group.v.push_back(Mth::make_cvector(float_token(tokens[0]),
                                        float_token(tokens[1]),
                                        float_token(tokens[2])));
}

void OBJModel::process_vt(std::vector<std::string> tokens) {
    if (tokens.size() != 2) {
        std::cout << "WARNING: Unexpected tokens in vt command." << std::endl;
        return;
    }
    if (_groups.size() == 0) {
        new_group("");
    }
    Group& group = _groups.back();
    
    group.vt.push_back(Mth::make_cvector(float_token(tokens[0]),
                                         float_token(tokens[1])));
}

void OBJModel::process_vn(std::vector<std::string> tokens) {
    if (tokens.size() != 3) {
        std::cout << "WARNING: Unexpected tokens in vn command." << std::endl;
        return;
    }
    if (_groups.size() == 0) {
        new_group("");
    }
    Group& group = _groups.back();
    
    group.vn.push_back(Mth::make_cvector(float_token(tokens[0]),
                                        float_token(tokens[1]),
                                        float_token(tokens[2])));
}

void OBJModel::process_f(std::vector<std::string> tokens) {
    if (tokens.size() != 3) {
        std::cout << "WARNING: Unexpected tokens in f command. Only triangles are allowed." << std::endl;
        return;
    }
    if (_groups.size() == 0) {
        new_group("");
    }
    Group& group = _groups.back();
    
    int v0, vt0, vn0;
    process_f_token(tokens[0], v0, vt0, vn0);
    int v1, vt1, vn1;
    process_f_token(tokens[1], v1, vt1, vn1);
    int v2, vt2, vn2;
    process_f_token(tokens[2], v2, vt2, vn2);
    
    if (v0 < 0 || v1 < 0 || v2 < 0) {
        std::cout << "WARNING: Malformed f command." << std::endl;
        return;
    }
    group.fv.push_back(v0);
    group.fv.push_back(v1);
    group.fv.push_back(v2);
    
    if (vt0 >= 0 && vt1 >= 0 && vt2 >= 0) {
        group.fvt.push_back(vt0);
        group.fvt.push_back(vt1);
        group.fvt.push_back(vt2);
    }
    
    if (vn0 >= 0 && vn1 >= 0 && vn2 >= 0) {
        group.fvn.push_back(vn0);
        group.fvn.push_back(vn1);
        group.fvn.push_back(vn2);
    }
}

void OBJModel::process_g(std::vector<std::string> tokens) {
    if (tokens.size() != 1) {
        std::cout << "WARNING: Unexpected tokens in g command." << std::endl;
        return;
    }
    new_group(tokens[0]);
}

void OBJModel::process_f_token(std::string const& token, int& v, int& vt, int& vn) {
    std::vector<std::string> sub_tokens;
    std::string current_sub_token;
    for (int i = 0; i < token.length(); ++i) {
        char c = token[i];
        if (c == '/') {
            sub_tokens.push_back(current_sub_token);
            current_sub_token = "";
        } else {
            current_sub_token += c;
        }
    }
    sub_tokens.push_back(current_sub_token);
    
    if (sub_tokens.size() == 1) {
        v = int_token(sub_tokens[0]);
        vt = -1;
        vn = -1;
    } else if (sub_tokens.size() == 2) {
        v = int_token(sub_tokens[0]);
        vt = int_token(sub_tokens[1]);
        vn = -1;
    } else if (sub_tokens.size() == 3) {
        v = int_token(sub_tokens[0]);
        vt = int_token(sub_tokens[1]);
        vn = int_token(sub_tokens[2]);
    } else {
        std::cout << "WARNING: Unexpected tokens in f subtoken." << std::endl;
        v = -1;
        vt = -1;
        vn = -1;
    }
}

void OBJModel::new_group(std::string const& name) {
    _groups.push_back(Group());
    _groups.back().name = name;
}

float OBJModel::float_token(std::string const& token) {
    std::stringstream ss(token);
    float value = 0.0f;
    ss >> value;
    return value;
}

int OBJModel::int_token(std::string const& token) {
    std::stringstream ss(token);
    int value = 0.0f;
    ss >> value;
    return value;
}
