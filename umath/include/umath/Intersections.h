#pragma once

#include <umath/Vec3.h>

namespace UMath::Intersections
{
    template <typename Real>
    Real ray_sphere(
            const UVec3<Real>& ray_origin,
            const UVec3<Real>& ray_dir,
            const UVec3<Real>& sphere_center,
            Real sphere_radius,
            Real epsilon)
    {
        Vec3 k = ray_origin - sphere_center;
        Real b = k % ray_dir;
        Real c = k % k - sphere_radius * sphere_radius;
        Real d = b * b - c;

        if (d > 0)
        {
            d = std::sqrt(d);
            Real t = -b - d;
            if (t <= epsilon)
            {
                t = -b + d;
            }
            if (t <= epsilon)
            {
                return -1;
            }

            return t;
        }

        return -1;
    }
}