#pragma once

#include <cmath>
#include <cstddef>

namespace UMath
{
    template<typename T>
    union UVec3
    {
    public:
        static const size_t ELEMENTS = 3;

#ifdef _MSC_VER
#pragma warning(disable : 4201)
#endif

        struct
        {
            T x, y, z;
        };

        struct
        {
            T r, g, b;
        };

#ifdef _MSC_VER
#pragma warning(default : 4201)
#endif

        T data[ELEMENTS];

        UVec3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

        explicit UVec3(T c) : UVec3(c, c, c) {}

        UVec3() : UVec3(0)
        {};

        UVec3<T> operator+(const UVec3<T> rhs) const
        { return UVec3(x + rhs.x, y + rhs.y, z + rhs.z); }

        UVec3<T> operator-(const UVec3<T> rhs) const
        { return UVec3(x - rhs.x, y - rhs.y, z - rhs.z); }

        UVec3<T> operator*(const UVec3<T> rhs) const
        { return UVec3(x * rhs.x, y * rhs.y, z * rhs.z); }

        /// Vector dot product operator
        T operator%(const UVec3& rhs)
        { return x * rhs.x + y * rhs.y + z * rhs.z; }

        /// Vector cross product operator
        UVec3<T> operator^(const UVec3& rhs)
        {
            return UVec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
        }

        UVec3<T> operator/(T c) const
        { return UVec3<T>(x / c, y / c, z / c); }

        UVec3<T> operator*(T c) const
        { return UVec3<T>(x * c, y * c, z * c); }

        bool operator==(const UVec3<T> rhs) const
        { return x == rhs.x && y == rhs.y && z == rhs.z; }

        bool operator!=(const UVec3<T> rhs) const
        { return !(rhs == *this); }

        UVec3<T> operator-() const
        { return UVec3<T>(0) - *this; }

        UVec3<T>& operator+=(const UVec3<T> rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        UVec3<T>& operator-=(const UVec3<T> rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        UVec3<T>& operator*=(const UVec3<T> rhs)
        {
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            return *this;
        }

        UVec3<T>& operator^=(const UVec3<T> rhs)
        {
            *this = *this ^ rhs;
            return *this;
        }

        UVec3<T>& operator/=(T c)
        {
            x /= c;
            y /= c;
            z /= c;
            return *this;
        }

        UVec3<T>& operator*=(T c)
        {
            x *= c;
            y *= c;
            z *= c;
            return *this;
        }

        UVec3<T>& normalize()
        {
            *this /= len();
            return *this;
        }

        T len() const { return std::sqrt(x * x + y * y + z * z); }

        UVec3<T> pow(T m) const
        {
            return UVec3(std::pow(x, m), std::pow(y, m), std::pow(z, m));
        }

        T mean() const
        {
            return (x + y + z) / 3;
        }

        T max_component() const
        {
            return x > y ? (x > z ? x : z) : (y > z ? y : z);
        }

        UVec3<T> x_axis() const
        { return UVec3(x, 0, 0); }

        UVec3<T> y_axis() const
        { return UVec3(0, y, 0); }

        UVec3<T> z_axis() const
        { return UVec3(0, 0, z); }
    };

    typedef UVec3<float> UVec3f;
    typedef UVec3<double> UVec3d;

    // Default vector type
    typedef UVec3f Vec3;

    template<typename T>
    UVec3<T> operator*(T c, const UVec3<T>& v)
    { return v * c; }
}