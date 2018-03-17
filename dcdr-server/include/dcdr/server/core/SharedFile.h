#pragma once

#include <optional>
#include <memory>
#include <vector>

namespace Dcdr::Server
{
    class SharedFile
    {
    public:
        enum class AccessMode
        {
            Readonly,
            Create,
            Append
        };

    public:
        SharedFile(
                const std::string& path,
                AccessMode accessMode);

        SharedFile(SharedFile&& rhs) noexcept;

        ~SharedFile();

        std::vector<uint8_t> read(
                std::optional<uint64_t> count = std::nullopt,
                std::optional<uint64_t> offset = std::nullopt) const;

        void write(
                const std::vector<uint8_t>& data,
                std::optional<uint64_t> offset = std::nullopt);

        uint64_t size() const;

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}