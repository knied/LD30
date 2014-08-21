//
//  MthQuaternion.h
//  Mth
//
//  Created by Kristof Niederholtmeyer on 28.07.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef Mth_MthQuaternion_h
#define Mth_MthQuaternion_h

#include "MthUtil.h"
#include "MthMatrix.h"

namespace Mth {
    
    template<class T>
    class Quaternion {
        T _cells[4];
        
    public:
        Quaternion()
        : _cells{ T(1), T(0), T(0), T(0) } {}
        Quaternion(T const& a, T const& b, T const& c, T const& d)
        : _cells{ a, b, c, d } {}
        
        inline T const& operator() (int i) const { return _cells[i]; }
        inline T& operator() (int i) { return _cells[i]; }
        
        Quaternion<T> const& operator += (Quaternion<T> const& q) {
            _cells[0] += q(0);
            _cells[1] += q(1);
            _cells[2] += q(2);
            _cells[3] += q(3);
            return *this;
        }
        Quaternion<T> const& operator -= (Quaternion<T> const& q) {
            _cells[0] -= q(0);
            _cells[1] -= q(1);
            _cells[2] -= q(2);
            _cells[3] -= q(3);
            return *this;
        }
        
        Quaternion<T> const& operator *= (Quaternion<T> const& q) {
            T x = _cells[1], y = _cells[2], z = _cells[3], sn = _cells[0] * q(0) - (_cells[1] * q(1) + _cells[2] * q(2) + _cells[3] * q(3));
            _cells[1] = y * q(3) - z * q(2) + _cells[0] * q(1) + x * q(0);
            _cells[2] = z * q(1) - x * q(3) + _cells[0] * q(2) + y * q(0);
            _cells[3] = x * q(2) - y * q(1) + _cells[0] * q(3) + z * q(0);
            _cells[0] = sn;
            return *this;
        }
        
        Quaternion<T> const& operator *= (T const& s) {
            _cells[0] *= s;
            _cells[1] *= s;
            _cells[2] *= s;
            _cells[3] *= s;
            return *this;
        }
        Quaternion<T> const& operator /= (T const& s) {
            _cells[0] /= s;
            _cells[1] /= s;
            _cells[2] /= s;
            _cells[3] /= s;
            return *this;
        }
    }; // Quaternion
    
    template<class T>
    inline Quaternion<T> make_quaternion(T const& a, T const& b, T const& c, T const& d) {
        return Quaternion<T>(a, b, c, d);
    }
    template<class T, class A>
    inline Quaternion<A> make_quaternion(CVector<T, 3> const& axis, A const& angle) {
        CVector<T, 3> n = normal(axis);
        A cos_angle_2 = cos(angle * 0.5f);
        A sin_angle_2 = sin(angle * 0.5f);
        return Quaternion<A>(cos_angle_2,
                             sin_angle_2 * n(0),
                             sin_angle_2 * n(1),
                             sin_angle_2 * n(2));
    }
    template<class T>
    inline Quaternion<T> make_quaternion(CVector<T, 3> const& euler) {
        T cos_z_2 = cos(0.5 * euler(2));
        T cos_y_2 = cos(0.5 * euler(1));
        T cos_x_2 = cos(0.5 * euler(0));
        
        T sin_z_2 = sin(0.5 * euler(2));
        T sin_y_2 = sin(0.5 * euler(1));
        T sin_x_2 = sin(0.5 * euler(0));
        
        return Quaternion<T>(cos_z_2 * cos_y_2 * cos_x_2 + sin_z_2 * sin_y_2 * sin_x_2,
                             cos_z_2 * cos_y_2 * sin_x_2 - sin_z_2 * sin_y_2 * cos_x_2,
                             cos_z_2 * sin_y_2 * cos_x_2 + sin_z_2 * cos_y_2 * sin_x_2,
                             sin_z_2 * cos_y_2 * cos_x_2 - cos_z_2 * sin_y_2 * sin_x_2);
    }
    // TODO: make sure this works as intended.
    // see also: look_at_matrix()
    template<class T>
    inline Quaternion<T> make_quaternion(CVector<T, 3> const& eye, CVector<T, 3> const& at, CVector<T, 3> const& up) {
        CVector<T, 3> z = normal(at - eye);
        CVector<T, 3> x = normal(cross(up, z));
        CVector<T, 3> y = normal(cross(z, x));
        
        T w = sqrt(T(1) + x(0) + y(1) + z(2)) * 0.5;
        T w4_recip = T(1) / (4 * w);
        return Quaternion<T>(w,
                             (y(2) - z(1)) * w4_recip,
                             (z(0) - x(2)) * w4_recip,
                             (x(1) - y(0)) * w4_recip);
    }
    
    template<typename T>
    inline Quaternion<T> operator + (Quaternion<T> const& q0, Quaternion<T> const& q1) {
        return Quaternion<T>(q0(0) + q1(0), q0(1) + q1(1), q0(2) + q1(2), q0(3) + q1(3));
    }
    
    template<typename T>
    inline Quaternion<T> operator - (Quaternion<T> const& q0, Quaternion<T> const& q1) {
        return Quaternion<T>(q0(0) - q1(0), q0(1) - q1(1), q0(2) - q1(2), q0(3) - q1(3));
    }
    
    template<class T0, class T1>
    inline auto operator * (Quaternion<T0> const& q0, Quaternion<T1> const& q1) -> Quaternion<decltype(T0() * T1())> {
        return make_quaternion(q0(0) * q1(0) - q0(1) * q1(1) - q0(2) * q1(2) - q0(3) * q1(3),
                               q0(2) * q1(3) - q0(3) * q1(2) + q0(0) * q1(1) + q0(1) * q1(0),
                               q0(3) * q1(1) - q0(1) * q1(3) + q0(0) * q1(2) + q0(2) * q1(0),
                               q0(1) * q1(2) - q0(2) * q1(1) + q0(0) * q1(3) + q0(3) * q1(0));
    }
    
    template<class T0, class T1>
    inline auto operator * (Quaternion<T0> const& q, T1 const& s) -> Quaternion<decltype(T0() * T1())> {
        return make_quaternion(q(0) * s, q(1) * s, q(2) * s, q(3) * s);
    }
    
    template<class T0, class T1>
    inline auto operator * (T0 const& s, Quaternion<T1> const& q) -> Quaternion<decltype(T0() * T1())> {
        return make_quaternion(q(0) * s, q(1) * s, q(2) * s, q(3) * s);
    }
    
    template<class T0, class T1>
    inline auto operator / (Quaternion<T0> const& q, T1 const& s) -> Quaternion<decltype(T0() / T1())> {
        return make_quaternion(q(0) / s, q(1) / s, q(2) / s, q(3) / s);
    }
    
    template<typename T>
    inline T dot(Quaternion<T> const& q0, Quaternion<T> const& q1) {
        return q0(0) * q1(0) + q0(1) * q1(1) + q0(2) * q1(2) + q0(3) * q1(3);
    }
    
    template<typename T>
    inline T length(Quaternion<T> const& q) {
        return sqrt(dot(q, q));
    }
    
    template<typename T>
    inline Quaternion<T> normal(Quaternion<T> const& q) {
        return q / (length(q) + std::numeric_limits<T>::epsilon());
    }
    
    template<typename T>
    inline Quaternion<T> conjugate(Quaternion<T> const& q) {
        return Quaternion<T>(q(0), -q(1), -q(2), -q(3));
    }
    
    template<typename T>
    inline Quaternion<T> inverse(Quaternion<T> const& q) {
        return conjugate(q) / (dot(q, q) + std::numeric_limits<T>::epsilon());
    }
    
    template<typename T>
    inline CVector<T, 3> rotate(Quaternion<T> const& q, CVector<T, 3> const& v) {
        Quaternion<T> V(T(0), v(0), v(1), v(2));
        Quaternion<T> result = q * V * conjugate(q);
        return make_cvector(result(1), result(2), result(3));
    }
    
    template<typename T>
    inline CVector<T, 3> euler(Quaternion<T> const& q) {
        T square_w = q(0) * q(0);
        T square_x = q(1) * q(1);
        T square_y = q(2) * q(2);
        T square_z = q(3) * q(3);
        return CVector<T, 3>(atan2(T(2) * (q(2) * q(3) + q(0) * q(1)), square_z - square_y - square_x + square_w),
                             asin(T(2) * (q(0) * q(2) - q(1) * q(3))),
                             atan2(T(2) * (q(1) * q(2) + q(0) * q(3)), square_x + square_w - square_z - square_y));
    }
    
    template<typename T>
    inline CVector<T, 3> axis(Quaternion<T> const& q) {
        T k = T(1) / sin(acos(q(0)));
        return CVector<T, 3>(q(1) * k, q(2) * k, q(3) * k);
    }
    
    template<typename T>
    inline T angle(Quaternion<T> const& q) {
        return acos(q(0)) * T(2);
    }
    
} // Mth

#endif
