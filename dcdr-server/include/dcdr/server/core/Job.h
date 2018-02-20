#pragma once

#include <cstdint>

#include <dcdr/server/core/Surface.h>

#include <dcdr/messaging/commander/CommanderInterconnectTypes.h>

namespace Dcdr::Server
{
    class Job
    {
    public:
        using JobState = Interconnect::Commander::JobState;

    public:
        Job(uint32_t sceneId, uint16_t width, uint16_t height, uint16_t chunkSize);
        Job(Job&& rhs);

        uint32_t get_scene_id() const;

        uint16_t get_width() const;
        uint16_t get_height() const;
        uint16_t get_chunk_size() const;

        JobState get_state() const;
        void set_state(JobState state);

        const Surface& get_readonly_surface() const;
        Surface& get_surface();
    private:
        uint32_t scemeId_;
        uint16_t width_;
        uint16_t height_;
        uint16_t chunkSize_;

        JobState state_;

        Surface surface_;
    };
}