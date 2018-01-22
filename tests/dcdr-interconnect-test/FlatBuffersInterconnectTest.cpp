#include <gtest/gtest.h>

#include <dcdr/messaging/FlatBuffersParcelSerializer.h>
#include <dcdr/messaging/FlatBuffersParcelDeserializer.h>
#include <dcdr/messaging/AWorkerRequestParcel.h>
#include <dcdr/messaging/WorkerConnectRequest.h>

using namespace Dcdr::Interconnect;

class FlatBuffersInterconnectTest : public ::testing::Test {};

TEST_F(FlatBuffersInterconnectTest, WorkerConnectRequestTest)
{
    const AWorkerRequestParcel::SessionID session {0, 1, 2, 3, 4, 6, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    const WorkerConnectRequest::Token     token   {0, 1, 2, 3, 4, 6, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    FlatBuffersParcelSerializer serializer;

    WorkerConnectRequest workerConnectRequest;
    workerConnectRequest.set_session_id(session);
    workerConnectRequest.set_token(token);

    auto serializedParcel = serializer.serialize(workerConnectRequest);

    FlatBuffersParcelDeserializer deserializer;
    auto deserializedParcel = deserializer.deserialize(serializedParcel);

    auto deserializedWorkerConnectRequest = dynamic_cast<WorkerConnectRequest*>(deserializedParcel.get());
    ASSERT_TRUE(deserializedWorkerConnectRequest->get_session_id() == session);
    ASSERT_TRUE(deserializedWorkerConnectRequest->get_token()      == token);
}