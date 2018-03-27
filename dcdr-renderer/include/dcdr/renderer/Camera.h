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
                Types::Vec3 pos,
                Types::Vec3 up,
                Types::Vec3 direction,
                Types::Real fovY,
                Types::Real focalDistance,
                Types::Real apertureRadius);

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