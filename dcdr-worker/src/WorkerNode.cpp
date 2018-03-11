#include <dcdr/worker/WorkerNode.h>

#include <dcdr/worker/WorkerExceptions.h>

#include <dcdr/logging/Logger.h>
#include <dcdr/transport/WebsocketSyncClientTransport.h>

#include <dcdr/messaging/IParcelDispatcher.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>


#include <dcdr/messaging/worker/WorkerRequestParcels.h>
#include <dcdr/messaging/worker/WorkerResponseParcels.h>

#include <dcdr/messaging/worker/WorkerInterconnectTypes.h>

#include <iostream>
#include <type_traits>

using namespace Dcdr::Worker;
using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;
using namespace Dcdr::Transport;

using namespace std::chrono_literals;

namespace
{
    template<typename ResponseType>
    class WorkerResponseDispatcher : public IParcelDispatcher
    {
    public:
        using VisitFunc = std::function<void(const ResponseType&)>;

    private:
        class InnerWorkerResponseDispatcher : public IWorkerResponseDispatcher
        {
        public:
            explicit InnerWorkerResponseDispatcher(VisitFunc visitFunc) :
                    visitFunc_(visitFunc) {}

            void dispatch(const ResponseType& parcel) override
            {
                visitFunc_(parcel);
            }

        private:
            VisitFunc visitFunc_;
        };

    public:
        explicit WorkerResponseDispatcher(VisitFunc visitFunc) :
                innerDispatcher_(visitFunc) {}

        void dispatch(const AWorkerResponseParcel& parcel) override
        {
            parcel.dispatch(innerDispatcher_);
        }

    private:
        InnerWorkerResponseDispatcher innerDispatcher_;
    };
}

WorkerNode::WorkerNode() :
    impl_(std::make_unique<Impl>()) {}

WorkerNode::~WorkerNode() = default;

struct WorkerNode::Impl
{
    Impl();

    void run();

    template<class ResponseType, class RequestParcelType, typename ResponseVisitFunc>
    void perform_command(RequestParcelType&& request, ResponseVisitFunc&& func);

private:
    std::unique_ptr<WebsocketSyncClientTransport> transport_;

    FlatBuffersParcelDeserializer deserializer_;
    FlatBuffersParcelSerializer serializer_;
};

WorkerNode::Impl::Impl() :
    transport_(nullptr),
    deserializer_(),
    serializer_() {}

template<class ResponseType, class RequestParcelType, typename ResponseVisitFunc>
void WorkerNode::Impl::perform_command(RequestParcelType&& request, ResponseVisitFunc&& func)
{
    static_assert(std::is_base_of<AWorkerRequestParcel, RequestParcelType>::value,
                  "Request type should have a base of AWorkerRequestParcel type");
    static_assert(std::is_base_of<WorkerResponse, ResponseType>::value,
                  "Request type should have a base of AWorkerRequest type");

    auto serializedRequest = std::forward<IParcel>(request).serialize(serializer_);

    if (serializedRequest.empty())
    {
        return;
    }

    auto serializedResponse = transport_->get_response(serializedRequest);

    if (serializedResponse == nullptr)
    {
        throw EmptyResponseException("Response is empty");
    }

    auto response = deserializer_.deserialize(*serializedResponse);

    WorkerResponseDispatcher<ResponseType> responseDispatcher(std::forward<ResponseVisitFunc>(func));

    response->dispatch(responseDispatcher);
}


void WorkerNode::Impl::run()
{
    transport_ = std::make_unique<WebsocketSyncClientTransport>("127.0.0.1:61297", 10s);

    FlatBuffersParcelDeserializer deserializer;
    FlatBuffersParcelSerializer serializer;

    uint32_t nodeId = 0;

    perform_command<WorkerLoginResponse>(
            WorkerLoginRequestParcel("Test_worker", "098f6bcd4621d373cade4e832627b4f6"),
            [&nodeId](const WorkerLoginResponse& response)
            {
                nodeId = response.get_node_id();
            });

    log_info(std::string("Logged in. Node id: ").append(std::to_string(nodeId)));

    for(;;)
    {
        std::vector<Dcdr::Interconnect::Worker::TaskArtifact> artifacts;
        perform_command<WorkerPollTasksResponse>(
                WorkerPollTasksRequestParcel(nodeId),
                [&artifacts, nodeId](const WorkerPollTasksResponse response)
                {
                    for (const auto& task : response.get_tasks())
                    {
                        log_info(std::string("Task: ")
                                         .append("x: ").append(std::to_string(task.x))
                                         .append("; y: ").append(std::to_string(task.y))
                                         .append("; w: ").append(std::to_string(task.width))
                                         .append("; h: ").append(std::to_string(task.height)));


                        std::vector<Dcdr::Types::MultisamplePixel> pixels;
                        pixels.reserve(task.width * task.height);
                        for (int y = 0; y < task.height; ++y)
                        {
                            for (int x = 0; x < task.width; ++x)
                            {
                                if (nodeId == 1)
                                {
                                    pixels.push_back(Dcdr::Types::MultisamplePixel {
                                            Dcdr::Types::Color(1.0f, 0.0f, 0.0f), 1});
                                }
                                else
                                {
                                    pixels.push_back(Dcdr::Types::MultisamplePixel {
                                            Dcdr::Types::Color(0.0f, 1.0f, 0.0f), 1});
                                }
                            }
                        }

                        artifacts.push_back(Dcdr::Interconnect::Worker::TaskArtifact
                        {
                            task.taskId,
                            std::move(pixels)
                        });
                    }
                });
        perform_command<WorkerServerStatusResponse>(
                WorkerCommitTasksRequestParcel(nodeId, std::move(artifacts)),
                [](const WorkerServerStatusResponse&)
                {
                    log_info("Sent work.");
                });

        // some condition will be added
        // break;
    }

    std::cin.get();

    perform_command<WorkerServerStatusResponse>(
            WorkerLogoutRequestParcel(nodeId),
            [](const WorkerServerStatusResponse&)
            {
                log_info(std::string("Logged out."));
            });
}

void WorkerNode::run()
{
    try
    {
        impl_->run();
    }
    catch (std::exception e)
    {
        log_error(std::string("Error: ").append(e.what()));
    }
}
