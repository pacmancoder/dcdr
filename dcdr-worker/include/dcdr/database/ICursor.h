#pragma once

#include <cstdint>
#include <optional>
#include <vector>

namespace Dcdr::Database
{
    class ICursor
    {
    public:
        virtual bool is_null(size_t column) const = 0;

        virtual int32_t get_int(size_t column) const = 0;
        virtual int64_t get_int64(size_t column) const = 0;
        virtual double  get_double(size_t column) const = 0;

        virtual std::string get_string(size_t column) const = 0;

        virtual std::vector<uint8_t> get_blob(size_t column) const = 0;

        virtual bool next() = 0;

        virtual ~ICursor() = default;
    };
}