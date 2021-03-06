#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <mutex>
#include <dcdr/server/core/Chunk.h>
#include <dcdr/messaging/commander/CommanderInterconnectTypes.h>

namespace Dcdr::Server
{
    using SurfaceFormat = Interconnect::Commander::ArtifactFormat;

    enum class MipmappingTechnique : uint8_t
    {
        Nearest,
    };

    struct SurfaceBuffer
    {
        SurfaceFormat format;
        uint16_t width;
        uint16_t height;
        std::vector<uint8_t> data;
    };

    /// @brief Represents rendering surface, which made of chunks
    /// @remark Class is thread-safe. Chunk read/write implemented
    ///         using COW idiom based on shared_ptr protected with
    ///         atomic_read & atomic_write
    class Surface
    {
    public:
        Surface(uint16_t width, uint16_t height, uint16_t chunkSize);
        Surface(Surface&& rhs);


        ChunkRect next_chunk_to_render();

        SurfaceBuffer get_surface_buffer(
                SurfaceFormat format,
                uint8_t mipmapLevel = 0,
                MipmappingTechnique mipmappingTechnique = MipmappingTechnique::Nearest) const;

        void commit_chunk(const Chunk& chunk);
        const Chunk read_chunk(size_t chunkX, size_t chunkY) const;

    private:
        uint16_t width_;
        uint16_t height_;
        uint16_t chunkSize_;

        uint16_t widthInChunks_;
        uint16_t heightInChunks_;

        uint64_t chunkCounter_;

        std::mutex chunksMutex_;

        std::vector<std::vector<std::shared_ptr<Chunk>>> chunks_;
    };
}