#pragma once

#include <cstdint>
#include <map>

#include <dcdr/server/core/Surface.h>

#include <dcdr/messaging/commander/CommanderInterconnectTypes.h>

namespace Dcdr::Server
{
    class Job
    {
    public:
        using JobState = Interconnect::Commander::JobState;
        using PropertiesMap = std::map<std::string, std::string>;

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

        void set_property(const std::string& property, const std::string& value);
        void remove_property(const std::string& property);
        const std::string get_property(const std::string& property) const;
        const PropertiesMap& get_all_properties() const;

    private:
        uint32_t scemeId_;
        uint16_t width_;
        uint16_t height_;
        uint16_t chunkSize_;

        JobState state_;

        Surface surface_;

        PropertiesMap properties_;
    };
}