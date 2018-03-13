#include <dcdr/server/core/Scene.h>

#include <dcdr/server/ServerExceptions.h>

#include <algorithm>

using namespace Dcdr::Server;


Scene::Scene(const std::string& path, const std::string& name, uint16_t width, uint16_t height) :
    name_(name),
    width_(width),
    height_(height),
    size_(std::nullopt),
    stream_(path, std::ios::in | std::ios::binary) {}

uint16_t Scene::get_width() const
{
    return width_;
}

uint16_t Scene::get_height() const
{
    return height_;
}

const std::string& Scene::get_name() const
{
    return name_;
}

uint64_t Scene::get_package_size()
{
    if (!size_.has_value())
    {
        stream_.seekg(0, std::ios::end);
        size_ = static_cast<uint64_t>(stream_.tellg());
    }

    return size_.value();
}

std::vector<uint8_t> Scene::get_scene_part(uint64_t offset, uint32_t partSize)
{
    auto size = get_package_size();

    if (offset >= size)
    {
        throw SceneException("Provided offset is bigger than scene size");
    }

    auto bytesToRead = std::min(size - offset, static_cast<uint64_t>(partSize));

    std::vector<uint8_t> buffer;
    buffer.resize(bytesToRead);
    stream_.seekg(offset, std::ios::beg);
    stream_.read(reinterpret_cast<char*>(buffer.data()), buffer.size());

    return buffer;
}
