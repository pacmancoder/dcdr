#pragma once

#include <dcdr/Types.h>

namespace Dcdr::Renderer
{

    struct IntersectionInfo
    {
        Dcdr::Types::Vec3 hit;
        Dcdr::Types::Vec3 normal;
        Dcdr::Types::UVCoord uv;

        IntersectionInfo() = default;
        IntersectionInfo(const IntersectionInfo&) = default;

        IntersectionInfo(
                Dcdr::Types::Vec3 hit_,
                Dcdr::Types::Vec3 normal_,
                Dcdr::Types::UVCoord uv_) :
                hit(hit_), normal(normal_), uv(uv_) {}
    };
}