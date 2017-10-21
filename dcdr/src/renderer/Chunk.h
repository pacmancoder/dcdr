#pragma once

#include <vector>
#include <mutex>

#include <DcdrTypes.h>
#include <renderer/UnbakedPixel.h>
#include <renderer/IChunkRenderer.h>

namespace Dcdr::Renderer
{

    // TODO: remove mutex; clone is possible only when not seizured.
    class Chunk {
    public:
        Chunk(Types::Offset x, Types::Offset y, Types::Size width, Types::Size height);
        Chunk(const Chunk& rhs);

        void render_chunk(IChunkRenderer& renderer);

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

