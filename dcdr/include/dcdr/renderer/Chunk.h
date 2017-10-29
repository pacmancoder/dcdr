#pragma once

#include <vector>
#include <mutex>

#include <dcdr/Types.h>
#include <dcdr/renderer/UnbakedPixel.h>
#include <dcdr/renderer/ISampleRenderer.h>

namespace Dcdr::Renderer
{

    // TODO: remove mutex; clone is possible only when not seizured.
    class Chunk
    {
    public:
        Chunk(Types::Offset x, Types::Offset y, Types::Size width, Types::Size height);

        Chunk(const Chunk& rhs);

        void render_chunk(ISampleRenderer& renderer);

        Types::Vec3 get_pixel(Types::Offset x, Types::Offset y);

        Types::Offset get_width();

        Types::Offset get_height();

        Types::Offset get_chunk_pos_x();

        Types::Offset get_chunk_pos_y();


    private:
        void add_sample(Types::Offset x, Types::Offset y, Types::Vec3);


    private:
        Types::Offset global_x_;
        Types::Offset global_y_;
        Types::Size width_;
        Types::Size height_;
        std::vector<UnbakedPixel> pixels_;
    };

}

