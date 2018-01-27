#include <dcdr/messaging/commander/ACommanderResponseParcel.h>
#include <dcdr/messaging/AParcelDispatcher.h>

using namespace Dcdr::Interconnect;

IParcel::ParcelHandle ACommanderResponseParcel::dispatch(AParcelDispatcher& dispatcher)
{
    return dispatcher.dispatch(*this);
}
