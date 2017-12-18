#pragma once

#include <string>
#include <cstdint>
#include <vector>

#include <dcdr/messaging/IRequest.h>

namespace Dcdr::Interconnect
{
    class IRequestSerializer;
    class IRequestProcessor;

    class ConnectRequest : public IRequest
    {
    public:
        explicit ConnectRequest(const std::string& userToken);

        std::vector<uint8_t> serialize(IRequestSerializer& serializer) const override;
        void process_request(IRequestProcessor& requestProcessor) const override;

        const std::string& get_user_token() const;
    private:
        std::string user_token_;
    };
}