#include <dcdr/server/Scene.h>

#include <dcdr/server/ServerExceptions.h>

#include <ratio>

using namespace Dcdr::Server;

namespace
{
    struct SceneInfo
    {
        std::string name;
        uint16_t width;
        uint16_t height;
        uint64_t size;
    };

    SceneInfo sceneInfo[] = {
            SceneInfo {"Cornell", 640, 480, 1 * 1024 * 1024},
            SceneInfo {"Spheres", 800, 600, 1 * 512  * 1024},
    };

    size_t fake_scene_index(const std::string& path)
    {
        if (path.find("cornell.dspf") != std::string::npos)
        {
            return 0;
        }

        return 1;
    }
}

Scene::Scene(const std::string& path) :
    name_(sceneInfo[fake_scene_index(path)].name),
    width_(sceneInfo[fake_scene_index(path)].width),
    height_(sceneInfo[fake_scene_index(path)].height),
    size_(sceneInfo[fake_scene_index(path)].size) {}

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

uint64_t Scene::get_package_size() const
{
    return size_;
}

std::vector<uint8_t> Scene::get_scene_part(uint64_t offset, uint32_t partSize) const
{
    if (offset >= size_)
    {
        throw SceneException("Provided offset is bigger than scene size");
    }
    if (offset + partSize > size_)
    {
        return std::vector<uint8_t>(size_ - offset);
    }

    return std::vector<uint8_t>(partSize);
}
