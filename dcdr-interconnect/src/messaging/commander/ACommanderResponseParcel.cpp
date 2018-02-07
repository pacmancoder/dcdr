#include <dcdr/messaging/commander/ACommanderResponseParcel.h>
#include <dcdr/messaging/IParcelDispatcher.h>

using namespace Dcdr::Interconnect;

IParcel::ParcelHandle ACommanderResponseParcel::dispatch(IParcelDispatcher& dispatcher) const
{
    return dispatcher.dispatch(*this);
}
