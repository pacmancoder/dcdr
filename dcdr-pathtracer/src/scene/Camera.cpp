#include <dcdr/scene/Camera.h>
#include <dcdr/Constants.h>

using namespace Dcdr;
using namespace Dcdr::Scene;

Camera::Camera(
        Types::Vec3 center,
        Types::Vec3 eye,
        Types::Vec3 up,
        Types::Real fov_y,
        Types::Vec3 focal_point,
        Types::Real aperture_radius)
{
    pos_ = eye;

    w_ = (center - eye).normalize();
    u_ = (up ^ w_).normalize();
    v_ = (w_ ^ u_).normalize();

    m_ = Types::Real(1.0 / tan(fov_y * Constants::Math::Pi / 360.0 ));

    focal_distance_ = focal_point.len() * (((focal_point - center).normalize()) % w_);
    aperture_radius_ = aperture_radius;
}

Tracing::Ray Camera::cast_ray(
        Types::Real x,
        Types::Real y,
        Types::Size width,
        Types::Size height,
        Types::Real u,
        Types::Real v,
        Utils::Rng& rng)
{
    Types::Real aspect = Types::Real(width) / Types::Real(height);
    Types::Real px = ((x + u - Types::Real(0.5)) / (Types::Real(width) - 1)) * 2 - 1;
    Types::Real py = ((y + v - Types::Real(0.5)) / (Types::Real(height) - 1)) * 2 - 1;
    Types::Vec3 ray_dir = (u_ * (-px * aspect) + v_ * (-py) + w_ * m_).normalize();
    Types::Vec3 ray_pos = pos_;
    if (aperture_radius_ > 0)
    {
        Types::Vec3 focal_point = pos_ + ray_dir * focal_distance_;
        Types::Real angle = rng.generate_real(0.0, 1.0) * 2 * Constants::Math::Pi;
        Types::Real radius = rng.generate_real(0.0, 1.0) * aperture_radius_;
        ray_pos += u_ * (std::cos(angle) * radius) + v_ * (std::sin(angle) * radius);
        ray_dir = (focal_point - ray_pos).normalize();
    }
    return Tracing::Ray(ray_pos, ray_dir);
}
