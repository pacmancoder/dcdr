#include <dcdr/renderer/UnbakedPixel.h>

#include <dcdr/Constants.h>

using namespace Dcdr;
using namespace Dcdr::Renderer;

UnbakedPixel::UnbakedPixel() :
    color_(Constants::Color::Black),
    variance_(Constants::Color::Black) {}

void UnbakedPixel::add_sample(Types::Vec3 sample) {
    samples_++;
    auto previousValue = color_;
    color_ +=  (sample - color_) / samples_;
    variance_ += (sample - previousValue) * (sample - color_);
}

Types::Vec3 &UnbakedPixel::get_color() {
    return color_;
}

Types::Vec3 &UnbakedPixel::get_variance() {
    if (samples_ < 2) return Constants::Color::Black;
    return variance_;
}
