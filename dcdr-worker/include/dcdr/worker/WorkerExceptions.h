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
                WorkerException("Communication", message) {}
    };

    class FsIOException : public WorkerException
    {
    public:
        explicit FsIOException(const std::string& message) :
                WorkerException("SceneStorage", message) {}
    };

    class SceneLoaderException : public WorkerException
    {
    public:
        explicit SceneLoaderException(const std::string& message) :
                WorkerException("SceneLoader", message) {}
    };
}