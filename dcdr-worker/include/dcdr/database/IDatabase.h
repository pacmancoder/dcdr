#pragma once

#include <dcdr/database/IStatement.h>

#include <memory>

namespace Dcdr::Database
{
    class IDatabase
    {
    public:
        using StatementPtr = std::shared_ptr<IStatement>;

    public:
        virtual StatementPtr prepare(const std::string& query) = 0;
        virtual ~IDatabase() = default;
    };
}