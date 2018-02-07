#include <dcdr/server/core/Core.h>

#include <dcdr/logging/Logger.h>

#include <iostream>
#include <fstream>
#include <iterator>

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

Core::Core() :
        IParcelDispatcher() {}

IParcel::ParcelHandle Core::dispatch(const ACommanderRequestParcel&)
{
    return make_parcel_handle(nullptr);
}

IParcel::ParcelHandle Core::dispatch(const ACommanderResponseParcel&)
{
    return make_parcel_handle(nullptr);
}

void Core::run()
{
    std::cin.get();
}
