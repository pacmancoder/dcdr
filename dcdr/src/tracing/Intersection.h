#pragma once

#include <DcdrTypes.h>

namespace Dcdr::Tracing
{
    struct Intersection
    {
        Dcdr::Types::Vec3 hit;
        Dcdr::Types::Vec3 normal;
        Dcdr::Types::Scalar distance;
        Dcdr::Types::UVCoord uv;

        Intersection(
                Dcdr::Types::Vec3 hit_,
                Dcdr::Types::Vec3 normal_,
                Dcdr::Types::Scalar distance_,
                Dcdr::Types::UVCoord uv_) :
                hit(hit_), normal(normal_), distance(distance_), uv(uv_) {}
    };
}