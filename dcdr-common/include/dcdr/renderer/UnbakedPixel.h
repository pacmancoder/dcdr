#pragma once

#include <dcdr/Types.h>

namespace Dcdr::Renderer
{
    class UnbakedPixel
    {
    public:
        UnbakedPixel();

        void add_sample(const Types::Vec3& sample);

        void combine(const UnbakedPixel &rhs);

        Types::Vec3 get_color() const;

        Types::Vec3 get_variance() const;

        Types::Vec3 get_standard_derivation() const;

    private:
        Types::Vec3 color_;
        Types::Vec3 variance_;
        Types::Counter samples_;
    };
}