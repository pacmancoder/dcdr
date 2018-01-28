#include <dcdr/messaging/commander/ACommanderResponseParcel.h>
#include <dcdr/messaging/AParcelDispatcher.h>

using namespace Dcdr::Interconnect;

IParcel::ParcelHandle ACommanderResponseParcel::dispatch(AParcelDispatcher& dispatcher) const
{
    return dispatcher.dispatch(*this);
}
