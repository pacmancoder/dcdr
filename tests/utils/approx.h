#pragma once
#include <cmath>

namespace TestUtils
{
    /// Compares 2 values approximately, according to delta
    template<typename T> bool CompareApprox(T lhs, T rhs, T dt)
    {
        return std::abs(lhs - rhs) <= dt;
    }
}