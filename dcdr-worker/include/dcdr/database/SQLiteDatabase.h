#pragma once

#include <dcdr/database/IDatabase.h>

#include <memory>

namespace Dcdr::Database
{
    class SQLiteDatabase : public IDatabase
    {
    public:
        using StatementPtr = std::shared_ptr<IStatement>;

    public:
        explicit SQLiteDatabase(const std::string& path);
        ~SQLiteDatabase();

        StatementPtr prepare(const std::string& query) override;

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}