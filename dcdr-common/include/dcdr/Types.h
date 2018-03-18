#pragma once

#include <umath/Vec3.h>
#include <cstdint>
#include <umath/Mat4.h>

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
    typedef UMath::UMat4<Real> Mat4;

    typedef Vec3 Position;
    typedef Vec3 Direction;
    typedef Vec3 Color;

    struct MultisamplePixel
    {
        MultisamplePixel() : color(), samples(0) {};
        MultisamplePixel(const Vec3& color_, uint32_t samples_) : color(color_), samples(samples_) {}

        bool operator==(const MultisamplePixel& rhs) const
        {
            return color == rhs.color && samples == rhs.samples;
        }

        Vec3 color;
        uint32_t samples;
    };

    struct UVCoord
    {
        UVCoord() = default;
        UVCoord(Real u_, Real v_) : u(u_), v(v_) {};

        Real u;
        Real v;
    };
}