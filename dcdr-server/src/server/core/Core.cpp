#include <dcdr/server/core/Core.h>

#include <iostream>
#include <fstream>
#include <iterator>

#include <dcdr/logging/Logger.h>
#include <dcdr/messaging/commander/ACommanderRequestParcelDispatcher.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceInfoRequest.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceInfoResponse.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceRequest.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceResponse.h>

#include <future>

using namespace Dcdr::Logging;
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
public:
    CoreCommanderRequestDispatcher() :
            ACommanderRequestParcelDispatcher() {}

    IParcel::ParcelHandle dispatch(const CommanderGetSurfaceInfoRequest&) override
    {
        auto response = std::make_unique<CommanderGetSurfaceInfoResponse>();
        response->set_width(1920);
        response->set_height(1920);

        return make_parcel_handle(std::move(response));
    }

    IParcel::ParcelHandle dispatch(const CommanderGetSurfaceRequest&) override
    {
        auto response = std::make_unique<CommanderGetSurfaceResponse>();

        std::ifstream imageStream("../../res/images/test_image.jpg", std::ios::binary);
        CommanderGetSurfaceResponse::ImageBuffer buffer((std::istreambuf_iterator<char>(imageStream)),
                                                        std::istreambuf_iterator<char>());
        response->set_image(
                CommanderGetSurfaceResponse::ImageFormat::Png,
                std::move(buffer));

        return make_parcel_handle(std::move(response));
    }
};

Core::Core() :
        AParcelDispatcher(),
        commanderRequestDispatcher_(new Core::CoreCommanderRequestDispatcher()) {}

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
