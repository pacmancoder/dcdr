#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <atomic>

namespace Dcdr::Utils
{
    template <typename InnerType>
    class RwLockProxy
    {
    public:
        using Timestamp = uint64_t;

    public:
        class ReadHandle
        {
        private:
            ReadHandle(const RwLockProxy<InnerType>& rwLockProxy) :
                rwLockProxy_(rwLockProxy),
                lock_(rwLockProxy.mutex_) {}

        public:
            const InnerType& operator*() { return rwLockProxy_.obj_; }
            const InnerType* operator->() { return &rwLockProxy_.obj_; };

            friend class RwLockProxy<InnerType>;

        private:
            const RwLockProxy<InnerType>& rwLockProxy_;
            std::shared_lock<std::shared_timed_mutex> lock_;
        };

        class WriteHandle
        {
        private:
            WriteHandle(RwLockProxy<InnerType>& rwLockProxy) :
                    rwLockProxy_(rwLockProxy),
                    priorityLock_(rwLockProxy.priorityMutex_),
                    lock_(rwLockProxy_.mutex_){}

        public:
            InnerType& operator*() { return rwLockProxy_.obj_; }
            InnerType* operator->() { return &rwLockProxy_.obj_; };

            friend class RwLockProxy<InnerType>;

        private:
            RwLockProxy<InnerType>& rwLockProxy_;
            std::unique_lock<std::shared_timed_mutex> priorityLock_;
            std::unique_lock<std::shared_timed_mutex> lock_;
        };

    public:
        template <typename... Args>
        explicit RwLockProxy(Args&&... args) :
                obj_(std::forward<Args>(args)...) {}

        ReadHandle read() const
        {
            // following lock will ensure that Exclusive lock will have priority over shared
            {
                std::unique_lock<std::shared_timed_mutex> priorityLock;
            }
            return ReadHandle(*this);
        }

        WriteHandle write()
        {
            timestamp_ = static_cast<Timestamp>(std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch()).count());
            return WriteHandle(*this);
        }

        Timestamp get_last_modified() const
        {
            return timestamp_;
        }

    private:
        mutable std::shared_timed_mutex priorityMutex_;
        mutable std::shared_timed_mutex mutex_;

        std::atomic<Timestamp> timestamp_;

        InnerType obj_;
    };
}