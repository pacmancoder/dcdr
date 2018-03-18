#pragma once

#include <dcdr/Types.h>

namespace Dcdr::Renderer
{
    class Pixel
    {
    public:
        Pixel();

        void add_sample(const Types::Vec3& sample);

        void combine(const Pixel &rhs);

        Types::Vec3 get_color() const;
        Types::Vec3 get_variance() const;
        Types::Vec3 get_standard_derivation() const;
        uint32_t    get_samples() const;


    private:
        Types::Vec3 color_;
        Types::Vec3 variance_;
        uint32_t    samples_;
    };
}