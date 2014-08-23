//
//  Transformation.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "Transformation.h"
#include <random>


Mth::Matrix<float, 3, 3> transformation(int x, int y) {
    return Mth::make_matrix(1.0f, 0.0f, (float)x,
                            0.0f, 1.0f, (float)y,
                            0.0f, 0.0f, 1.0f);
    
}

Mth::Matrix<float, 3, 3> flip(bool x, bool y) {
    float a = x ? -1.0f : 1.0f;
    float b = y ? -1.0f : 1.0f;
    return Mth::make_matrix(a, 0.0f, 0.0f,
                            0.0f, b, 0.0f,
                            0.0f, 0.0f, 1.0f);
}