#pragma once

#include <dcdr/Types.h>
#include <dcdr/tracing/Ray.h>
#include <dcdr/utils/Rng.h>
#include <memory>

namespace Dcdr::Scene
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

         Tracing::Ray cast_ray(
                 Types::Real x,
                 Types::Real y,
                 Types::Size width,
                 Types::Size height,
                 Types::Real u,
                 Types::Real v,
                 Utils::Rng& rng
         );

    private:
        Dcdr::Types::Vec3 pos_;
        Dcdr::Types::Vec3 u_, v_, w_;
        Dcdr::Types::Real m_;
        Dcdr::Types::Real focal_distance_;
        Dcdr::Types::Real aperture_radius_;
    };

    typedef std::unique_ptr<Camera> CameraPtr;
    typedef std::unique_ptr<Camera> CameraUniquePtr;
    typedef std::string CameraId;
}