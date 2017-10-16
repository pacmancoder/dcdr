#pragma once
#include <tuple>
#include <cmath>

namespace UMath
{
    template<typename T>
    union Vec3
    {
    public:
        static const size_t ELEMENTS = 3;

        struct
        {
            T x, y, z;
        };
        T data[ELEMENTS];

        Vec3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

        explicit Vec3(T c) : Vec3(c, c, c) {}
        Vec3() : Vec3(0) {};

        Vec3<T> operator+(const Vec3<T> rhs) const { return Vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
        Vec3<T> operator-(const Vec3<T> rhs) const { return Vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
        Vec3<T> operator*(const Vec3<T> rhs) const { return Vec3(x * rhs.x, y * rhs.y, z * rhs.z); }

        /// Vector dot product operator
        T operator%(const Vec3& rhs) { return x * rhs.x + y * rhs.y + z * rhs.z; }

        /// Vector cross product operator
        Vec3<T> operator^(const Vec3& rhs)
        {
            return Vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
        }

        Vec3<T> operator/(T c) const { return Vec3<T>(x / c, y / c, z / c); }
        Vec3<T> operator*(T c) const { return Vec3<T>(x * c, y * c, z * c); }

        bool operator==(const Vec3<T> rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
        bool operator!=(const Vec3<T> rhs) const { return !(rhs == *this); }

        Vec3<T>& operator+=(const Vec3<T> rhs)
        {
            x += rhs.x; y += rhs.y; z += rhs.z;
            return *this;
        }
        Vec3<T>& operator-=(const Vec3<T> rhs)
        {
            x -= rhs.x; y -= rhs.y; z -= rhs.z;
            return *this;
        }
        Vec3<T>& operator*=(const Vec3<T> rhs)
        {
            x *= rhs.x; y *= rhs.y; z *= rhs.z;
            return *this;
        }

        Vec3<T>& operator^=(const Vec3<T> rhs)
        {
            *this = *this ^ rhs;
            return *this;
        }

        Vec3<T>& operator/=(T c)
        {
            x /= c; y /= c; z /= c;
            return *this;
        }
        Vec3<T>& operator*=(T c)
        {
            x *= c; y *= c; z *= c;
            return *this;
        }

        Vec3<T>& normalize() { *this /= len(); }

        T len() const { return std::sqrt(x * x + y * y + z * z); }

        Vec3<T> x_axis() const { return Vec3(x, 0, 0); }
        Vec3<T> y_axis() const { return Vec3(0, y, 0); }
        Vec3<T> z_axis() const { return Vec3(0, 0, z); }
    };

    typedef Vec3<float>  Vec3f;
    typedef Vec3<double> Vec3d;

    template<typename T> Vec3<T> operator*(T c, const Vec3<T>& v) { return v * c; }
}