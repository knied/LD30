//
//  MthUtil.h
//  Mth
//
//  Created by Kristof Niederholtmeyer on 20.07.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef Mth_MthUtil_h
#define Mth_MthUtil_h

////////////////////////////////////////////////////////////////////////////////

#include <type_traits>

#include "MthInterval.h"

////////////////////////////////////////////////////////////////////////////////

namespace Mth {
    
////////////////////////////////////////////////////////////////////////////////
    
    double const pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;
    
    template<class T>
    T sqrt(T const& v);
    
    template<class T>
    T cos(T const& v);
    
    template<class T>
    T sin(T const& v);
    
    template<class T>
    T tan(T const& v);
    
    template<class T>
    T acos(T const& v);
    
    template<class T>
    T asin(T const& v);
    
    template<class T>
    T atan(T const& v);
    
    template<class T>
    T atan2(T const& a, T const& b);
    
    template<class T>
    T abs(T const& v);
    
    template<typename T>
    inline constexpr int signum(T x, std::false_type is_signed) {
        return T(0) <= x;
    }
    
    template<typename T>
    inline constexpr int signum(T x, std::true_type is_signed) {
        return (T(0) <= x) - (x < T(0));
    }
    
    template<typename T>
    inline constexpr int signum(T x) {
        return signum(x, std::is_signed<T>());
    }
    
    template<typename T>
    T clamp(T const& v, Interval<T> const& i) {
        return std::min(i.max(), std::max(i.min(), v));
    }
    
////////////////////////////////////////////////////////////////////////////////
    
}

////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////
