#include <dcdr/renderer/MeshGeometry.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/intersect.hpp>

#include <dcdr/logging/Logger.h>

using namespace Dcdr::Renderer;
using namespace Dcdr::Logging;

bool MeshGeometry::intersect(Ray ray, Dcdr::Types::Mat4 objectTransform, IntersectionInfo& intersection) const
{

    bool intersectionDetected = false;

    Types::Real distance = 0;
    Types::Vec3 baryCoords(0);

    size_t nearestTriangle = 0;

    for (size_t i = 0; i < triangles_.size(); ++i)
    {
        Types::Real currentDistance;
        Types::Vec2 currentBaryCoords;

        if (!glm::intersectRayTriangle(
                ray.pos,
                ray.dir,
                Types::Vec3(objectTransform * Types::Vec4(triangles_[i].pos[0], 1.f)),
                Types::Vec3(objectTransform * Types::Vec4(triangles_[i].pos[1], 1.f)),
                Types::Vec3(objectTransform * Types::Vec4(triangles_[i].pos[2], 1.f)),
                currentBaryCoords,
                currentDistance))
        {
            continue;
        }

        if ((!intersectionDetected) || (currentDistance < distance))
        {
            distance = currentDistance;
            baryCoords = Types::Vec3(1 - currentBaryCoords.x - currentBaryCoords.y, currentBaryCoords.x, currentBaryCoords.y);
            nearestTriangle = i;
            intersectionDetected = true;
        }
    }

    if (intersectionDetected)
    {
        intersection.hit = ray.pos + ray.dir * distance;

        intersection.normal =
                Types::Vec3(objectTransform * Types::Vec4(triangles_[nearestTriangle].normal[0], 0.f)) * baryCoords[0] +
                Types::Vec3(objectTransform * Types::Vec4(triangles_[nearestTriangle].normal[1], 0.f)) * baryCoords[1] +
                Types::Vec3(objectTransform * Types::Vec4(triangles_[nearestTriangle].normal[2], 0.f)) * baryCoords[2];

        intersection.uv =
                triangles_[nearestTriangle].uv[0] * baryCoords[0] +
                triangles_[nearestTriangle].uv[1] * baryCoords[1] +
                triangles_[nearestTriangle].uv[2] * baryCoords[2];
    }

    return intersectionDetected;
}

MeshGeometry::MeshGeometry(std::vector<MeshGeometry::Triangle> triangles) :
    triangles_(std::move(triangles)) {}