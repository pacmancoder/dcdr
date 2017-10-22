#pragma once

#include <dcdr/Types.h>

namespace Dcdr::Renderer
{
    class UnbakedPixel
    {
    public:
        UnbakedPixel();

        void add_sample(Types::Vec3 sample);

        Types::Vec3& get_color();
        Types::Vec3& get_variance();

    private:
        Types::Counter samples_;
        Types::Vec3 color_;
        Types::Vec3 variance_;
    };
}