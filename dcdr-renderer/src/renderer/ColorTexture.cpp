#include <dcdr/renderer/ColorTexture.h>

using namespace Dcdr::Renderer;

ColorTexture::ColorTexture(Dcdr::Types::Color color) :
    color_(color) {}

Dcdr::Types::Color ColorTexture::get_color(Dcdr::Types::UVCoord) const
{
    return color_;
}
