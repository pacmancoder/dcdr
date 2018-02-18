#pragma once

#include <cstdint>

#include <dcdr/server/Surface.h>

namespace Dcdr::Server
{
    class Job
    {
    public:
        Job(uint32_t sceneId, uint16_t width, uint16_t height, uint16_t chunkSize);
        Job(Job&& rhs);

        uint32_t get_scene_id() const;

        uint16_t get_width() const;
        uint16_t get_height() const;
        uint16_t get_chunk_size() const;

        const Surface& get_readonly_surface() const;
        Surface& get_surface();
    private:
        uint32_t scemeId_;
        uint16_t width_;
        uint16_t height_;
        uint16_t chunkSize_;

        Surface surface_;
    };
}