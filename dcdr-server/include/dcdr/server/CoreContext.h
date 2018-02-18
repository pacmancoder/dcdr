#pragma once

#include <dcdr/utils/RwLockProxy.h>

#include <dcdr/server/Node.h>
#include <dcdr/server/Connection.h>
#include <dcdr/server/Work.h>
#include <dcdr/server/Scene.h>
#include <dcdr/server/Job.h>

#include <chrono>
#include <map>
#include <atomic>
#include <mutex>
#include <shared_mutex>

namespace Dcdr::Server
{
    class ISceneLoader;

    template <typename InnerType>
    class RwLockProxy
    {
    public:
        class ReadHandle
        {
        public:
            ReadHandle(const InnerType& obj, std::shared_timed_mutex& mutex) :
                    obj_(obj),
                    lock_(mutex) {}

            const InnerType& operator*() { return obj_; }
            const InnerType* operator->() { return &obj_; };

        private:
            const InnerType& obj_;
            std::shared_lock<std::shared_timed_mutex> lock_;
        };

        class WriteHandle
        {
        public:
            WriteHandle(InnerType& obj, std::shared_timed_mutex& mutex) :
                    obj_(obj),
                    lock_(mutex) {}

            InnerType& operator*() { return obj_; }
            InnerType* operator->() { return &obj_; };

        private:
            InnerType& obj_;
            std::unique_lock<std::shared_timed_mutex> lock_;
        };

    public:
        template <typename... Args>
        explicit RwLockProxy(Args&&... args) :
                obj_(std::forward<Args>(args)...) {}

        ReadHandle read() { return ReadHandle(obj_, mutex_); }
        WriteHandle write() { return WriteHandle(obj_, mutex_); }

    private:
        std::shared_timed_mutex mutex_;
        InnerType obj_;
    };

    /// @brief provides facade for server core entities
    /// @remark class is thread-safe
    class CoreContext
    {
    public:
        using Timestamp = uint64_t;

    public:

    private:

    };
}