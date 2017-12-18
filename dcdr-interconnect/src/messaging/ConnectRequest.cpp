#include <dcdr/messaging/ConnectRequest.h>
#include <dcdr/messaging/IRequestSerializer.h>
#include <dcdr/messaging/IRequestProcessor.h>

using namespace Dcdr::Interconnect;

ConnectRequest::ConnectRequest(const std::string &userToken) :
    user_token_(userToken) {}

std::vector<uint8_t> ConnectRequest::serialize(IRequestSerializer &serializer) const
{
    return serializer.serialize(*this);
}

void ConnectRequest::process_request(IRequestProcessor &requestProcessor) const
{
    requestProcessor.process_request(*this);
}

const std::string &ConnectRequest::get_user_token() const {
    return user_token_;
}
