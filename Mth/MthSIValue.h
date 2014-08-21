//
//  MthSIValue.h
//  Mth
//
//  Created by Kristof Niederholtmeyer on 20.07.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef Mth_SIValue_h
#define Mth_SIValue_h

////////////////////////////////////////////////////////////////////////////////

namespace Mth {
    
////////////////////////////////////////////////////////////////////////////////
    
    template <class Type, int L, int M, int T, int A>
    class SIValue {
        Type _value;
        
    public:
        SIValue() : _value(0) {}
        SIValue(Type const& v) : _value(v) {}
        
        inline SIValue<Type, L, M, T, A> const& operator += (SIValue<Type, L, M, T, A> const& v) {
            _value += v.value();
            return *this;
        }
        inline SIValue<Type, L, M, T, A> const& operator -= (SIValue<Type, L, M, T, A> const& v) {
            _value -= v.value();
            return *this;
        }
        inline SIValue<Type, L, M, T, A> const& operator *= (Type const& f) {
            _value *= f;
            return *this;
        }
        inline SIValue<Type, L, M, T, A> const& operator /= (Type const& f) {
            _value /= f;
            return *this;
        }
        
        inline Type const& value() const { return _value; }
    }; // SIUnit
    
////////////////////////////////////////////////////////////////////////////////
    
    template <class Type, int L0, int M0, int T0, int A0, int L1, int M1, int T1, int A1>
    inline SIValue<Type, L0+L1, M0+M1, T0+T1, A0+A1> operator * (SIValue<Type, L0, M0, T0, A0> const& v0,
                                                                 SIValue<Type, L1, M1, T1, A1> const& v1) {
        return SIValue<Type, L0+L1, M0+M1, T0+T1, A0+A1>(v0.value() * v1.value());
    }
    template <class Type, int L0, int M0, int T0, int A0, int L1, int M1, int T1, int A1>
    inline SIValue<Type, L0-L1, M0-M1, T0-T1, A0-A1> operator / (SIValue<Type, L0, M0, T0, A0> const& v0,
                                                                 SIValue<Type, L1, M1, T1, A1> const& v1) {
        return SIValue<Type, L0-L1, M0-M1, T0-T1, A0-A1>(v0.value() / v1.value());
    }
    
    template <class Type, int L, int M, int T, int A>
    inline SIValue<Type, L, M, T, A> operator * (SIValue<Type, L, M, T, A> const& v, Type const& f) {
        return SIValue<Type, L, M, T, A>(v.value() * f);
    }
    template <class Type, int L, int M, int T, int A>
    inline SIValue<Type, L, M, T, A> operator * (Type const& f, SIValue<Type, L, M, T, A> const& v) {
        return SIValue<Type, L, M, T, A>(f * v.value());
    }
    template <class Type, int L, int M, int T, int A>
    inline SIValue<Type, L, M, T, A> operator / (SIValue<Type, L, M, T, A> const& v, Type const& f) {
        return SIValue<Type, L, M, T, A>(v.value() / f);
    }
    template <class Type, int L, int M, int T, int A>
    inline SIValue<Type, -L, -M, -T, -A> operator / (Type const& f, SIValue<Type, L, M, T, A> const& v) {
        return SIValue<Type, -L, -M, -T, -A>(f / v.value());
    }
    
    template <class Type, int L, int M, int T, int A>
    inline SIValue<Type, L, M, T, A> operator + (SIValue<Type, L, M, T, A> const& v0,
                                                 SIValue<Type, L, M, T, A> const& v1) {
        return SIValue<Type, L, M, T, A>(v0.value() + v1.value());
    }
    template <class Type, int L, int M, int T, int A>
    inline SIValue<Type, L, M, T, A> operator - (SIValue<Type, L, M, T, A> const& v0,
                                                 SIValue<Type, L, M, T, A> const& v1) {
        return SIValue<Type, L, M, T, A>(v0.value() - v1.value());
    }
    template <class Type, int L, int M, int T, int A>
    inline SIValue<Type, L, M, T, A> operator - (SIValue<Type, L, M, T, A> const& v) {
        return SIValue<Type, L, M, T, A>(-v.value());
    }
    
    template <class Type, int L, int M, int T, int A>
    inline bool operator == (SIValue<Type, L, M, T, A> const& v0,
                             SIValue<Type, L, M, T, A> const& v1) {
        return v0.value() == v1.value();
    }
    template <class Type, int L, int M, int T, int A>
    inline bool operator != (SIValue<Type, L, M, T, A> const& v0,
                             SIValue<Type, L, M, T, A> const& v1) {
        return v0.value() != v1.value();
    }
    template <class Type, int L, int M, int T, int A>
    inline bool operator < (SIValue<Type, L, M, T, A> const& v0,
                            SIValue<Type, L, M, T, A> const& v1) {
        return v0.value() < v1.value();
    }
    template <class Type, int L, int M, int T, int A>
    inline bool operator <= (SIValue<Type, L, M, T, A> const& v0,
                             SIValue<Type, L, M, T, A> const& v1) {
        return v0.value() <= v1.value();
    }
    template <class Type, int L, int M, int T, int A>
    inline bool operator > (SIValue<Type, L, M, T, A> const& v0,
                            SIValue<Type, L, M, T, A> const& v1) {
        return v0.value() > v1.value();
    }
    template <class Type, int L, int M, int T, int A>
    inline bool operator >= (SIValue<Type, L, M, T, A> const& v0,
                             SIValue<Type, L, M, T, A> const& v1) {
        return v0.value() >= v1.value();
    }
    
    template<class Type, int L, int M, int T, int A>
    inline SIValue<Type, L/2, M/2, T/2, A/2> sqrt(SIValue<Type, L, M, T, A> const& v) {
        return SIValue<Type, L/2, M/2, T/2, A/2>(sqrt(v.value()));
    }
    template<class Type, int L, int M, int T, int A>
    inline SIValue<Type, L, M, T, A> cos(SIValue<Type, L, M, T, A> const& v) {
        return SIValue<Type, L, M, T, A>(cos(v.value()));
    }
    template<class Type, int L, int M, int T, int A>
    inline SIValue<Type, L, M, T, A> sin(SIValue<Type, L, M, T, A> const& v) {
        return SIValue<Type, L, M, T, A>(sin(v.value()));
    }
    
    typedef SIValue<float, 1, 0, 0, 0> Length;
    typedef SIValue<float, 0, 0, 0, 1> Angle;
    typedef SIValue<float, 2, 0, 0, 0> Area;
    typedef SIValue<float, 0, 1, 0, 0> Mass;
    typedef SIValue<float, 0,-1, 0, 0> InvMass;
    typedef SIValue<float, 2, 1, 0, 0> Inertia;
    typedef SIValue<float,-2,-1, 0, 0> InvInertia;
    typedef SIValue<float, 0, 0, 1, 0> Time;
    typedef SIValue<float, 0, 0,-1, 0> Frequency;
    typedef SIValue<float, 1, 0,-1, 0> Speed;
    typedef SIValue<float, 0, 0,-1, 1> AngularSpeed;
    typedef SIValue<float, 1, 0,-2, 0> Acceleration;
    typedef SIValue<float, 1, 1,-1, 0> Impuls;
    typedef SIValue<float, 2, 1,-1, 1> AngularImpuls;
    typedef SIValue<float, 1, 1,-2, 0> Force;
    typedef SIValue<float, 2, 1,-2, 0> Torque;
    
    template<typename Type, int L, int M, int T, int A>
    inline Matrix<SIValue<Type, -L, -M, -T, -A>, 3, 3> inverse(Matrix<SIValue<Type, L, M, T, A>, 3, 3> const& m) {
        return make_matrix(m(1,1) * m(2,2) - m(1,2) * m(2,1), m(0,2) * m(2,1) - m(0,1) * m(2,2), m(0,1) * m(1,2) - m(0,2) * m(1,1),
                           m(1,2) * m(2,0) - m(1,0) * m(2,2), m(0,0) * m(2,2) - m(0,2) * m(2,0), m(0,2) * m(1,0) - m(0,0) * m(1,2),
                           m(1,0) * m(2,1) - m(1,1) * m(2,0), m(0,1) * m(2,0) - m(0,0) * m(2,1), m(0,0) * m(1,1) - m(0,1) * m(1,0)) / det(m);
    }
    
    template<class Type, int L, int M, int T, int A, int R, int C>
    inline Matrix<Type, R, C> value(Matrix<SIValue<Type, L, M, T, A>, R, C> const& m) {
        Matrix<Type, R, C> result;
        for (int row = 0; row < R; ++row) {
            for (int col = 0; col < C; ++col) {
                result(row, col) = m(row, col).value();
            }
        }
        return result;
    }
    template<class Type, int L, int M, int T, int A>
    inline Quaternion<Type> value(Quaternion<SIValue<Type, L, M, T, A>> const& q) {
        return Mth::make_quaternion(q(0).value(), q(1).value(), q(2).value(), q(3).value());
    }
    
////////////////////////////////////////////////////////////////////////////////
    
}

////////////////////////////////////////////////////////////////////////////////

#endif /* defined(Mth_SIValue_h) */

////////////////////////////////////////////////////////////////////////////////
