#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace Dcdr::Server
{
    /// server scene class should provide minimal scene parsing abilities - read name, width, height and size
    /// TODO: implement actual .dspf (dcdr scene package format) read and parsing
    class Scene
    {
    public:
        Scene(const std::string& path);
        Scene(Scene&& rhs) = default;

        const std::string& get_name() const;

        uint16_t get_width() const;
        uint16_t get_height() const;

        uint64_t get_package_size() const;

        std::vector<uint8_t> get_scene_part(uint64_t offset, uint32_t partSize) const;

    private:
        std::string name_;
        uint16_t width_;
        uint16_t height_;
        // dummy
        uint64_t size_;
    };
}