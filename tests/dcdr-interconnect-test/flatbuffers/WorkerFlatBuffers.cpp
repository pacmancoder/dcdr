#include "FlatBuffersTest.h"

#include <dcdr/messaging/worker/WorkerRequestParcels.h>
#include <dcdr/messaging/worker/WorkerResponseParcels.h>

using namespace Dcdr;
using namespace Dcdr::Interconnect;

TEST_F(FlatBuffersInterconnectTest, WorkerLoginRequestParcel)
{
    WorkerLoginRequestParcel request("hello", "there");

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<WorkerLoginRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_EQ(receivedRequest->get_request().get_node_id(), 0u);
    ASSERT_EQ(receivedRequest->get_request().get_name(), request.get_request().get_name());
    ASSERT_EQ(receivedRequest->get_request().get_token(), request.get_request().get_token());
}

TEST_F(FlatBuffersInterconnectTest, WorkerLogoutRequestParcel)
{
    WorkerLogoutRequestParcel request(42u);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<WorkerLogoutRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_EQ(receivedRequest->get_request().get_node_id(), 42u);
}

TEST_F(FlatBuffersInterconnectTest, WorkerSendHardwareInfoRequestParcel)
{
    WorkerSendHardwareInfoRequestParcel request(42u, std::vector<PropertyPair> { PropertyPair {"property", "value"} });

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<WorkerSendHardwareInfoRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_EQ(receivedRequest->get_request().get_node_id(), 42u);
    ASSERT_EQ(receivedRequest->get_request().get_properties().size(), 1u);
    ASSERT_EQ(receivedRequest->get_request().get_properties()[0].name, request.get_request().get_properties()[0].name);
    ASSERT_EQ(receivedRequest->get_request().get_properties()[0].value, request.get_request().get_properties()[0].value);
}

TEST_F(FlatBuffersInterconnectTest, WorkerPollTasksRequestParcel)
{
    WorkerPollTasksRequestParcel request(42u);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<WorkerPollTasksRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_EQ(receivedRequest->get_request().get_node_id(), 42u);
}

TEST_F(FlatBuffersInterconnectTest, WorkerCommitTasksRequestParcel)
{
    WorkerCommitTasksRequestParcel request(
            42,
            std::vector<Worker::TaskArtifact> {
                    Worker::TaskArtifact {13u, std::vector<Worker::Pixel>{
                            Worker::Pixel{Types::Vec3(0.f), 0u}, Worker::Pixel{Types::Vec3(1.f), 1u}}}});

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<WorkerCommitTasksRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_EQ(receivedRequest->get_request().get_node_id(), 42u);
    ASSERT_EQ(receivedRequest->get_request().get_artifacts().size(), 1u);
    const auto& artifact = receivedRequest->get_request().get_artifacts()[0];
    ASSERT_EQ(artifact.taskId, 13u);
    ASSERT_EQ(artifact.data.size(), 2u);
    ASSERT_EQ(artifact.data[0].samples, 0u);
    ASSERT_EQ(artifact.data[0].color.r, 0.f);
    ASSERT_EQ(artifact.data[0].color.g, 0.f);
    ASSERT_EQ(artifact.data[0].color.b, 0.f);
    ASSERT_EQ(artifact.data[1].samples, 1u);
    ASSERT_EQ(artifact.data[1].color.r, 1.f);
    ASSERT_EQ(artifact.data[1].color.g, 1.f);
    ASSERT_EQ(artifact.data[1].color.b, 1.f);
}

TEST_F(FlatBuffersInterconnectTest, WorkerDownloadSceneRequestParcel)
{
    WorkerDownloadSceneRequestParcel request(42u, 13u, 666u);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<WorkerDownloadSceneRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_EQ(receivedRequest->get_request().get_node_id(), 42u);
    ASSERT_EQ(receivedRequest->get_request().get_scene_id(), 13u);
    ASSERT_EQ(receivedRequest->get_request().get_offset(), 666u);
}


TEST_F(FlatBuffersInterconnectTest, WorkerServerStatusResponseParcel)
{
    WorkerServerStatusResponseParcel response(42u, Worker::ServerStatus::Ok, "ok");

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<WorkerServerStatusResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    ASSERT_EQ(receivedResponse->get_response().get_node_id(), 42u);
    ASSERT_EQ(receivedResponse->get_response().get_status(), Worker::ServerStatus::Ok);
    ASSERT_EQ(receivedResponse->get_response().get_message(), std::string("ok"));
}

TEST_F(FlatBuffersInterconnectTest, WorkerLoginResponseParcel)
{
    WorkerLoginResponseParcel response(42u);

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<WorkerLoginResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    ASSERT_EQ(receivedResponse->get_response().get_node_id(), 42u);
}

TEST_F(FlatBuffersInterconnectTest, WorkerPollTasksResponseParcel)
{
    WorkerPollTasksResponseParcel response(
            42,
            std::vector<Worker::TaskInfo> {
                Worker::TaskInfo {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u}
            });

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<WorkerPollTasksResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    ASSERT_EQ(receivedResponse->get_response().get_node_id(), 42u);
    ASSERT_EQ(receivedResponse->get_response().get_tasks().size(), 1u);
    const auto& tasks = receivedResponse->get_response().get_tasks();
    ASSERT_EQ(tasks[0].taskId,        0u);
    ASSERT_EQ(tasks[0].sceneId,       1u);
    ASSERT_EQ(tasks[0].x,             2u);
    ASSERT_EQ(tasks[0].y,             3u);
    ASSERT_EQ(tasks[0].width,         4u);
    ASSERT_EQ(tasks[0].height,        5u);
    ASSERT_EQ(tasks[0].minIterations, 6u);
    ASSERT_EQ(tasks[0].maxIterations, 7u);
}

TEST_F(FlatBuffersInterconnectTest, WorkerDownloadSceneResponseParcel)
{
    WorkerDownloadSceneResponseParcel response(42u, 13u, 64u, 128u, std::vector<uint8_t> {1u, 2u, 3u});

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<WorkerDownloadSceneResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    ASSERT_EQ(receivedResponse->get_response().get_node_id(),    42u);
    ASSERT_EQ(receivedResponse->get_response().get_scene_id(),   13u);
    ASSERT_EQ(receivedResponse->get_response().get_offset(),     64u);
    ASSERT_EQ(receivedResponse->get_response().get_bytes_left(), 128u);
    ASSERT_EQ(receivedResponse->get_response().get_data()[0],    1u);
    ASSERT_EQ(receivedResponse->get_response().get_data()[1],    2u);
    ASSERT_EQ(receivedResponse->get_response().get_data()[2],    3u);
}

TEST_F(FlatBuffersInterconnectTest, WorkerGetSceneInfoRequestParcel)
{
    WorkerGetSceneInfoRequestParcel request(42u, 13u);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<WorkerGetSceneInfoRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_EQ(receivedRequest->get_request().get_node_id(), 42u);
    ASSERT_EQ(receivedRequest->get_request().get_scene_id(), 13u);
}

TEST_F(FlatBuffersInterconnectTest, WorkerGetSceneInfoResponseParcel)
{
    WorkerGetSceneInfoResponseParcel response(
            1u, 2u, 64u, 128u, "Test");

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<WorkerGetSceneInfoResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    ASSERT_EQ(receivedResponse->get_response().get_node_id(),    1u);
    ASSERT_EQ(receivedResponse->get_response().get_scene_id(),   2u);
    ASSERT_EQ(receivedResponse->get_response().get_width(),      64u);
    ASSERT_EQ(receivedResponse->get_response().get_height(),     128u);
    ASSERT_EQ(receivedResponse->get_response().get_file_name(),  std::string("Test"));
}
