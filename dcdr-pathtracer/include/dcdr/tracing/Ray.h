#pragma once

#include <dcdr/Types.h>

namespace Dcdr::Tracing
{
    struct Ray
    {
        Dcdr::Types::Vec3 pos;
        Dcdr::Types::Vec3 dir;

        Ray(Dcdr::Types::Vec3 pos_, Dcdr::Types::Vec3 dir_) : pos(pos_), dir(dir_) {}
    };
}