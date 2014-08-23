//
//  Transformation.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef __LD30Xcode__Transformation__
#define __LD30Xcode__Transformation__

#include <iostream>
#include "MthMatrix.h"

Mth::Matrix<float, 3, 3> transformation(int x, int y);
Mth::Matrix<float, 3, 3> flip(bool x, bool y);

#endif /* defined(__LD30Xcode__Transformation__) */
