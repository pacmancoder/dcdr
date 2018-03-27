#pragma once

#include <memory>
#include <map>

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

    class Material
    {
    public:
        using Textures = std::map<TextureType, std::shared_ptr<ITexture>>;

    public:
        Material(const MaterialParams& params, Textures textures);

        bool is_texture_assigned(TextureType textureType) const;
        const ITexture& get_texture(TextureType textureType) const;

        const MaterialParams& get_params() const;

    private:
        MaterialParams params_;
        Textures textures_;
    };
}