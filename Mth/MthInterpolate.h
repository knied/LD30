//
//  MthInterpolate.h
//  Mth
//
//  Created by Kristof Niederholtmeyer on 29.07.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef Mth_MthInterpolate_h
#define Mth_MthInterpolate_h

////////////////////////////////////////////////////////////////////////////////

#include "MthUtil.h"

////////////////////////////////////////////////////////////////////////////////

namespace Mth {
    
////////////////////////////////////////////////////////////////////////////////
    
    template <typename T>
    T linear_interpolation(T const& p0,
                           T const& p1,
                           float t) {
        return p0 + (p1 - p0) * t;
    }
    
    template <typename T>
    T linear_interpolation_dir(T const& p0,
                               T const& p1,
                               float t) {
        return p1 - p0;
    }
    
    template <typename T>
    T quadratic_interpolation(T const& p0,
                              T const& p1,
                              T const& p2,
                              float t) {
        return (1.0f - t) * ((1.0f - t) * p0 + 2.0f * t * p1) + t * t * p2;
    }
    
    template <typename T>
    T quadratic_interpolation_dir(T const& p0,
                                  T const& p1,
                                  T const& p2,
                                  float t) {
        return 2.0f * (1.0f - t) * (p1 - p0) + 2.0f * t * (p2 - p1);
    }
    
    template<typename T>
    T cubic_interpolation(T const& p0,
                          T const& p1,
                          T const& p2,
                          T const& p3,
                          float t) {
        return (1.0f - t) * ((1.0f - t) * ((1.0f - t) * p0 + 3.0f * t * p1) + 3.0f * t * t * p2) + t * t * t * p3;
    }
    
    template<typename T>
    T cubic_interpolation_dir(T const& p0,
                              T const& p1,
                              T const& p2,
                              T const& p3,
                              float t) {
        return 3.0f * ((1.0f - t) * ((1.0f - t) * (p1 - p0) + 2.0f * t * (p2 - p1)) + t * t * (p3 - p2));
    }
    
    template<typename T>
    Quaternion<T> spherical_linear_interpolation(Quaternion<T> const& q0,
                                                 Quaternion<T> const& q1,
                                                 float t) {
        T d = dot(q0, q1);
        T sign = signum(d);
        d = sign * d;
        if (d < 0.95) {
            T angle = acos(d);
            return (q0 * sin(angle * (1.0f - t)) + sign * q1 * sin(angle * t)) / sin(angle);
        }
        return linear_interpolation(q0, sign * q1, t);
    }
    
////////////////////////////////////////////////////////////////////////////////
    
}

////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////
