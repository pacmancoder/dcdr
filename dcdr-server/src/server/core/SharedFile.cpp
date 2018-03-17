#include <dcdr/server/core/SharedFile.h>
#include <fstream>
#include <stdexcept>
#include <shared_mutex>

using namespace Dcdr::Server;


namespace
{
    auto GetNativeAccessMode(SharedFile::AccessMode accessMode)
    {
        switch (accessMode)
        {
            case SharedFile::AccessMode::Readonly: return std::ios::binary | std::ios::in;
            case SharedFile::AccessMode::Create:   return std::ios::binary | std::ios::out;
            case SharedFile::AccessMode::Append:   return std::ios::binary | std::ios::out | std::ios::app;
        }

        throw std::invalid_argument("Unreachable code");
    }
}

struct SharedFile::Impl
{
    Impl(std::string path, AccessMode accessMode);

    std::string path_;
    AccessMode accessMode_;
    std::shared_timed_mutex mutex_;
};

SharedFile::Impl::Impl(std::string path, SharedFile::AccessMode accessMode) :
    path_(std::move(path)),
    accessMode_(accessMode),
    mutex_() {}

SharedFile::SharedFile(const std::string& path, AccessMode accessMode) :
    impl_(std::make_unique<Impl>(path, accessMode)) {}

SharedFile::SharedFile(SharedFile &&rhs) noexcept :
    impl_(std::move(rhs.impl_)) {}

SharedFile::~SharedFile() = default;

std::vector<uint8_t> SharedFile::read(std::optional<uint64_t> count, std::optional<uint64_t> offset) const
{
    std::shared_lock<std::shared_timed_mutex> lock(impl_->mutex_);

    std::fstream stream(impl_->path_, GetNativeAccessMode(impl_->accessMode_));

    if (!count.has_value())
    {
        stream.seekg(0, std::ios::end);
        count = static_cast<uint64_t>(stream.tellg());
    }

    if (offset.has_value())
    {
        stream.seekg(offset.value(), std::ios::beg);
    }
    else if (!count.has_value())
    {
        stream.seekg(0, std::ios::beg);
    }

    std::vector<uint8_t> buffer;
    buffer.resize(count.value());
    stream.read(reinterpret_cast<char*>(buffer.data()), buffer.size());
    return buffer;
}

void SharedFile::write(const std::vector<uint8_t>& data, std::optional<uint64_t> offset)
{
    std::unique_lock<std::shared_timed_mutex> lock(impl_->mutex_);

    std::fstream stream(impl_->path_, GetNativeAccessMode(impl_->accessMode_));

    if (offset.has_value())
    {
        stream.seekg(offset.value(), std::ios::beg);
    }

    stream.write(reinterpret_cast<const char*>(data.data()), data.size());
}

uint64_t SharedFile::size() const
{
    std::shared_lock<std::shared_timed_mutex> lock(impl_->mutex_);

    std::fstream stream(impl_->path_, GetNativeAccessMode(impl_->accessMode_));

    stream.seekg(0, std::ios::end);
    return static_cast<uint64_t>(stream.tellg());
}
