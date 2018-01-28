#pragma once

#include <memory>
#include <dcdr/messaging/AParcelDispatcher.h>

namespace Dcdr::Server
{
    class Core : public Interconnect::AParcelDispatcher
    {
    public:
        Core();

        void run();

        Interconnect::IParcel::ParcelHandle dispatch(const Interconnect::ACommanderRequestParcel& parcel) override;

        virtual ~Core();
    private:
        class CoreCommanderRequestDispatcher;
        std::unique_ptr<CoreCommanderRequestDispatcher> commanderRequestDispatcher_;
    };
}