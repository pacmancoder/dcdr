#pragma once

#include <dcdr/utils/RwLockProxy.h>
#include <chrono>
#include <map>
#include <functional>
#include <atomic>

namespace Dcdr::Server
{
    template <class ResourceType, typename IdType = uint32_t>
    class SharedResourceManager
    {
    public:
        using ResourceProxy = Utils::RwLockProxy<ResourceType>;
        using ReadHandle = typename ResourceProxy::ReadHandle;
        using WriteHandle = typename ResourceProxy::WriteHandle;
        using Timestamp = typename ResourceProxy::Timestamp;

        using ResourceStorageProxy = Utils::RwLockProxy<std::map<IdType, ResourceProxy>>;

        using Hook = std::function<void(IdType)>;

    public:
        SharedResourceManager(
                Hook addHook = nullptr,
                Hook removeHook = nullptr) :
            resources_(),
            nextId_(0),
            addHook_(addHook),
            removeHook_(removeHook) {}

        ReadHandle read(IdType id)
        {
            return resources_.read()->at(id).read();
        }

        WriteHandle write(IdType id)
        {
            // any number of clients can change different resources simultaneously
            // as long as ResourceStorageProxy is untouched.
            // So, const cast is performed to provide such capability
            return const_cast<ResourceProxy&>(resources_.read()->at(id)).write();
        }

        uint32_t add(ResourceType&& resource)
        {
            auto id = nextId_++;

            resources_.write()->emplace(id, std::forward<ResourceType>(resource));

            if (addHook_ != nullptr)
            {
                addHook_(id);
            }

            return id;
        }

        void remove(IdType id)
        {
            if (removeHook_ != nullptr)
            {
                removeHook_(id);
            }

            resources_.write()->erase(id);
        }

        Timestamp get_last_modified()
        {
            return resources_.get_last_modified();
        }

        template <typename IterateFunc>
        void iterate_const(IterateFunc&& iterateFunc)
        {
            auto handle = resources_.read();
            for (const auto& resource : *handle)
            {
                std::forward<IterateFunc>(iterateFunc)((*resource.second)->read());
            }
        }

        template <typename IterateFunc>
        void iterate(IterateFunc&& iterateFunc)
        {
            auto handle = resources_.write();
            for (auto& resource : *handle)
            {
                std::forward<IterateFunc>(iterateFunc)(const_cast<ResourceProxy&>(*resource.second)->read());
            }
        }

    private:
        ResourceStorageProxy resources_;
        IdType nextId_;

        Hook addHook_;
        Hook removeHook_;
    };
}