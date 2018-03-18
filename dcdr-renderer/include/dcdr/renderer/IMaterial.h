#pragma once

#include <memory>

#include <dcdr/Types.h>
#include <dcdr/renderer/ITexture.h>

namespace Dcdr::Renderer
{
    enum class TextureType
    {
        Bump,
        Diffuse,
        Glossiness,
        RefractionGlossiness
    };

    struct MaterialParams
    {
        Types::Real ambient;
        Types::Real diffuse;
        Types::Real reflectance;
        Types::Real glossiness;
        Types::Real refractionGlossiness;
        Types::Real transmittance;
        Types::Real ior;
        Types::Real emittance;
    };

    class IMaterial
    {

    public:
        virtual bool is_texture_assigned(TextureType textureType) = 0;
        virtual const ITexture& get_texture(TextureType textureType) = 0;

        virtual MaterialParams& get_params() = 0;

        virtual ~IMaterial() = default;
    };
}