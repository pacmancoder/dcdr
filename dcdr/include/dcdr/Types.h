#pragma once

#include <umath/Vec3.h>
#include <cstdint>

namespace Dcdr::Types
{
    typedef float Real;

    typedef unsigned int  Offset;
    typedef int           RelativeOffset;
    typedef unsigned int  Size;
    typedef unsigned long Counter;

    typedef float RealOffset;
    typedef float RealSize;

    typedef UMath::UVec3<Real> Vec3;

    typedef Vec3 Position;
    typedef Vec3 Direction;
    typedef Vec3 Color;

    struct UVCoord
    {
        Real u;
        Real v;
    };
}