#pragma once

#include <cstdint>
#include <fstream>
#include <vector>
#include <optional>
#include <map>


namespace Dcdr::Worker
{
    class Scene;

    class SceneStorage
    {
    public:
        using SceneTransferHandle = unsigned int;

    public:
        explicit SceneStorage(const std::string &sceneStoragePath);

        SceneTransferHandle cache_start(const std::string& sceneFile);
        void cache_write_chunk(SceneTransferHandle handle, const std::vector<uint8_t>& data);
        void cache_finish(SceneTransferHandle handle);
        void cache_abort(SceneTransferHandle handle);

        bool is_file_cached(const std::string& file) const;
        std::string get_cached_file_path(const std::string& sceneFile) const;

    private:
        struct IncompleteFile
        {
            std::string   name;
            std::ofstream stream;
        };

        struct File
        {
            std::ofstream stream;
        };

    private:
        std::string get_full_file_path(const std::string& fileName) const;

    private:
        std::string sceneStoragePath_;

        SceneTransferHandle nextHandle_;
        std::map<uint32_t, IncompleteFile> incompleteFiles_;
    };
}