#pragma once

#include <dcdr/Exception.h>

namespace Dcdr::Worker
{
    class WorkerException : public DcdrException
    {
    public:
        WorkerException(const std::string& kind, const std::string& message) :
                DcdrException("Worker", kind, message) {}
    };

    class EmptyResponseException : public WorkerException
    {
    public:
        explicit EmptyResponseException(const std::string& message) :
                WorkerException("Worker", message) {}
    };
}