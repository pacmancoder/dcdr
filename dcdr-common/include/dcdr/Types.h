#pragma once

#include <glm/ext.hpp>

#include <cstdint>

namespace Dcdr::Types
{
    typedef float Real;

    typedef unsigned int Offset;
    typedef int RelativeOffset;
    typedef unsigned int Size;
    typedef unsigned long Counter;

    typedef float RealOffset;
    typedef float RealSize;

    typedef glm::vec2 Vec2;
    typedef glm::vec3 Vec3;
    typedef glm::vec4 Vec4;
    typedef glm::mat4 Mat4;

    typedef Vec3 Position;
    typedef Vec3 Direction;
    typedef Vec3 Color;
    typedef Vec2 UVCoord;


    struct MultisamplePixel
    {
        MultisamplePixel() : color(), samples(0) {};
        MultisamplePixel(const Vec3& color_, uint32_t samples_) : color(color_), samples(samples_) {}

        bool operator==(const MultisamplePixel& rhs) const
        {
            return color == rhs.color && samples == rhs.samples;
        }

        Vec3 color;
        uint32_t samples;
    };
}