#include <dcdr/worker/SceneLoader.h>
#include <dcdr/logging/Logger.h>
#include <dcdr/worker/WorkerExceptions.h>

#include <functional>
#include <fstream>

#include <microtar.h>
#include <sqlite3.h>

using namespace Dcdr;
using namespace Dcdr::Logging;
using namespace Dcdr::Worker;

namespace
{
    const char* LOG_PREFIX = "[SceneLoader] ";
}

struct SceneLoader::Impl
{
    explicit Impl(std::string path);

    std::string scenePath_;
};

SceneLoader::Impl::Impl(std::string path) :
    scenePath_(std::move(path)) {}

SceneLoader::SceneLoader(const std::string& path) :
    impl_(std::make_unique<Impl>(path)) {}

void SceneLoader::load_to(Renderer::Scene& /*scene*/)
{
    mtar_t tar = {};
    std::unique_ptr<mtar_t, std::function<void(mtar_t*)>> tarDeleter(&tar, [](mtar_t* tar){ mtar_close(tar); });

    if (mtar_open(&tar, impl_->scenePath_.c_str(), "rb") != MTAR_ESUCCESS)
    {
        throw SceneLoaderException("Can't open scene file");
    }

    mtar_header_t tarHeader = {};
    if (mtar_find(&tar, "scene.db", &tarHeader) != MTAR_ESUCCESS)
    {
        throw SceneLoaderException("Can't find scene.db in scene tar archive");
    }

    std::string unpackedDBPath = impl_->scenePath_ + ".scene.db.tmp";
    {
        std::ofstream unpackedFile;
        unpackedFile.exceptions(std::ios::failbit | std::ios::badbit);
        unpackedFile.open(unpackedDBPath, std::ios::out | std::ios::binary);
        std::vector<char> buffer(tarHeader.size);
        mtar_read_data(&tar, buffer.data(), tarHeader.size);
        unpackedFile.write(buffer.data(), buffer.size());
        log_debug(LOG_PREFIX, "Unpacked scene.db file");
    }

    sqlite3* dbHandle = nullptr;
    std::unique_ptr<sqlite3, std::function<void(sqlite3*)>> sqliteDeleter(dbHandle, [](sqlite3* db){ sqlite3_close(db); });

    if (sqlite3_open(unpackedDBPath.c_str(), &dbHandle) != SQLITE_OK)
    {
        log_debug("Can't open sqlite3 database:", sqlite3_errmsg(dbHandle));
        throw SceneLoaderException("Can't open sqlite3 database");
    }

    sqlite3_stmt* cursor;
    if (sqlite3_prepare_v2(dbHandle, "SELECT uid, name FROM Metainfo", -1, &cursor, nullptr) != SQLITE_OK)
    {
        log_debug("Can't query metainfo: ", sqlite3_errmsg(dbHandle));
        throw SceneLoaderException("Can't query metainfo");
    }

    sqlite3_step(cursor);
    log_info(LOG_PREFIX, "Parsing scene ", sqlite3_column_text(cursor, 1), " with uid ", sqlite3_column_text(cursor, 0));

}

SceneLoader::~SceneLoader() = default;

