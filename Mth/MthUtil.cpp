//
//  MthUtil.cpp
//  Mth
//
//  Created by Kristof Niederholtmeyer on 20.07.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "MthUtil.h"
#include <math.h>

////////////////////////////////////////////////////////////////////////////////

namespace Mth {
    
////////////////////////////////////////////////////////////////////////////////
    
    template<>
    float sqrt<float> (float const& v) {
        return ::sqrtf(v);
    }
    template<>
    double sqrt<double> (double const& v) {
        return ::sqrt(v);
    }
    template<>
    long double sqrt<long double> (long double const& v) {
        return ::sqrtl(v);
    }
    
    template<>
    float cos<float> (float const& v) {
        return ::cosf(v);
    }
    template<>
    double cos<double> (double const& v) {
        return ::cos(v);
    }
    template<>
    long double cos<long double> (long double const& v) {
        return ::cosl(v);
    }
    
    template<>
    float sin<float> (float const& v) {
        return ::sinf(v);
    }
    template<>
    double sin<double> (double const& v) {
        return ::sin(v);
    }
    template<>
    long double sin<long double> (long double const& v) {
        return ::sinl(v);
    }
    
    template<>
    float tan<float> (float const& v) {
        return ::tanf(v);
    }
    template<>
    double tan<double> (double const& v) {
        return ::tan(v);
    }
    template<>
    long double tan<long double> (long double const& v) {
        return ::tanl(v);
    }
    
    template<>
    float acos<float> (float const& v) {
        return ::acosf(v);
    }
    template<>
    double acos<double> (double const& v) {
        return ::acos(v);
    }
    template<>
    long double acos<long double> (long double const& v) {
        return ::acosl(v);
    }
    
    template<>
    float asin<float> (float const& v) {
        return ::asinf(v);
    }
    template<>
    double asin<double> (double const& v) {
        return ::asin(v);
    }
    template<>
    long double asin<long double> (long double const& v) {
        return ::asinl(v);
    }
    
    template<>
    float atan<float> (float const& v) {
        return ::atanf(v);
    }
    template<>
    double atan<double> (double const& v) {
        return ::atan(v);
    }
    template<>
    long double atan<long double> (long double const& v) {
        return ::atanl(v);
    }
    
    template<>
    float atan2<float> (float const& a, float const& b) {
        return ::atan2f(a, b);
    }
    template<>
    double atan2<double> (double const& a, double const& b) {
        return ::atan2(a, b);
    }
    template<>
    long double atan2<long double> (long double const& a, long double const& b) {
        return ::atan2l(a, b);
    }
    
    template<>
    float abs<float>(float const& v) {
        return ::fabsf(v);
    }
    template<>
    double abs<double>(double const& v) {
        return ::fabs(v);
    }
    template<>
    long double abs<long double>(long double const& v) {
        return ::fabsl(v);
    }
    
////////////////////////////////////////////////////////////////////////////////
    
}

////////////////////////////////////////////////////////////////////////////////
