#pragma once

#include <memory>
#include <cstdint>
#include <vector>

namespace Dcdr::Database
{
    class ICursor;

    class IStatement
    {
    public:
        using CursorPtr = std::shared_ptr<ICursor>;

    public:
        virtual CursorPtr execute() = 0;

        virtual IStatement& bind(int32_t value) = 0;
        virtual IStatement& bind(int64_t value) = 0;
        virtual IStatement& bind(double value) = 0;

        virtual IStatement& bind(const std::string& value) = 0;

        virtual IStatement& bind(std::vector<uint8_t> value) = 0;
        virtual IStatement& bind(nullptr_t) = 0;

        template <typename T>
        IStatement& operator <<(T&& value)
        {
            bind(std::forward<T>(value));
            return *this;
        }

        virtual ~IStatement() = default;
    };
}