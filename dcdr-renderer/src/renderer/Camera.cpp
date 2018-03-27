#include <dcdr/renderer/Camera.h>
#include <dcdr/Constants.h>

#include <cmath>

using namespace Dcdr;
using namespace Dcdr::Renderer;

Camera::Camera(
        Types::Vec3 pos,
        Types::Vec3 up,
        Types::Vec3 direction,
        Types::Real fovY,
        Types::Real focalDistance,
        Types::Real apertureRadius)
{
    pos_ = pos;

    w_ = direction;
    u_ = (up ^ w_).normalize();
    v_ = (w_ ^ u_).normalize();

    m_ = Types::Real(1.0 / std::tan(fovY / 2.0));

    focalDistance_ = focalDistance;
    apertureRadius_ = apertureRadius;
}

Types::Vec3 Camera::get_pos() const
{
    return pos_;
}

Ray Camera::cast_ray(
        Types::Real x,
        Types::Real y,
        Types::Size width,
        Types::Size height,
        Types::Real u,
        Types::Real v,
        Utils::Rng& /*rng*/) const
{
    Types::Real aspect = Types::Real(width) / Types::Real(height);
    Types::Real px = ((x + u - Types::Real(0.5)) / (Types::Real(width) - 1)) * 2 - 1;
    Types::Real py = ((y + v - Types::Real(0.5)) / (Types::Real(height) - 1)) * 2 - 1;
    Types::Vec3 rayDir = (u_ * (-px * aspect) + v_ * (-py) + w_ * m_).normalize();
    Types::Vec3 rayPos = pos_;

    /*
    if (apertureRadius_ > 0)
    {
        Types::Vec3 focal_point = pos_ + rayDir * focalDistance_;
        Types::Real angle = rng.generate_real(0.0, 1.0) * 2 * Constants::Math::Pi;
        Types::Real radius = rng.generate_real(0.0, 1.0) * apertureRadius_;
        rayPos += u_ * (std::cos(angle) * radius) + v_ * (std::sin(angle) * radius);
        rayDir = (focal_point - rayPos).normalize();
    }
    */

    return Ray {rayPos, rayDir};
}
