#pragma once

#include <umath/Vec3.h>
#include <cstdint>

namespace Dcdr::Types
{
    typedef float Real;

    typedef unsigned int Offset;
    typedef int RelativeOffset;
    typedef unsigned int Size;
    typedef unsigned long Counter;

    typedef float RealOffset;
    typedef float RealSize;

    typedef UMath::UVec3<Real> Vec3;

    typedef Vec3 Position;
    typedef Vec3 Direction;
    typedef Vec3 Color;

    struct MultisamplePixel
    {
        Vec3 color;
        uint32_t samples;

        bool operator==(const MultisamplePixel& rhs) const
        {
            return color == rhs.color && samples == rhs.samples;
        }
    };

    struct UVCoord
    {
        Real u;
        Real v;

        UVCoord() : u(0), v(0) {};
        UVCoord(Real c) : u(c), v(c) {};
        UVCoord(Real u_, Real v_) : u(u_), v(v_) {};
    };
}