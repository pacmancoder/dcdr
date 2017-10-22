#pragma once

#include <cstring>
#include <algorithm>
#include <umath/Vec3.h>

// TODO: matrix inverse

namespace UMath
{
    template<typename T>
    union UMat4
    {
    public:
        static const size_t ELEMENTS = 16;
        static const size_t ROW_ELEMENTS = 4;
        static const size_t COL_ELEMENTS = 4;

        struct
        {
            T a11, a12, a13, a14,
                    a21, a22, a23, a24,
                    a31, a32, a33, a34,
                    a41, a42, a43, a44;
        };
        T data[COL_ELEMENTS][ROW_ELEMENTS];

    private:
        UMat4()
        { std::memset(data, 0, sizeof(data)); }

        UMat4(const T* buffer)
        { std::memcpy(data, buffer, sizeof(data)); }

    public:

        UMat4<T> operator*(const UMat4<T>& rhs)
        {
            // TODO: SIMD, NEON
            const T buffer[ELEMENTS] = {
                    a11 * rhs.a11 + a21 * rhs.a12 + a31 * rhs.a13 + a41 * rhs.a14,
                    a11 * rhs.a21 + a21 * rhs.a22 + a31 * rhs.a23 + a41 * rhs.a24,
                    a11 * rhs.a31 + a21 * rhs.a32 + a31 * rhs.a33 + a41 * rhs.a34,
                    a11 * rhs.a41 + a21 * rhs.a42 + a31 * rhs.a43 + a41 * rhs.a44,
                    a12 * rhs.a11 + a22 * rhs.a12 + a32 * rhs.a13 + a42 * rhs.a14,
                    a12 * rhs.a21 + a22 * rhs.a22 + a32 * rhs.a23 + a42 * rhs.a24,
                    a12 * rhs.a31 + a22 * rhs.a32 + a32 * rhs.a33 + a42 * rhs.a34,
                    a12 * rhs.a41 + a22 * rhs.a42 + a32 * rhs.a43 + a42 * rhs.a44,
                    a13 * rhs.a11 + a23 * rhs.a12 + a33 * rhs.a13 + a43 * rhs.a14,
                    a13 * rhs.a21 + a23 * rhs.a22 + a33 * rhs.a23 + a43 * rhs.a24,
                    a13 * rhs.a31 + a23 * rhs.a32 + a33 * rhs.a33 + a43 * rhs.a34,
                    a13 * rhs.a41 + a23 * rhs.a42 + a33 * rhs.a43 + a43 * rhs.a44,
                    a14 * rhs.a11 + a24 * rhs.a12 + a34 * rhs.a13 + a44 * rhs.a14,
                    a14 * rhs.a21 + a24 * rhs.a22 + a34 * rhs.a23 + a44 * rhs.a24,
                    a14 * rhs.a31 + a24 * rhs.a32 + a34 * rhs.a33 + a44 * rhs.a34,
                    a14 * rhs.a41 + a24 * rhs.a42 + a34 * rhs.a43 + a44 * rhs.a44,
            };
            return UMat4(buffer);
        }

        bool operator==(const UMat4<T>& rhs) const
        {
            return memcmp(data, rhs.data, sizeof(data)) == 0;
        }

        bool operator!=(const UMat4<T>& rhs) const
        {
            return !(*this == rhs);
        }

        UMat4<T>& transpose()
        {
            std::swap(a21, a12);
            std::swap(a31, a13);
            std::swap(a41, a14);
            std::swap(a32, a23);
            std::swap(a42, a24);
            std::swap(a43, a34);
        }

        UVec3<T> transform_point(UVec3<T> v) const
        {
            T x = a11 * v.x + a21 * v.y + a31 * v.z + a41;
            T y = a12 * v.x + a22 * v.y + a32 * v.z + a42;
            T z = a13 * v.x + a23 * v.y + a33 * v.z + a43;
            T w = a14 * v.x + a24 * v.y + a34 * v.z + a44;

            return UVec3<T>(x / w, y / w, z / w);
        }

        UVec3<T> transform_direction(UVec3<T> v) const
        {
            T x = a11 * v.x + a21 * v.y + a31 * v.z;
            T y = a12 * v.x + a22 * v.y + a32 * v.z;
            T z = a13 * v.x + a23 * v.y + a33 * v.z;
            T w = a14 * v.x + a24 * v.y + a34 * v.z;

            return UVec3<T>(x, y, z);
        }

        static UMat4<T> zero()
        { return UMat4<T>(); }

        static UMat4<T> from_buffer(const T* buffer)
        { return UMat4<T>(buffer); }

        static UMat4<T> identity()
        {
            UMat4 m;
            for (int i = 0; i < COL_ELEMENTS; ++i)
                m.data[i][i] = 1;
            return m;
        }
    };

    typedef UMat4<float> UMat4f;
    typedef UMat4<double> UMat4d;

    // Default matrix type
    typedef UMat4f Mat4;
}

