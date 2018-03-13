#pragma once

#include <cstdint>
#include <fstream>
#include <vector>

namespace Dcdr::Worker
{
    class Scene;

    class SceneStorage
    {
    public:
        SceneStorage(const std::string &sceneStoragePath);

        int  start_scene_file_transfer(uint32_t scene, std::string& sceneHash);
        void continue_scene_file_transfer(uint32_t scene, const std::vector<uint32_t> data);
        int  finish_scene_file_transfer(uint32_t scene);

        bool is_scene_loaded(uint32_t scene) const;
        bool is_scene_file_cached(const std::string& sceneHash);
        Scene get_scene(uint32_t scene) const;

    private:
        const std::string &sceneStoragePath_;
    };
}