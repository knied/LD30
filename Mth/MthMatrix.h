//
//  MthMatrix.h
//  Mth
//
//  Created by Kristof Niederholtmeyer on 20.07.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef Mth_MthMatrix_h
#define Mth_MthMatrix_h

////////////////////////////////////////////////////////////////////////////////

#include "MthUtil.h"
#include <cstring>

////////////////////////////////////////////////////////////////////////////////

namespace Mth {
    
////////////////////////////////////////////////////////////////////////////////
    
    template<class T, int R, int C>
    class Matrix {
        T _cells[R * C];
        
    public:
        // identity matrix
        Matrix() {
            for (int row = 0; row < R; ++row) {
                for (int col = 0; col < C; ++col) {
                    (*this)(row,col) = row == col ? T(1) : T(0);
                }
            }
        }
        // diagonal matrix
        Matrix(T const& d) {
            for (int row = 0; row < R; ++row) {
                for (int col = 0; col < C; ++col) {
                    (*this)(row,col) = row == col ? d : T(0);
                }
            }
        }
        Matrix(T const cells[R * C]) {
            memcpy(_cells, cells, R * C * sizeof(T));
        }
        
        inline T const& operator () (int row, int col) const {
            return _cells[row + R * col];
        }
        inline T& operator () (int row, int col) {
            return _cells[row + R * col];
        }
        
        Matrix<T, 1, C> row(int r) const {
            Matrix<T, 1, C> result;
            for (int col = 0; col < C; ++col) {
                result(0, col) = (*this)(r, col);
            }
            return result;
        }
        Matrix<T, R, 1> col(int c) const {
            Matrix<T, R, 1> result;
            for (int row = 0; row < R; ++row) {
                result(row, 0) = (*this)(row, c);
            }
            return result;
        }
        template<int NR, int NC>
        Matrix<T, NR, NC> sub(int row_offset, int col_offset) const {
            Matrix<T, NR, NC> result;
            for (int row = 0; row < NR; ++row) {
                for (int col = 0; col < NC; ++col) {
                    result(row, col) = (*this)(row_offset + row, col_offset + col);
                }
            }
            return result;
        }
        
        inline Matrix<T, R, C> const& operator += (Matrix<T, R, C> const& m) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] += m._cells[i];
            }
            return *this;
        }
        inline Matrix<T, R, C> const& operator -= (Matrix<T, R, C> const& m) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] -= m._cells[i];
            }
            return *this;
        }
        inline Matrix<T, R, C> const& operator += (T const& s) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] += s;
            }
            return *this;
        }
        inline Matrix<T, R, C> const& operator -= (T const& s) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] -= s;
            }
            return *this;
        }
        template<class U>
        inline Matrix<T, R, C> const& operator *= (U const& s) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] *= s;
            }
            return *this;
        }
        template<class U>
        inline Matrix<T, R, C> const& operator /= (U const& s) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] /= s;
            }
            return *this;
        }
    }; // Matrix
    
////////////////////////////////////////////////////////////////////////////////
    
    template<class T, int C>
    class Matrix<T, 1, C> {
        enum {R = 1};
        
        T _cells[R * C];
        
    public:
        Matrix() {
            for (int row = 0; row < R; ++row) {
                for (int col = 0; col < C; ++col) {
                    (*this)(row,col) = T(0);
                }
            }
        }
        Matrix(T const cells[R * C]) {
            memcpy(_cells, cells, R * C * sizeof(T));
        }
        
        inline T const& operator () (int row, int col) const {
            return _cells[row + R * col];
        }
        inline T& operator () (int row, int col) {
            return _cells[row + R * col];
        }
        inline T const& operator () (int i) const {
            return _cells[i];
        }
        inline T& operator () (int i) {
            return _cells[i];
        }
        
        Matrix<T, 1, C> row(int r) const {
            Matrix<T, 1, C> result;
            for (int col = 0; col < C; ++col) {
                result(0, col) = (*this)(r, col);
            }
            return result;
        }
        Matrix<T, R, 1> col(int c) const {
            Matrix<T, R, 1> result;
            for (int row = 0; row < R; ++row) {
                result(row, 0) = (*this)(row, c);
            }
            return result;
        }
        template<int NR, int NC>
        Matrix<T, NR, NC> sub(int row_offset, int col_offset) const {
            Matrix<T, NR, NC> result;
            for (int row = 0; row < NR; ++row) {
                for (int col = 0; col < NC; ++col) {
                    result(row, col) = (*this)(row_offset + row, col_offset + col);
                }
            }
            return result;
        }
        
        inline Matrix<T, R, C> const& operator += (Matrix<T, R, C> const& m) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] += m._cells[i];
            }
            return *this;
        }
        inline Matrix<T, R, C> const& operator -= (Matrix<T, R, C> const& m) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] -= m._cells[i];
            }
            return *this;
        }
        inline Matrix<T, R, C> const& operator += (T const& s) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] += s;
            }
            return *this;
        }
        inline Matrix<T, R, C> const& operator -= (T const& s) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] -= s;
            }
            return *this;
        }
        template<class U>
        inline Matrix<T, R, C> const& operator *= (U const& s) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] *= s;
            }
            return *this;
        }
        template<class U>
        inline Matrix<T, R, C> const& operator /= (U const& s) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] /= s;
            }
            return *this;
        }
    }; // Matrix
    
////////////////////////////////////////////////////////////////////////////////
    
    template<class T, int R>
    class Matrix<T, R, 1> {
        enum {C = 1};
        
        T _cells[R * C];
        
    public:
        Matrix() {
            for (int row = 0; row < R; ++row) {
                for (int col = 0; col < C; ++col) {
                    (*this)(row,col) = T(0);
                }
            }
        }
        Matrix(T const cells[R * C]) {
            memcpy(_cells, cells, R * C * sizeof(T));
        }
        
        inline T const& operator () (int row, int col) const {
            return _cells[row + R * col];
        }
        inline T& operator () (int row, int col) {
            return _cells[row + R * col];
        }
        inline T const& operator () (int i) const {
            return _cells[i];
        }
        inline T& operator () (int i) {
            return _cells[i];
        }
        
        Matrix<T, 1, C> row(int r) const {
            Matrix<T, 1, C> result;
            for (int col = 0; col < C; ++col) {
                result(0, col) = (*this)(r, col);
            }
            return result;
        }
        Matrix<T, R, 1> col(int c) const {
            Matrix<T, R, 1> result;
            for (int row = 0; row < R; ++row) {
                result(row, 0) = (*this)(row, c);
            }
            return result;
        }
        template<int NR, int NC>
        Matrix<T, NR, NC> sub(int row_offset, int col_offset) const {
            Matrix<T, NR, NC> result;
            for (int row = 0; row < NR; ++row) {
                for (int col = 0; col < NC; ++col) {
                    result(row, col) = (*this)(row_offset + row, col_offset + col);
                }
            }
            return result;
        }
        
        inline Matrix<T, R, C> const& operator += (Matrix<T, R, C> const& m) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] += m._cells[i];
            }
            return *this;
        }
        inline Matrix<T, R, C> const& operator -= (Matrix<T, R, C> const& m) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] -= m._cells[i];
            }
            return *this;
        }
        inline Matrix<T, R, C> const& operator += (T const& s) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] += s;
            }
            return *this;
        }
        inline Matrix<T, R, C> const& operator -= (T const& s) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] -= s;
            }
            return *this;
        }
        template<class U>
        inline Matrix<T, R, C> const& operator *= (U const& s) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] *= s;
            }
            return *this;
        }
        template<class U>
        inline Matrix<T, R, C> const& operator /= (U const& s) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] /= s;
            }
            return *this;
        }
    }; // Matrix
    
////////////////////////////////////////////////////////////////////////////////
    
    template<class T>
    class Matrix<T, 1, 1> {
        enum {R = 1};
        enum {C = 1};
        
        T _cells[R * C];
        
    public:
        Matrix() : _cells{ T(0) } {}
        Matrix(T const& d) : _cells{ d } {}
        Matrix(T const cells[R * C]) {
            memcpy(_cells, cells, R * C * sizeof(T));
        }
        
        inline T const& operator () (int row, int col) const {
            return _cells[row + R * col];
        }
        inline T& operator () (int row, int col) {
            return _cells[row + R * col];
        }
        inline T const& operator () (int i) const {
            return _cells[i];
        }
        inline T& operator () (int i) {
            return _cells[i];
        }
        
        operator T const&() const {
            return _cells[0];
        }
        operator T&() {
            return _cells[0];
        }
        
        Matrix<T, 1, C> row(int r) const {
            return Matrix<T, 1, C>(_cells[0]);
        }
        Matrix<T, R, 1> col(int c) const {
            return Matrix<T, R, 1>(_cells[0]);
        }
        template<int NR, int NC>
        Matrix<T, NR, NC> sub(int row_offset, int col_offset) const {
            Matrix<T, NR, NC> result;
            for (int row = 0; row < NR; ++row) {
                for (int col = 0; col < NC; ++col) {
                    result(row, col) = (*this)(row_offset + row, col_offset + col);
                }
            }
            return result;
        }
        
        inline Matrix<T, R, C> const& operator += (Matrix<T, R, C> const& m) {
            _cells[0] += m._cells[0];
            return *this;
        }
        inline Matrix<T, R, C> const& operator -= (Matrix<T, R, C> const& m) {
            _cells[0] -= m._cells[0];
            return *this;
        }
        inline Matrix<T, R, C> const& operator += (T const& s) {
            _cells[0] += s;
            return *this;
        }
        inline Matrix<T, R, C> const& operator -= (T const& s) {
            _cells[0] -= s;
            return *this;
        }
        template<class U>
        inline Matrix<T, R, C> const& operator *= (U const& s) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] *= s;
            }
            return *this;
        }
        template<class U>
        inline Matrix<T, R, C> const& operator /= (U const& s) {
            for (int i = 0; i < R * C; ++i) {
                _cells[i] /= s;
            }
            return *this;
        }
    }; // Matrix
    
////////////////////////////////////////////////////////////////////////////////
    
    template<class T, int C>
    using RVector = Matrix<T, 1, C>;
    template<class T, int R>
    using CVector = Matrix<T, R, 1>;
    
////////////////////////////////////////////////////////////////////////////////
    
    template<class T>
    inline Matrix<T, 2, 2> make_matrix(T const& m00, T const& m01,
                                       T const& m10, T const& m11) {
        T const tmp[] = { m00, m10, m01, m11 };
        return Matrix<T, 2, 2>(tmp);
    }
    template<class T>
    inline Matrix<T, 3, 3> make_matrix(T const& m00, T const& m01, T const& m02,
                                       T const& m10, T const& m11, T const& m12,
                                       T const& m20, T const& m21, T const& m22) {
        T const tmp[] = { m00, m10, m20, m01, m11, m21, m02, m12, m22 };
        return Matrix<T, 3, 3>(tmp);
    }
    template<class T>
    inline Matrix<T, 4, 4> make_matrix(T const& m00, T const& m01, T const& m02, T const& m03,
                                       T const& m10, T const& m11, T const& m12, T const& m13,
                                       T const& m20, T const& m21, T const& m22, T const& m23,
                                       T const& m30, T const& m31, T const& m32, T const& m33) {
        T const tmp[] = { m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33 };
        return Matrix<T, 4, 4>(tmp);
    }
    template<class T>
    inline Matrix<T, 1, 2> make_rvector(T const& v0, T const& v1) {
        T const tmp[] = { v0, v1 };
        return Matrix<T, 1, 2>(tmp);
    }
    template<class T>
    inline Matrix<T, 1, 3> make_rvector(T const& v0, T const& v1, T const& v2) {
        T const tmp[] = { v0, v1, v2 };
        return Matrix<T, 1, 3>(tmp);
    }
    template<class T>
    inline Matrix<T, 1, 4> make_rvector(T const& v0, T const& v1, T const& v2, T const& v3) {
        T const tmp[] = { v0, v1, v2, v3 };
        return Matrix<T, 1, 4>(tmp);
    }
    template<class T>
    inline Matrix<T, 2, 1> make_cvector(T const& v0, T const& v1) {
        T const tmp[] = { v0, v1 };
        return Matrix<T, 2, 1>(tmp);
    }
    template<class T>
    inline Matrix<T, 3, 1> make_cvector(T const& v0, T const& v1, T const& v2) {
        T const tmp[] = { v0, v1, v2 };
        return Matrix<T, 3, 1>(tmp);
    }
    template<class T>
    inline Matrix<T, 4, 1> make_cvector(T const& v0, T const& v1, T const& v2, T const& v3) {
        T const tmp[] = { v0, v1, v2, v3 };
        return Matrix<T, 4, 1>(tmp);
    }
    
////////////////////////////////////////////////////////////////////////////////
    
    template<class T, int R, int C>
    inline Matrix<T, R, C> operator + (Matrix<T, R, C> const& m0, Matrix<T, R, C> const& m1) {
        Matrix<T, R, C> result(m0);
        result += m1;
        return result;
    }
    template<class T, int R, int C>
    inline Matrix<T, R, C> operator - (Matrix<T, R, C> const& m0, Matrix<T, R, C> const& m1) {
        Matrix<T, R, C> result(m0);
        result -= m1;
        return result;
    }
    template<class T, int R, int C>
    inline Matrix<T, R, C> operator + (Matrix<T, R, C> const& m, T const& s) {
        Matrix<T, R, C> result(m);
        result += s;
        return result;
    }
    template<class T, int R, int C>
    inline Matrix<T, R, C> operator - (Matrix<T, R, C> const& m, T const& s) {
        Matrix<T, R, C> result(m);
        result -= s;
        return result;
    }
    template<class T, int R, int C>
    inline Matrix<T, R, C> operator - (Matrix<T, R, C> const& m) {
        Matrix<T, R, C> result;
        for (int row = 0; row < R; ++row) {
            for (int col = 0; col < C; ++col) {
                result(row, col) = -m(row, col);
            }
        }
        return result;
    }
    
    template<class T0, class T1, int R, int N, int C>
    inline auto operator * (Matrix<T0, R, N> const& m0, Matrix<T1, N, C> const& m1) -> Matrix<decltype(T0() * T1()), R, C> {
        typedef decltype(T0() * T1()) T;
        Matrix<T, R, C> result;
        for (int row = 0; row < R; ++row) {
            for (int col = 0; col < C; ++col) {
                T cell(0);
                for (int i = 0; i < N; ++i) {
                    cell += (m0(row, i) * m1(i, col));
                }
                result(row, col) = cell;
            }
        }
        return result;
    }
    template<class T0, class T1, int R, int C>
    inline auto operator * (Matrix<T0, R, C> const& m, T1 const& s) -> Matrix<decltype(T0() * T1()), R, C> {
        typedef decltype(T0() * T1()) T;
        Matrix<T, R, C> result;
        for (int row = 0; row < R; ++row) {
            for (int col = 0; col < C; ++col) {
                result(row, col) = m(row, col) * s;
            }
        }
        return result;
    }
    template<class T0, class T1, int R, int C>
    inline auto operator * (T0 const& s, Matrix<T1, R, C> const& m) -> Matrix<decltype(T0() * T1()), R, C> {
        typedef decltype(T0() * T1()) T;
        Matrix<T, R, C> result;
        for (int row = 0; row < R; ++row) {
            for (int col = 0; col < C; ++col) {
                result(row, col) = s * m(row, col);
            }
        }
        return result;
    }
    template<class T0, class T1, int R, int C>
    inline auto operator / (Matrix<T0, R, C> const& m, T1 const& s) -> Matrix<decltype(T0() / T1()), R, C> {
        typedef decltype(T0() / T1()) T;
        Matrix<T, R, C> result;
        for (int row = 0; row < R; ++row) {
            for (int col = 0; col < C; ++col) {
                result(row, col) = m(row, col) / s;
            }
        }
        return result;
    }
    
    template<class T, int R, int C>
    inline Matrix<T, C, R> transpose(Matrix<T, R, C> const& m) {
        Matrix<T, C, R> result;
        for (int row = 0; row < R; ++row) {
            for (int col = 0; col < C; ++col) {
                result(col, row) = m(row, col);
            }
        }
        return result;
    }
    
    template<class T0, class T1, int C>
    inline auto dot(Matrix<T0, 1, C> const& m0, Matrix<T1, 1, C> const& m1) -> decltype(T0() * T1()) {
        typedef decltype(T0() * T1()) T;
        T result(0);
        for (int col = 0; col < C; ++col) {
            result += m0(0, col) * m1(0, col);
        }
        return result;
    }
    template<class T0, class T1, int R>
    inline auto dot(Matrix<T0, R, 1> const& m0, Matrix<T1, R, 1> const& m1) -> decltype(T0() * T1()) {
        typedef decltype(T0() * T1()) T;
        T result(0);
        for (int row = 0; row < R; ++row) {
            result += (m0(row, 0) * m1(row, 0));
        }
        return result;
    }
    
    template<class T, int C>
    inline T length(Matrix<T, 1, C> const& m) {
        return sqrt(dot(m, m));
    }
    template<class T, int R>
    inline T length(Matrix<T, R, 1> const& m) {
        return sqrt(dot(m, m));
    }
    
    template<class T0, class T1>
    inline auto cross(Matrix<T0, 1, 3> const& m0, Matrix<T1, 1, 3> const& m1) -> Matrix<decltype(T0() * T1()), 1, 3> {
        return make_rvector(m0(1) * m1(2) - m0(2) * m1(1),
                            m0(2) * m1(0) - m0(0) * m1(2),
                            m0(0) * m1(1) - m0(1) * m1(0));
    }
    template<class T0, class T1>
    inline auto cross(Matrix<T0, 3, 1> const& m0, Matrix<T1, 3, 1> const& m1) -> Matrix<decltype(T0() * T1()), 3, 1> {
        return make_cvector(m0(1) * m1(2) - m0(2) * m1(1),
                            m0(2) * m1(0) - m0(0) * m1(2),
                            m0(0) * m1(1) - m0(1) * m1(0));
    }
    
    template<class T, int C>
    inline auto normal(Matrix<T, 1, C> const& m) -> Matrix<decltype(T() / T()), 1, C> {
        return m / (length(m) + std::numeric_limits<T>::epsilon());
    }
    template<class T, int R>
    inline auto normal(Matrix<T, R, 1> const& m) -> Matrix<decltype(T() / T()), R, 1> {
        return m / (length(m) + std::numeric_limits<T>::epsilon());
    }
    
    template<typename T>
    inline auto det(Matrix<T, 2, 2> const& m) -> decltype(T() * T()) {
        return m(0,0) * m(1,1) - m(1,0) * m(0,1);
    }
    template<typename T>
    inline auto det(Matrix<T, 3, 3> const& m) -> decltype(T() * T() * T()) {
        return   m(0,0) * (m(1,1) * m(2,2) - m(1,2) * m(2,1))
               + m(0,1) * (m(1,2) * m(2,0) - m(1,0) * m(2,2))
               + m(0,2) * (m(1,0) * m(2,1) - m(1,1) * m(2,0));
    }
    template<typename T>
    inline auto det(Matrix<T, 4, 4> const& m) -> decltype(T() * T() * T() * T()) {
        typedef decltype(T() * T()) U;
        U t0 = m(2,2) * m(3,3) - m(3,2) * m(2,3);
        U t1 = m(2,1) * m(3,3) - m(3,1) * m(2,3);
        U t2 = m(2,0) * m(3,3) - m(3,0) * m(2,3);
        U t3 = m(2,1) * m(3,2) - m(3,1) * m(2,2);
        U t4 = m(2,0) * m(3,2) - m(3,0) * m(2,2);
        U t5 = m(2,0) * m(3,1) - m(3,0) * m(2,1);
        return   m(0,0) * (m(1,1) * t0 - m(1,2) * t1 + m(1,3) * t3)
               - m(0,1) * (m(1,0) * t0 - m(1,2) * t2 + m(1,3) * t4)
               + m(0,2) * (m(1,0) * t1 - m(1,1) * t2 + m(1,3) * t5)
               - m(0,3) * (m(1,0) * t3 - m(1,1) * t4 + m(1,2) * t5);
    }
    
    template<typename T>
    inline Matrix<T, 2, 2> inverse(Matrix<T, 2, 2> const& m) {
        return make_matrix(m(1,1), -m(0,1),
                           -m(1,0), m(0,0)) / det(m);
    }
    template<typename T>
    inline Matrix<T, 3, 3> inverse(Matrix<T, 3, 3> const& m) {
        return make_matrix(m(1,1) * m(2,2) - m(1,2) * m(2,1), m(0,2) * m(2,1) - m(0,1) * m(2,2), m(0,1) * m(1,2) - m(0,2) * m(1,1),
                           m(1,2) * m(2,0) - m(1,0) * m(2,2), m(0,0) * m(2,2) - m(0,2) * m(2,0), m(0,2) * m(1,0) - m(0,0) * m(1,2),
                           m(1,0) * m(2,1) - m(1,1) * m(2,0), m(0,1) * m(2,0) - m(0,0) * m(2,1), m(0,0) * m(1,1) - m(0,1) * m(1,0)) / det(m);
    }
    template<typename T>
    inline Matrix<T, 4, 4> inverse(Matrix<T, 4, 4> const& m) {
        typedef decltype(T() * T() * T()) U;
        U m00 =   m(1, 1) * m(2, 2) * m(3, 3)
                - m(1, 1) * m(2, 3) * m(3, 2)
                - m(2, 1) * m(1, 2) * m(3, 3)
                + m(2, 1) * m(1, 3) * m(3, 2)
                + m(3, 1) * m(1, 2) * m(2, 3)
                - m(3, 1) * m(1, 3) * m(2, 2);
        U m10 = - m(1, 0) * m(2, 2) * m(3, 3)
                + m(1, 0) * m(2, 3) * m(3, 2)
                + m(2, 0) * m(1, 2) * m(3, 3)
                - m(2, 0) * m(1, 3) * m(3, 2)
                - m(3, 0) * m(1, 2) * m(2, 3)
                + m(3, 0) * m(1, 3) * m(2, 2);
        U m20 =   m(1, 0) * m(2, 1) * m(3, 3)
                - m(1, 0) * m(2, 3) * m(3, 1)
                - m(2, 0) * m(1, 1) * m(3, 3)
                + m(2, 0) * m(1, 3) * m(3, 1)
                + m(3, 0) * m(1, 1) * m(2, 3)
                - m(3, 0) * m(1, 3) * m(2, 1);
        U m30 = - m(1, 0) * m(2, 1) * m(3, 2)
                + m(1, 0) * m(2, 2) * m(3, 1)
                + m(2, 0) * m(1, 1) * m(3, 2)
                - m(2, 0) * m(1, 2) * m(3, 1)
                - m(3, 0) * m(1, 1) * m(2, 2)
                + m(3, 0) * m(1, 2) * m(2, 1);
        
        U m01 = - m(0, 1) * m(2, 2) * m(3, 3)
                + m(0, 1) * m(2, 3) * m(3, 2)
                + m(2, 1) * m(0, 2) * m(3, 3)
                - m(2, 1) * m(0, 3) * m(3, 2)
                - m(3, 1) * m(0, 2) * m(2, 3)
                + m(3, 1) * m(0, 3) * m(2, 2);
        U m11 =   m(0, 0) * m(2, 2) * m(3, 3)
                - m(0, 0) * m(2, 3) * m(3, 2)
                - m(2, 0) * m(0, 2) * m(3, 3)
                + m(2, 0) * m(0, 3) * m(3, 2)
                + m(3, 0) * m(0, 2) * m(2, 3)
                - m(3, 0) * m(0, 3) * m(2, 2);
        U m21 = - m(0, 0) * m(2, 1) * m(3, 3)
                + m(0, 0) * m(2, 3) * m(3, 1)
                + m(2, 0) * m(0, 1) * m(3, 3)
                - m(2, 0) * m(0, 3) * m(3, 1)
                - m(3, 0) * m(0, 1) * m(2, 3)
                + m(3, 0) * m(0, 3) * m(2, 1);
        U m31 =   m(0, 0) * m(2, 1) * m(3, 2)
                - m(0, 0) * m(2, 2) * m(3, 1)
                - m(2, 0) * m(0, 1) * m(3, 2)
                + m(2, 0) * m(0, 2) * m(3, 1)
                + m(3, 0) * m(0, 1) * m(2, 2)
                - m(3, 0) * m(0, 2) * m(2, 1);

        U m02 =   m(0, 1) * m(1, 2) * m(3, 3)
                - m(0, 1) * m(1, 3) * m(3, 2)
                - m(1, 1) * m(0, 2) * m(3, 3)
                + m(1, 1) * m(0, 3) * m(3, 2)
                + m(3, 1) * m(0, 2) * m(1, 3)
                - m(3, 1) * m(0, 3) * m(1, 2);
        U m12 = - m(0, 0) * m(1, 2) * m(3, 3)
                + m(0, 0) * m(1, 3) * m(3, 2)
                + m(1, 0) * m(0, 2) * m(3, 3)
                - m(1, 0) * m(0, 3) * m(3, 2)
                - m(3, 0) * m(0, 2) * m(1, 3)
                + m(3, 0) * m(0, 3) * m(1, 2);
        U m22 =   m(0, 0) * m(1, 1) * m(3, 3)
                - m(0, 0) * m(1, 3) * m(3, 1)
                - m(1, 0) * m(0, 1) * m(3, 3)
                + m(1, 0) * m(0, 3) * m(3, 1)
                + m(3, 0) * m(0, 1) * m(1, 3)
                - m(3, 0) * m(0, 3) * m(1, 1);
        U m32 = - m(0, 0) * m(1, 1) * m(3, 2)
                + m(0, 0) * m(1, 2) * m(3, 1)
                + m(1, 0) * m(0, 1) * m(3, 2)
                - m(1, 0) * m(0, 2) * m(3, 1)
                - m(3, 0) * m(0, 1) * m(1, 2)
                + m(3, 0) * m(0, 2) * m(1, 1);

        U m03 = - m(0, 1) * m(1, 2) * m(2, 3)
                + m(0, 1) * m(1, 3) * m(2, 2)
                + m(1, 1) * m(0, 2) * m(2, 3)
                - m(1, 1) * m(0, 3) * m(2, 2)
                - m(2, 1) * m(0, 2) * m(1, 3)
                + m(2, 1) * m(0, 3) * m(1, 2);
        U m13 =   m(0, 0) * m(1, 2) * m(2, 3)
                - m(0, 0) * m(1, 3) * m(2, 2)
                - m(1, 0) * m(0, 2) * m(2, 3)
                + m(1, 0) * m(0, 3) * m(2, 3)
                + m(2, 0) * m(0, 2) * m(1, 3)
                - m(2, 0) * m(0, 3) * m(1, 2);
        U m23 = - m(0, 0) * m(1, 1) * m(2, 3)
                + m(0, 0) * m(1, 3) * m(2, 1)
                + m(1, 0) * m(0, 1) * m(2, 3)
                - m(1, 0) * m(0, 3) * m(2, 1)
                - m(2, 0) * m(0, 1) * m(1, 3)
                + m(2, 0) * m(0, 3) * m(1, 1);
        U m33 =   m(0, 0) * m(1, 1) * m(2, 2)
                - m(0, 0) * m(1, 2) * m(2, 1)
                - m(1, 0) * m(0, 1) * m(2, 2)
                + m(1, 0) * m(0, 2) * m(2, 1)
                + m(2, 0) * m(0, 1) * m(1, 2)
                - m(2, 0) * m(0, 2) * m(1, 1);

        typedef decltype(T() * T() * T() * T()) V;
        V det = m(0, 0) * m00 + m(0, 1) * m10 + m(0, 2) * m20 + m(0, 3) * m30;
        return make_matrix(m00, m01, m02, m03,
                           m10, m11, m12, m13,
                           m20, m21, m22, m23,
                           m30, m31, m32, m33) / det;
    }
    
    template<class T>
    Matrix<T, 4, 4> perspective_projection(T const& width, T const& height, T const& field_of_view, T const& znear, T const& zfar) {
        T const aspect = width / height;
        T const h = 1 / tan(field_of_view * pi / 360);
        return make_matrix(h / aspect,  T(0),   T(0),                       T(0),
                           T(0),        h,      T(0),                       T(0),
                           T(0),        T(0),   -(zfar+znear)/(zfar-znear), -2*zfar*znear/(zfar-znear),
                           T(0),        T(0),   -T(1),                      T(0));
    }
    template<class T>
    Matrix<T, 4, 4> perspective_projection(T const& left, T const& right, T const& bottom, T const& top, T const& znear, T const& zfar) {
        return make_matrix(2 * znear / (right - left),  T(0),                       (right + left) / (right - left),    T(0),
                           T(0),                        2 * znear / (top - bottom), (top + bottom) / (top - bottom),    T(0),
                           T(0),                        T(0),                       -(zfar + znear) / (zfar - znear),   -2 * zfar*znear / (zfar - znear),
                           T(0),                        T(0),                       -T(1),                              T(0));
    }
    template<class T>
    Matrix<T, 4, 4> orthogonal_projection(T const& left, T const& right, T const& bottom, T const& top, T const& znear, T const& zfar) {
        return make_matrix(2 / (right - left),  T(0),               T(0),                   -(right + left) / (right - left),
                           T(0),                2 / (top - bottom), T(0),                   -(top + bottom) / (top - bottom),
                           T(0),                T(0),               -2 / (zfar - znear),    -(zfar + znear) / (zfar - znear),
                           T(0),                T(0),               T(0),                   T(1));
    }
    template<class T>
    Matrix<T, 4, 4> orthogonal_projection(T const& width, T const& height, T const& znear, T const& zfar) {
        return orthogonal_projection(-width/2, width/2, -height/2, height/2, znear, zfar);
    }
    template<class T>
    Matrix<T, 3, 3> normal_matrix(Matrix<T, 4, 4> const& mv) {
        Matrix<T, 4, 4> tmp = transpose(inverse(mv));
        return tmp.template sub<3, 3>(0, 0);
    }
    
    // TODO: make sure this works as intended.
    // see also: make_quaternion()
    template<class T>
    Matrix<T, 4, 4> look_at_matrix(CVector<T, 3> const& eye, CVector<T, 3> const& at, CVector<T, 3> const& up) {
        CVector<T, 3> zaxis = normal(at - eye);
        CVector<T, 3> xaxis = normal(cross(up, zaxis));
        CVector<T, 3> yaxis = cross(zaxis, xaxis);
        
        return make_matrix(xaxis(0), xaxis(1), xaxis(2), -dot(xaxis, eye),
                           yaxis(0), yaxis(1), yaxis(2), -dot(yaxis, eye),
                           zaxis(0), zaxis(1), zaxis(2), -dot(zaxis, eye),
                           T(0), T(0), T(0), T(1));
    }
    
////////////////////////////////////////////////////////////////////////////////
    
} // Mth

////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////
