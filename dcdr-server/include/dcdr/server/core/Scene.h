#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <optional>

namespace Dcdr::Server
{
    /// server scene class should provide minimal scene parsing abilities - read name, width, height and size
    /// TODO: implement actual .dspf (dcdr scene package format) read and parsing
    class Scene
    {
    public:
        Scene(
                const std::string& sceneFileName,
                uint32_t sceneFileId,
                const std::string& name,
                uint16_t width,
                uint16_t height);
        Scene(Scene&& rhs) = default;

        const std::string& get_scene_file_name() const;
        uint32_t get_scene_file_id() const;
        const std::string& get_name() const;

        uint16_t get_width() const;
        uint16_t get_height() const;

    private:
        std::string sceneFileName_;
        uint32_t sceneFileId_;
        std::string name_;
        uint16_t width_;
        uint16_t height_;

    };
}