#pragma once

#include <dcdr/Types.h>
#include <dcdr/renderer/Ray.h>
#include <dcdr/utils/Rng.h>
#include <memory>

namespace Dcdr::Renderer
{
    class Camera
    {
    public:
        Camera(
                Types::Vec3 center,
                Types::Vec3 eye,
                Types::Vec3 up,
                Types::Real fov_y,
                Types::Vec3 focal_point,
                Types::Real aperture_radius);

         Ray cast_ray(
                 Types::Real x,
                 Types::Real y,
                 Types::Size width,
                 Types::Size height,
                 Types::Real u,
                 Types::Real v,
                 Utils::Rng& rng
         ) const;

        Types::Vec3 get_pos() const;

    private:
        Types::Vec3 pos_;
        Types::Vec3 u_, v_, w_;
        Types::Real m_;
        Types::Real focalDistance_;
        Types::Real apertureRadius_;
    };
}