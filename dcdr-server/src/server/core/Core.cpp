#include <dcdr/server/core/Core.h>

#include <iostream>

#include <dcdr/messaging/commander/ACommanderRequestParcelDispatcher.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceInfoRequest.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceInfoResponse.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceRequest.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceResponse.h>

#include <future>

using namespace Dcdr::Server;
using namespace Dcdr::Interconnect;

namespace
{
    IParcel::ParcelHandle make_parcel_handle(IParcel::ParcelPtr parcel)
    {
        std::promise<IParcel::ParcelPtr> responsePromise;
        responsePromise.set_value(std::move(parcel));
        return responsePromise.get_future();
    }
}

class Core::CoreCommanderRequestDispatcher : public ACommanderRequestParcelDispatcher
{
    IParcel::ParcelHandle dispatch(const CommanderGetSurfaceInfoRequest& parcel) override
    {
        auto response = std::make_unique<CommanderGetSurfaceInfoResponse>();
        response->set_width(1920);
        response->set_height(1920);

        return make_parcel_handle(std::move(response));
    }

    IParcel::ParcelHandle dispatch(const CommanderGetSurfaceRequest& parcel) override
    {
        auto response = std::make_unique<CommanderGetSurfaceResponse>();

        response->set_image(
                CommanderGetSurfaceResponse::ImageFormat::Png,
                CommanderGetSurfaceResponse::ImageBuffer{1, 6, 1, 3});

        return make_parcel_handle(std::move(response));
    }
};

Core::Core() : commanderRequestDispatcher_() {}

IParcel::ParcelHandle Core::dispatch(const ACommanderRequestParcel& parcel)
{
    return parcel.dispatch(*commanderRequestDispatcher_);
}

void Core::run()
{
    std::cin.get();
}

Core::~Core()
{

}
