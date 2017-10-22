#include <dcdr/renderer/UnbakedPixel.h>

#include <dcdr/Constants.h>

using namespace Dcdr;
using namespace Dcdr::Renderer;

UnbakedPixel::UnbakedPixel() :
        color_(Constants::Color::Black),
        variance_(Constants::Color::Black),
        samples_(0) {}

void UnbakedPixel::add_sample(const Types::Vec3& sample)
{
    samples_++;
    auto previousValue = color_;
    color_ += (sample - color_) / samples_;
    variance_ += (sample - previousValue) * (sample - color_);
}

const Types::Vec3& UnbakedPixel::get_color()
{
    return color_;
}

const Types::Vec3& UnbakedPixel::get_variance()
{
    if (samples_ < 2) return Constants::Color::Black;
    return variance_;
}
