#pragma once

#include <dcdr/database/ICursor.h>

#include <memory>

#include <sqlite3.h>

namespace Dcdr::Database
{
    class SQLiteCursor : public ICursor
    {
    public:
        explicit SQLiteCursor(std::shared_ptr<sqlite3_stmt> statement);

        bool is_null(size_t column) override;

        int32_t get_int(size_t column) override;
        int64_t get_int64(size_t column) override;
        double get_double(size_t column) override;

        std::string get_string(size_t column) override;

        std::vector<uint8_t> get_blob(size_t column) override;

        bool next() override;

    private:
        std::shared_ptr<sqlite3_stmt> statement_;
    };
}