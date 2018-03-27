#pragma once

#include <dcdr/renderer/ITexture.h>

namespace Dcdr::Renderer
{
    class ColorTexture : public ITexture
    {
    public:
        ColorTexture(Types::Color color);

        Types::Color get_color(Types::UVCoord uv) const override;

    private:
        Types::Color color_;
    };
}