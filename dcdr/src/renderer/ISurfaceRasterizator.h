#pragma once

#include <DcdrTypes.h>

namespace Dcdr::Renderer
{
    class ISurfaceRasterizator {
        virtual void set_image_size(Types::Size width, Types::Size height) = 0;
        virtual void draw_pixel(Types::Vec3 color, Types::Offset x, Types::Offset y) = 0;
    };
}