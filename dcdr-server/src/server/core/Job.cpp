#include <dcdr/server/core/Job.h>

using namespace Dcdr::Server;

Job::Job(uint32_t sceneId, uint16_t width, uint16_t height, uint16_t chunkSize) :
    scemeId_(sceneId),
    width_(width),
    height_(height),
    chunkSize_(chunkSize),
    state_(JobState::InProgress),
    surface_(width, height, chunkSize),
    properties_() {}

Job::Job(Job&& rhs) :
    scemeId_(rhs.scemeId_),
    width_(rhs.width_),
    height_(rhs.height_),
    chunkSize_(rhs.chunkSize_),
    state_(rhs.state_),
    surface_(std::move(rhs.surface_)),
    properties_(std::move(rhs.properties_)) {}

uint32_t Job::get_scene_id() const
{
    return scemeId_;
}

uint16_t Job::get_width() const
{
    return width_;
}

uint16_t Job::get_height() const
{
    return height_;
}

uint16_t Job::get_chunk_size() const
{
    return chunkSize_;
}

const Surface& Job::get_readonly_surface() const
{
    return surface_;
}

Surface& Job::get_surface()
{
    return surface_;
}

Job::JobState Job::get_state() const
{
    return state_;
}

void Job::set_state(Job::JobState state)
{
    state_ = state;
}

void Job::set_property(const std::string& property, const std::string& value)
{
    properties_.emplace(property, value);
}

void Job::remove_property(const std::string& property)
{
    properties_.erase(property);
}

const std::string Job::get_property(const std::string& property) const
{
    const auto foundProperty = properties_.find(property);
    if (foundProperty != properties_.cend())
    {
        return foundProperty->second;
    }

    return std::string();
}

const Job::PropertiesMap& Job::get_all_properties() const
{
    return properties_;
}
