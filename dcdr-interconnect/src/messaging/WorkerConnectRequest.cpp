#include <dcdr/messaging/WorkerConnectRequest.h>

#include <algorithm>
#include <dcdr/messaging/AParcelSerializer.h>

using namespace Dcdr::Interconnect;

WorkerConnectRequest::WorkerConnectRequest() :
        AWorkerRequestParcel(),
        token_()
{
    std::fill(token_.begin(), token_.end(), 0);
}

IParcel::SerializedParcel WorkerConnectRequest::serialize(AParcelSerializer& dispatcher)
{
    return dispatcher.serialize(*this);
}

void WorkerConnectRequest::set_token(const Token& token)
{
    token_ = token;
}

const WorkerConnectRequest::Token& WorkerConnectRequest::get_token() const
{
    return token_;
}
