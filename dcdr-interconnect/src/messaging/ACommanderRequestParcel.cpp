#include <dcdr/messaging/ACommanderRequestParcel.h>

#include <dcdr/messaging/IParcelDispatcher.h>

using namespace Dcdr::Interconnect;

IParcel::ParcelHandle ACommanderRequestParcel::dispatch(IParcelDispatcher& dispatcher)
{
    return dispatcher.dispatch(*this);
}
