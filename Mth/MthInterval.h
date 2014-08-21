//
//  MthInterval.h
//  Mth
//
//  Created by Kristof Niederholtmeyer on 22.07.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef Mth_MthInterval_h
#define Mth_MthInterval_h

////////////////////////////////////////////////////////////////////////////////

#include <algorithm>

////////////////////////////////////////////////////////////////////////////////

namespace Mth {
    
////////////////////////////////////////////////////////////////////////////////
    
    template<class T>
    class Interval {
        T _min;
        T _max;
        
    public:
        Interval() : _min(0), _max(0) {}
        Interval(T const& a, T const& b) : _min(std::min(a, b)), _max(std::max(a, b)) {}
        
        T const& min() const { return _min; }
        T const& max() const { return _max; }
    }; // Interval
    
    template<class T>
    inline bool overlapping(Interval<T> const& i0, Interval<T> const& i1) {
        return (i0.min() - i1.max() < T(0)) && (i0.max() - i1.min() > T(0));
    }
    
////////////////////////////////////////////////////////////////////////////////
    
}

////////////////////////////////////////////////////////////////////////////////

#endif
