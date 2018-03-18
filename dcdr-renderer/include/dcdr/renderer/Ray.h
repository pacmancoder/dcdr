#pragma once

#include <dcdr/Types.h>

namespace Dcdr::Renderer
{
    struct Ray
    {
        Ray(const Types::Vec3& pos_, const Types::Vec3& dir_) : pos(pos_), dir(dir_) {}

        Types::Vec3 pos;
        Types::Vec3 dir;
    };
}