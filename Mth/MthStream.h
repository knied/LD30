//
//  MthStream.h
//  Mth
//
//  Created by Kristof Niederholtmeyer on 21.07.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef Mth_MthStream_h
#define Mth_MthStream_h

////////////////////////////////////////////////////////////////////////////////

#include <ostream>
#include <iomanip>
#include "MthMatrix.h"
#include "MthSIValue.h"

////////////////////////////////////////////////////////////////////////////////

namespace Mth {
    
////////////////////////////////////////////////////////////////////////////////
    
    template<class T, int R, int C>
    std::ostream& operator << (std::ostream& stream, Matrix<T, R, C> const& m) {
        for (int row = 0; row < R; ++row) {
            for (int col = 0; col < C; ++col) {
                stream << std::setw(10) << std::fixed << std::right << m(row, col);
            }
            stream << std::endl;
        }
        return stream;
    }
    
    template<class Type, int L, int M, int T, int A>
    std::ostream& operator << (std::ostream& stream, SIValue<Type, L, M, T, A> const& v) {
        stream << v.value();
        return stream;
    }
    
////////////////////////////////////////////////////////////////////////////////
    
} // Mth

////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////
