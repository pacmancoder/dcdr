#include "FlatBuffersTest.h"

#include <dcdr/messaging/worker/WorkerRequestParcels.h>
#include <dcdr/messaging/worker/WorkerResponseParcels.h>

using namespace Dcdr;
using namespace Dcdr::Interconnect;

TEST_F(FlatBuffersInterconnectTest, WorkerLoginRequestParcel)
{
    WorkerLoginRequestParcel request(42, "hello", "there");

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<WorkerLoginRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_EQ(receivedRequest->get_request().get_node_id(), 42);
    ASSERT_EQ(receivedRequest->get_request().get_name(), request.get_request().get_name());
    ASSERT_EQ(receivedRequest->get_request().get_token(), request.get_request().get_token());
}

TEST_F(FlatBuffersInterconnectTest, WorkerLogoutRequestParcel)
{
    WorkerLogoutRequestParcel request(42);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<WorkerLogoutRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_EQ(receivedRequest->get_request().get_node_id(), 42);
}

TEST_F(FlatBuffersInterconnectTest, WorkerSendHardwareInfoRequestParcel)
{
    WorkerSendHardwareInfoRequestParcel request(42, std::vector<PropertyPair> { PropertyPair {"property", "value"} });

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<WorkerSendHardwareInfoRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_EQ(receivedRequest->get_request().get_node_id(), 42);
    ASSERT_EQ(receivedRequest->get_request().get_properties().size(), 1);
    ASSERT_EQ(receivedRequest->get_request().get_properties()[0].name, request.get_request().get_properties()[0].name);
    ASSERT_EQ(receivedRequest->get_request().get_properties()[0].value, request.get_request().get_properties()[0].value);
}

TEST_F(FlatBuffersInterconnectTest, WorkerPollTasksRequestParcel)
{
    WorkerPollTasksRequestParcel request(42);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<WorkerPollTasksRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_EQ(receivedRequest->get_request().get_node_id(), 42);
}

TEST_F(FlatBuffersInterconnectTest, WorkerCommitTasksRequestParcel)
{
    WorkerCommitTasksRequestParcel request(
            42,
            std::vector<Worker::TaskArtifact> {
                    Worker::TaskArtifact {13, std::vector<Worker::Pixel>{
                            Worker::Pixel{Types::Vec3(0.f), 0}, Worker::Pixel{Types::Vec3(1.f), 1}}}});

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<WorkerCommitTasksRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_EQ(receivedRequest->get_request().get_node_id(), 42);
    ASSERT_EQ(receivedRequest->get_request().get_artifacts().size(), 1);
    const auto& artifact = receivedRequest->get_request().get_artifacts()[0];
    ASSERT_EQ(artifact.taskId, 13);
    ASSERT_EQ(artifact.data.size(), 2);
    ASSERT_EQ(artifact.data[0].samples, 0);
    ASSERT_EQ(artifact.data[0].color.r, 0.f);
    ASSERT_EQ(artifact.data[0].color.g, 0.f);
    ASSERT_EQ(artifact.data[0].color.b, 0.f);
    ASSERT_EQ(artifact.data[1].samples, 1);
    ASSERT_EQ(artifact.data[1].color.r, 1.f);
    ASSERT_EQ(artifact.data[1].color.g, 1.f);
    ASSERT_EQ(artifact.data[1].color.b, 1.f);
}

TEST_F(FlatBuffersInterconnectTest, WorkerDownloadSceneRequestParcel)
{
    WorkerDownloadSceneRequestParcel request(42, 13, 666);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<WorkerDownloadSceneRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_EQ(receivedRequest->get_request().get_node_id(), 42);
    ASSERT_EQ(receivedRequest->get_request().get_scene_id(), 13);
    ASSERT_EQ(receivedRequest->get_request().get_offset(), 666);
}


TEST_F(FlatBuffersInterconnectTest, WorkerServerStatusResponseParcel)
{
    WorkerServerStatusResponseParcel response(42, Worker::ServerStatus::Ok, "ok");

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<WorkerServerStatusResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    ASSERT_EQ(receivedResponse->get_response().get_node_id(), 42);
    ASSERT_EQ(receivedResponse->get_response().get_status(), Worker::ServerStatus::Ok);
    ASSERT_EQ(receivedResponse->get_response().get_message(), std::string("ok"));
}

TEST_F(FlatBuffersInterconnectTest, WorkerLoginResponseParcel)
{
    WorkerLoginResponseParcel response(42);

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<WorkerLoginResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    ASSERT_EQ(receivedResponse->get_response().get_node_id(), 42);
}

TEST_F(FlatBuffersInterconnectTest, WorkerPollTasksResponseParcel)
{
    WorkerPollTasksResponseParcel response(
            42,
            std::vector<Worker::TaskInfo> {
                Worker::TaskInfo {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
            });

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<WorkerPollTasksResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    ASSERT_EQ(receivedResponse->get_response().get_node_id(), 42);
    ASSERT_EQ(receivedResponse->get_response().get_tasks().size(), 1);
    const auto& tasks = receivedResponse->get_response().get_tasks();
    ASSERT_EQ(tasks[0].taskId,        0);
    ASSERT_EQ(tasks[0].sceneId,       1);
    ASSERT_EQ(tasks[0].sceneWidth,    2);
    ASSERT_EQ(tasks[0].sceneHeight,   3);
    ASSERT_EQ(tasks[0].x,             4);
    ASSERT_EQ(tasks[0].y,             5);
    ASSERT_EQ(tasks[0].width,         6);
    ASSERT_EQ(tasks[0].height,        7);
    ASSERT_EQ(tasks[0].minIterations, 8);
    ASSERT_EQ(tasks[0].maxIterations, 9);
}

TEST_F(FlatBuffersInterconnectTest, WorkerDownloadSceneResponseParcel)
{
    WorkerDownloadSceneResponseParcel response(42, 1, 64, 128, std::vector<uint8_t> {1, 2, 3});

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<WorkerDownloadSceneResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    ASSERT_EQ(receivedResponse->get_response().get_node_id(),    42);
    ASSERT_EQ(receivedResponse->get_response().get_scene_id(),   1);
    ASSERT_EQ(receivedResponse->get_response().get_offset(),     64);
    ASSERT_EQ(receivedResponse->get_response().get_bytes_left(), 128);
    ASSERT_EQ(receivedResponse->get_response().get_data()[0],    1);
    ASSERT_EQ(receivedResponse->get_response().get_data()[1],    2);
    ASSERT_EQ(receivedResponse->get_response().get_data()[2],    3);

}