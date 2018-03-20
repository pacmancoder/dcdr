#pragma once

#include <memory>

namespace Dcdr::Database
{
    class IStatement;

    class IDatabase
    {
    public:
        using StatementPtr = std::shared_ptr<IStatement>;

    public:
        virtual StatementPtr prepare(const std::string& query) = 0;
        virtual ~IDatabase() = default;
    };
}