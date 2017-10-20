#pragma once

#include <umath/Vec3.h>

namespace Dcdr::Types
{
    typedef float Scalar;
    typedef UMath::UVec3<Scalar> Vec3;

    struct UVCoord
    {
        Scalar u;
        Scalar v;
    };
}