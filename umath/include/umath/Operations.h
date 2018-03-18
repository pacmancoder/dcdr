#pragma once

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
}