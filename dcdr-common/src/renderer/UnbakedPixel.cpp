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

void UnbakedPixel::combine(const UnbakedPixel &rhs)
{
    // proportional add color
    Types::Real partial_factor = Types::Real(rhs.samples_) / samples_;
    color_ = (color_ * (1 - partial_factor)) + (rhs.color_ * partial_factor);
    // variance could be just added (covariance of 2 samples equals 0, values are independent)
    variance_ = variance_ + rhs.variance_;
    samples_ += rhs.samples_;
}

Types::Vec3 UnbakedPixel::get_color() const
{
    return color_;
}

Types::Vec3 UnbakedPixel::get_variance() const
{
    if (samples_ < 2) return Constants::Color::Black;
    return variance_ / (samples_ - 1);
}

Types::Vec3 UnbakedPixel::get_standard_derivation() const
{
    return get_variance().pow(Types::Real(0.5));
}
