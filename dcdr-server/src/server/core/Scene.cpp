#include <dcdr/server/core/Scene.h>

#include <dcdr/server/ServerExceptions.h>

#include <algorithm>

using namespace Dcdr::Server;


Scene::Scene(
        const std::string& sceneFileName,
        uint32_t sceneFileId,
        const std::string& name,
        uint16_t width,
        uint16_t height) :
    sceneFileName_(sceneFileName),
    sceneFileId_(sceneFileId),
    name_(name),
    width_(width),
    height_(height) {}

uint16_t Scene::get_width() const
{
    return width_;
}

uint16_t Scene::get_height() const
{
    return height_;
}

const std::string& Scene::get_scene_file_name() const
{
    return sceneFileName_;
}

uint32_t Scene::get_scene_file_id() const
{
    return sceneFileId_;
}

const std::string& Scene::get_name() const
{
    return name_;
}
