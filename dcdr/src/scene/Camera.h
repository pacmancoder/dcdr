#pragma once

#include <dcdr/Types.h>

namespace Dcdr::Scene
{
    class Camera
    {
    public:
        Camera(Dcdr::Types::Vec3 pos, Dcdr::Types::Vec3 dir, Types::Real fov) :
                pos_(pos), dir_(dir), fov_(fov) {}

        const Dcdr::Types::Vec3& get_pos()
        {
            return pos_;
        }

        const Dcdr::Types::Vec3& get_dir()
        {
            return dir_;
        }

        const Dcdr::Types::Real get_fow()
        {
            return fov_;
        }

    private:
        Dcdr::Types::Vec3 pos_;
        Dcdr::Types::Vec3 dir_;

        Dcdr::Types::Real fov_;
    };
}