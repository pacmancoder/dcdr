#include <dcdr/renderer/Material.h>

using namespace Dcdr::Renderer;

Material::Material(const MaterialParams &params, Material::Textures textures) :
    params_(params), textures_(std::move(textures)) {}

bool Material::is_texture_assigned(TextureType textureType) const
{
    return textures_.find(textureType) != textures_.cend();
}

const ITexture &Material::get_texture(TextureType textureType) const
{
    return *textures_.at(textureType);
}

const MaterialParams &Material::get_params() const
{
    return params_;
}
