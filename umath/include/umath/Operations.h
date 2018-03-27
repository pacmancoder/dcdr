#pragma once

#include <umath/Vec3.h>

namespace UMath
{
    template <typename Real>
    Real clamp(Real value, Real min, Real max)
    {
        if (value < min)
        {
            return min;
        }
        if (value > max)
        {
            return max;
        }

        return value;
    }

    template<typename T>
    UVec3<T> clamp(UVec3<T> value, UVec3<T> min, UVec3<T> max)
    {
        return UVec3<T>(
                clamp(value.x, min.x, max.x),
                clamp(value.y, min.y, max.y),
                clamp(value.z, min.z, max.z));
    }
}