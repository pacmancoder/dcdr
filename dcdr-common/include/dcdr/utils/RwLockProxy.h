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
        template <typename... Args>
        explicit RwLockProxy(Args&&... args) :
                obj_(std::forward<Args>(args)...)
        {
            update_modify_timestamp();
        }

        template<typename AccessFunc>
        void access_read(AccessFunc&& accessFunc) const
        {
            // following lock will ensure that Exclusive lock will have priority over shared
            {
                std::unique_lock<std::shared_timed_mutex> priorityLock(priorityMutex_);
            }

            std::shared_lock<std::shared_timed_mutex> accessLock(mutex_);

            accessFunc(obj_);
        }

        template<typename AccessFunc>
        void access_write(AccessFunc&& accessFunc)
        {
            // do not allow new readers to do object access
            std::unique_lock<std::shared_timed_mutex> priorityLock(priorityMutex_);

            std::unique_lock<std::shared_timed_mutex> accessLock(mutex_);

            update_modify_timestamp();
            accessFunc(obj_);
        }

        Timestamp get_last_modified() const
        {
            return timestamp_;
        }

        void update_modify_timestamp()
        {
            timestamp_ = static_cast<Timestamp>(std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch()).count());
        }

    private:
        mutable std::shared_timed_mutex priorityMutex_;
        mutable std::shared_timed_mutex mutex_;

        std::atomic<Timestamp> timestamp_;

        InnerType obj_;
    };
}