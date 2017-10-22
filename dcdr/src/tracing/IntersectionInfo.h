#pragma once

#include <dcdr/Types.h>

namespace Dcdr::Tracing
{

    struct IntersectionInfo
    {
        Dcdr::Types::Vec3 hit;
        Dcdr::Types::Vec3 normal;
        Dcdr::Types::Real distance;
        Dcdr::Types::UVCoord uv;

        IntersectionInfo(
                Dcdr::Types::Vec3 hit_,
                Dcdr::Types::Vec3 normal_,
                Dcdr::Types::Real distance_,
                Dcdr::Types::UVCoord uv_) :
                hit(hit_), normal(normal_), distance(distance_), uv(uv_) {}
    };
}