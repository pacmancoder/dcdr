#pragma once

#include <dcdr/renderer/IObjectGeometry.h>
#include <dcdr/Types.h>

#include <vector>
#include <array>

namespace Dcdr::Renderer
{
    class MeshGeometry : public IObjectGeometry
    {
    public:
        struct Triangle
        {
            std::array<Types::Vec3, 3> pos;
            std::array<Types::Vec3, 3> normal;
            std::array<Types::UVCoord, 3> uv;
        };
    public:
        explicit MeshGeometry(std::vector<Triangle> triangles);

        bool intersect(Ray ray, Types::Mat4 objectTransform, IntersectionInfo& intersection) const override;

    private:
        std::vector<Triangle> triangles_;
    };
}