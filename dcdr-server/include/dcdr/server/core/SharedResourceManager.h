#pragma once

#include <dcdr/utils/RwLockProxy.h>
#include <chrono>
#include <map>
#include <functional>
#include <atomic>
#include "../../../../../libs/mongoose/mongoose-git/mongoose.h"

namespace Dcdr::Server
{
    template <class ResourceType, typename IdType = uint32_t>
    class SharedResourceManager
    {
    public:
        using ResourceProxy = Utils::RwLockProxy<ResourceType>;
        using Timestamp = typename ResourceProxy::Timestamp;

        using ResourceStorage = std::map<IdType, ResourceProxy>;
        using ResourceStorageProxy = Utils::RwLockProxy<ResourceStorage>;

        using Hook = std::function<void(IdType)>;

    public:
        SharedResourceManager(
                Hook addHook = nullptr,
                Hook removeHook = nullptr) :
            resources_(),
            nextId_(0),
            addHook_(addHook),
            removeHook_(removeHook) {}


        template<typename AccessFunc>
        void access_read(IdType id, AccessFunc&& accessFunc) const
        {
            resources_.access_read([id, accessFunc = std::forward<AccessFunc>(accessFunc)]
                                           (const ResourceStorage& resource)
            {
                const_cast<ResourceProxy&>(resource.at(id))
                        .access_read(std::move(accessFunc));
            });

        }

        template<typename AccessFunc>
        void access_write(IdType id, AccessFunc&& accessFunc) const
        {
            resources_.access_read([id, accessFunc = std::forward<AccessFunc>(accessFunc)]
                                           (const ResourceStorage& resource)
            {
                // no writes performed to outer container, so many writers can work with resource pool
                const_cast<ResourceProxy&>(resource.at(id))
                        .access_write(std::move(accessFunc));
            });

        }

        uint32_t add(ResourceType&& resource)
        {
            auto id = nextId_++;

            resources_.access_write([id, &resource](ResourceStorage& resources)
            {
                resources.emplace(id, std::move(resource));
            });

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

            resources_.access_write([id](ResourceStorage& resources)
            {
                resources.erase(id);
            });
        }

        bool exists(IdType id) const
        {
            bool exists = false;
            resources_.access_read([id, &exists](const ResourceStorage& resources)
            {
                exists = resources.find(id) != resources.cend();
            });

            return exists;
        }

        Timestamp get_last_modified() const
        {
            return resources_.get_last_modified();
        }

        template <typename IterateFunc>
        void iterate_const(IterateFunc&& iterateFunc) const
        {
            resources_.access_read(
            [iterateFunc = std::forward<IterateFunc>(iterateFunc)]
                    (const ResourceStorage& resources)
            {
                for (const auto& resourceEntry : resources)
                {
                    resourceEntry.second.access_read(
                            [id = resourceEntry.first, iterateFunc = std::move(iterateFunc)](const ResourceType& resource)
                            {
                                iterateFunc(id, resource);
                            });
               }
            });
        }

        template <typename IterateFunc>
        void iterate(IterateFunc&& iterateFunc) const
        {
            resources_.update_modify_timestamp();
            resources_.access_read(
            [iterateFunc = std::forward<IterateFunc>(iterateFunc)]
                    (const ResourceStorage& resources) mutable
            {
                for (auto& resourceEntry : const_cast<ResourceStorage&>(resources))
                {
                    resourceEntry.second.access_write(
                    [id = resourceEntry.first, iterateFunc = std::move(iterateFunc)](ResourceType& resource)
                    {
                        iterateFunc(id, resource);
                    });
                }
            });
        }

    private:
        // mutable is for setting new timestamp when writing internal data of container
        // (while container self is still const)
        mutable ResourceStorageProxy resources_;

        IdType nextId_;

        Hook addHook_;
        Hook removeHook_;
    };
}