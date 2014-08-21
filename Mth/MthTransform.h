//
//  MthTransform.h
//  Mth
//
//  Created by Kristof Niederholtmeyer on 31.07.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef Mth_MthTransform_h
#define Mth_MthTransform_h

////////////////////////////////////////////////////////////////////////////////

#include "MthMatrix.h"
#include "MthQuaternion.h"

////////////////////////////////////////////////////////////////////////////////

namespace Mth {
    
////////////////////////////////////////////////////////////////////////////////
    
    // Transformation
    template<typename T>
    Matrix<T, 3, 3> rotation(const Quaternion<T>& q) {
        T d_0_0 = q(0) * q(0);
        T d_0_1 = q(0) * q(1);
        T d_0_2 = q(0) * q(2);
        T d_0_3 = q(0) * q(3);
        
        T d_1_1 = q(1) * q(1);
        T d_1_2 = q(1) * q(2);
        T d_1_3 = q(1) * q(3);
        
        T d_2_2 = q(2) * q(2);
        T d_2_3 = q(2) * q(3);
        
        T d_3_3 = q(3) * q(3);
        return make_matrix(d_0_0 + d_1_1 - d_2_2 - d_3_3, 2 * (d_1_2 - d_0_3),           2 * (d_1_3 + d_0_2),
                           2 * (d_1_2 + d_0_3),           d_0_0 - d_1_1 + d_2_2 - d_3_3, 2 * (d_2_3 - d_0_1),
                           2 * (d_1_3 - d_0_2),           2 * (d_2_3 + d_0_1),           d_0_0 - d_1_1 - d_2_2 + d_3_3);
        
    }
    template<typename T>
    Matrix<T, 4, 4> homogeneous_rotation(const Quaternion<T>& q) {
        T d_0_0 = q(0) * q(0);
        T d_0_1 = q(0) * q(1);
        T d_0_2 = q(0) * q(2);
        T d_0_3 = q(0) * q(3);
        
        T d_1_1 = q(1) * q(1);
        T d_1_2 = q(1) * q(2);
        T d_1_3 = q(1) * q(3);
        
        T d_2_2 = q(2) * q(2);
        T d_2_3 = q(2) * q(3);
        
        T d_3_3 = q(3) * q(3);
        return make_matrix(d_0_0 + d_1_1 - d_2_2 - d_3_3, 2 * (d_1_2 - d_0_3),           2 * (d_1_3 + d_0_2),           T(0),
                           2 * (d_1_2 + d_0_3),           d_0_0 - d_1_1 + d_2_2 - d_3_3, 2 * (d_2_3 - d_0_1),           T(0),
                           2 * (d_1_3 - d_0_2),           2 * (d_2_3 + d_0_1),           d_0_0 - d_1_1 - d_2_2 + d_3_3, T(0),
                           T(0),                          T(0),                          T(0),                          T(1));
    }
    
    
    template<typename T>
    Matrix<T, 4, 4> homogeneous_translation(const CVector<T, 3>& t) {
        return make_matrix(T(1), T(0), T(0), t(0),
                           T(0), T(1), T(0), t(1),
                           T(0), T(0), T(1), t(2),
                           T(0), T(0), T(0), T(1));
    }
    
    template<typename T>
    Matrix<T, 3, 3> scale(const CVector<T, 3>& s) {
        return make_matrix(s(0), T(0), T(0),
                           T(0), s(1), T(0),
                           T(0), T(0), s(2));
    }
    
    template<typename T>
    Matrix<T, 4, 4> homogeneous_scale(const CVector<T, 3>& s) {
        return make_matrix(s(0), T(0), T(0), T(0),
                           T(0), s(1), T(0), T(0),
                           T(0), T(0), s(2), T(0),
                           T(0), T(0), T(0), T(1));
    }
    
    template<typename T>
    CVector<T, 3> transformed_point(const Matrix<T, 4, 4>& transformation, const CVector<T, 3>& point) {
        return make_cvector(transformation(0,0) * point(0) + transformation(0,1) * point(1) + transformation(0,2) * point(2) + transformation(0,3),
                            transformation(1,0) * point(0) + transformation(1,1) * point(1) + transformation(1,2) * point(2) + transformation(1,3),
                            transformation(2,0) * point(0) + transformation(2,1) * point(1) + transformation(2,2) * point(2) + transformation(2,3));
    }
    
    template<typename T>
    CVector<T, 3> transformed_vector(const Matrix<T, 4, 4>& transformation, const CVector<T, 3>& vector) {
        return make_cvector(transformation(0,0) * vector(0) + transformation(0,1) * vector(1) + transformation(0,2) * vector(2),
                            transformation(1,0) * vector(0) + transformation(1,1) * vector(1) + transformation(1,2) * vector(2),
                            transformation(2,0) * vector(0) + transformation(2,1) * vector(1) + transformation(2,2) * vector(2));
    }
    
    template<typename T>
    CVector<T, 3> normalized_device_coordinates(Matrix<T, 4, 4> const& MVP, CVector<T, 3> const& p) {
        CVector<T, 4> ndc = MVP * make_cvector(p(0), p(1), p(2), T(1));
        return make_cvector(ndc(0) / ndc(3), ndc(1) / ndc(3), ndc(2) / ndc(3));
    }
    
////////////////////////////////////////////////////////////////////////////////
    
}

////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////
