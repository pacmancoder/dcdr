#pragma once

#include <dcdr/Types.h>

namespace Dcdr::Renderer
{
    class UnbakedPixel
    {
    public:
        UnbakedPixel();

        void add_sample(const Types::Vec3& sample);

        const Types::Vec3& get_color();

        const Types::Vec3& get_variance();

    private:
        Types::Vec3 color_;
        Types::Vec3 variance_;
        Types::Counter samples_;
    };
}