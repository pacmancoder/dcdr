#include <dcdr/worker/SceneStorage.h>
#include <dcdr/worker/WorkerExceptions.h>

#include <cstdio>
#include <experimental/filesystem>

using namespace Dcdr::Worker;

SceneStorage::SceneStorage(const std::string& sceneStoragePath) :
    sceneStoragePath_(sceneStoragePath),
    nextHandle_(0),
    incompleteFiles_() {}

SceneStorage::SceneTransferHandle SceneStorage::cache_start(const std::string& sceneFile)
{
    try
    {
        std::ofstream stream;
        stream.exceptions(std::ios::badbit | std::ios::failbit);
        stream.open(get_full_file_path(sceneFile), std::ios::out | std::ios::binary);

        incompleteFiles_.emplace(
                nextHandle_,
                IncompleteFile { sceneFile, std::move(stream) });
        return nextHandle_++;
    }
    catch (const std::exception& e)
    {
        throw FsIOException(e.what());
    }
}

void SceneStorage::cache_write_chunk(
        SceneStorage::SceneTransferHandle handle, const std::vector<uint8_t>& data)
{
    try
    {
        incompleteFiles_.at(handle).stream.write(reinterpret_cast<const char*>(data.data()), data.size());
    }
    catch (const std::exception& e)
    {
        throw FsIOException(e.what());
    }
}

void SceneStorage::cache_finish(SceneStorage::SceneTransferHandle handle)
{
    try
    {
        incompleteFiles_.erase(handle);
    }
    catch (const std::exception& e)
    {
        throw FsIOException(e.what());
    }
}

void SceneStorage::cache_abort(SceneStorage::SceneTransferHandle handle)
{
    try
    {
        auto pathToRemove = get_full_file_path(incompleteFiles_.at(handle).name);
        cache_finish(handle);
        std::remove(pathToRemove.c_str());
    }
    catch (const std::exception& e)
    {
        throw FsIOException(e.what());
    }
}

bool SceneStorage::is_file_cached(const std::string& file) const
{
    return static_cast<bool>(std::ifstream(get_full_file_path(file), std::ios::in | std::ios::binary));
}

std::string SceneStorage::get_cached_file_path(const std::string& sceneFile) const
{
    if (!is_file_cached(sceneFile))
    {
        throw FsIOException(std::string("File ").append(sceneFile).append(" is not cached"));
    }

    return get_full_file_path(sceneFile);
}

std::string SceneStorage::get_full_file_path(const std::string& fileName) const
{
    return sceneStoragePath_ + "/" + fileName;
}
