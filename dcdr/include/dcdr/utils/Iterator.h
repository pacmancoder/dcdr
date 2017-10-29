#pragma once

#include <memory>

namespace Dcdr::Utils
{
    template <typename T>
    class IITerator
    {
    public:
        virtual void advance() = 0;
        virtual bool can_advance() = 0;
        virtual T& get() = 0;
    };

    template <typename T>
    class IConstIterator
    {
    public:
        virtual void advance() = 0;
        virtual bool can_advance() = 0;
        virtual const T& get() = 0;
    };

    template <class T> using IteratorPtr = std::unique_ptr<IITerator<T>>;
    template <class T> using ConstIteratorPtr = std::unique_ptr<IConstIterator<T>>;

}