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
        Scene(const std::string& path, const std::string& name, uint16_t width, uint16_t height);
        Scene(Scene&& rhs) = default;

        const std::string& get_name() const;

        uint16_t get_width() const;
        uint16_t get_height() const;

        uint64_t get_package_size();

        std::vector<uint8_t> get_scene_part(uint64_t offset, uint32_t partSize);

    private:
        std::string name_;
        uint16_t width_;
        uint16_t height_;
        std::optional<uint64_t> size_;

        std::ifstream stream_;
    };
}