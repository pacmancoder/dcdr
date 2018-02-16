#include <dcdr/server/Job.h>

using namespace Dcdr::Server;

Job::Job(uint32_t sceneId, uint16_t width, uint16_t height, uint16_t chunkSize) :
    scemeId_(sceneId),
    width_(width),
    height_(height),
    chunkSize_(chunkSize),
    surface_(width, height, chunkSize){}

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
