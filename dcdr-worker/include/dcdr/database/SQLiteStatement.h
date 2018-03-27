#pragma once

#include <dcdr/database/IStatement.h>

#include <string>

#include <sqlite3.h>

namespace Dcdr::Database
{
    class SQLiteStatement : public IStatement
    {
    public:
        explicit SQLiteStatement(sqlite3_stmt* statement);
        CursorPtr execute() override;

        IStatement& bind(int32_t value) override;
        IStatement& bind(int64_t value) override;
        IStatement& bind(double value) override;

        IStatement& bind(const std::string &value) override;

        IStatement& bind(std::vector<uint8_t> value) override;

        IStatement& bind(nullptr_t aNullptr) override;

    private:
        std::shared_ptr<sqlite3_stmt> statement_;

        int currentBindIndex_;
    };
}