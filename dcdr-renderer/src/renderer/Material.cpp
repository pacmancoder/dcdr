#include <dcdr/renderer/Material.h>

using namespace Dcdr::Renderer;

Material::Material(const MaterialParams &params, Material::Textures textures) :
    params_(params), textures_(std::move(textures)) {}

bool Material::is_texture_assigned(TextureType textureType) const
{
    auto foundTextureIter = textures_.find(textureType);
    return foundTextureIter != textures_.cend() && foundTextureIter->second != nullptr;
}

const ITexture &Material::get_texture(TextureType textureType) const
{
    return *textures_.at(textureType);
}

const MaterialParams &Material::get_params() const
{
    return params_;
}
