#include <gtest/gtest.h>

#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>
#include <dcdr/messaging/commander/CommanderRequestParcels.h>
#include <dcdr/messaging/commander/CommanderResponseParcels.h>

using namespace Dcdr::Interconnect;

class FlatBuffersInterconnectTest : public ::testing::Test
{
protected:
    FlatBuffersParcelSerializer serializer_;
    FlatBuffersParcelDeserializer deserializer_;
};


TEST_F(FlatBuffersInterconnectTest, CommanderGetJobListRequestParcelTest)
{
    CommanderGetJobListRequestParcel request;

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderGetJobListRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetJobInfoRequestParcelTest)
{
    CommanderGetJobInfoRequestParcel request(42);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderGetJobInfoRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_TRUE(receivedRequest->get_request().get_job_id() == 42);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetJobPreviewRequestParcel)
{
    CommanderGetJobPreviewRequestParcel request(42, 2);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderGetJobPreviewRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_TRUE(receivedRequest->get_request().get_job_id() == 42);
    ASSERT_TRUE(receivedRequest->get_request().get_mipmap_level() == 2);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetJobArtifactRequestParcel)
{
    CommanderGetJobArtifactRequestParcel request(42);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderGetJobArtifactRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_TRUE(receivedRequest->get_request().get_job_id() == 42);
}

TEST_F(FlatBuffersInterconnectTest, CommanderSetJobStateRequestParcel)
{
    CommanderSetJobStateRequestParcel request(42, Commander::JobState::InProgress);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderSetJobStateRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_TRUE(receivedRequest->get_request().get_job_id() == 42);
    ASSERT_TRUE(receivedRequest->get_request().get_job_state() == Commander::JobState::InProgress);
}

TEST_F(FlatBuffersInterconnectTest, CommanderAddJobRequestParcel)
{
    CommanderAddJobRequestParcel request(42, 2.0f);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderAddJobRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_TRUE(receivedRequest->get_request().get_scene_id() == 42);
    ASSERT_TRUE(receivedRequest->get_request().get_scale() == 2.0f);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetSceneListRequestParcel)
{
    CommanderGetSceneListRequestParcel request;

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderGetSceneListRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetNodeListRequestParcel)
{
    CommanderGetNodeListRequestParcel request;

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderGetNodeListRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetNodeInfoRequestParcel)
{
    CommanderGetNodeInfoRequestParcel request(42);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderGetNodeInfoRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_TRUE(receivedRequest->get_request().get_node_id() == 42);
}

TEST_F(FlatBuffersInterconnectTest, CommanderSetNodeStateRequestParcel)
{
    CommanderSetNodeStateRequestParcel request(42, Commander::NodeState::Malfunctioned);

    auto serialized = static_cast<const IParcel&>(request).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedRequest = dynamic_cast<CommanderSetNodeStateRequestParcel*>(deserialized.get());
    ASSERT_TRUE(receivedRequest != nullptr);
    ASSERT_TRUE(receivedRequest->get_request().get_node_id() == 42);
    ASSERT_TRUE(receivedRequest->get_request().get_node_state() == Commander::NodeState::Malfunctioned);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetJobListResponseParcel)
{
    std::vector<Commander::Job> jobs = {
            {42, "test",      Commander::JobState::InProgress},
            {2,  "test2",     Commander::JobState::Removed},
            {0,  "aaaaaasda", Commander::JobState::Stopped}
    };

    CommanderGetJobListResponseParcel response(jobs);

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<CommanderGetJobListResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    for (size_t i = 0; i < jobs.size(); ++i)
    {
        ASSERT_EQ(jobs[i].id, receivedResponse->get_response().get_jobs()[i].id);
        ASSERT_EQ(jobs[i].name, receivedResponse->get_response().get_jobs()[i].name);
        ASSERT_EQ(jobs[i].state, receivedResponse->get_response().get_jobs()[i].state);
    }
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetJobInfoResponseParcel)
{
    std::vector<Commander::PropertyPair> properties = {{"one", "1"}, {"two", "2"}};

    CommanderGetJobInfoResponseParcel response(42, properties);

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<CommanderGetJobInfoResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    ASSERT_TRUE(receivedResponse->get_response().get_job_id() == 42);
    for (size_t i = 0; i < properties.size(); ++i)
    {
        ASSERT_EQ(properties[i].name, receivedResponse->get_response().get_job_info()[i].name);
        ASSERT_EQ(properties[i].value, receivedResponse->get_response().get_job_info()[i].value);
    }
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetJobPreviewResponseParcel)
{
    std::vector<uint8_t> data = {1, 2, 3};

    CommanderGetJobPreviewResponseParcel response(42, data);

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<CommanderGetJobPreviewResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    ASSERT_TRUE(receivedResponse->get_response().get_job_id() == 42);
    for (size_t i = 0; i < data.size(); ++i)
    {
        ASSERT_EQ(data[i], receivedResponse->get_response().get_preview()[i]);
    }
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetJobArtifactResponseParcel)
{
    std::vector<uint8_t> data = {1, 2, 3};

    CommanderGetJobArtifactResponseParcel response(42, data);

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<CommanderGetJobArtifactResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    ASSERT_TRUE(receivedResponse->get_response().get_job_id() == 42);
    for (size_t i = 0; i < data.size(); ++i)
    {
        ASSERT_EQ(data[i], receivedResponse->get_response().get_artifact()[i]);
    }
}

TEST_F(FlatBuffersInterconnectTest, CommanderDoJobListUpdateResponseParcel)
{
    CommanderDoJobListUpdateResponseParcel response;

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<CommanderDoJobListUpdateResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetSceneListReponseParcel)
{
    std::vector<Commander::Scene> scenes = {
            {1, "one", 640, 480},
            {2, "two", 1920, 1080}
    };

    CommanderGetSceneListReponseParcel response(scenes);

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<CommanderGetSceneListReponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    for (size_t i = 0; i < scenes.size(); ++i)
    {
        ASSERT_EQ(scenes[i].id, receivedResponse->get_response().get_scenes()[i].id);
        ASSERT_EQ(scenes[i].name, receivedResponse->get_response().get_scenes()[i].name);
        ASSERT_EQ(scenes[i].width, receivedResponse->get_response().get_scenes()[i].width);
        ASSERT_EQ(scenes[i].height, receivedResponse->get_response().get_scenes()[i].height);
    }
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetNodeListResponseParcel)
{
    std::vector<Commander::Node> nodes = {
            {1, "one", Commander::NodeState::Malfunctioned},
            {2, "two", Commander::NodeState::Offline},
            {3, "333", Commander::NodeState::Disabled},
            {4, "444", Commander::NodeState::Active}
    };

    CommanderGetNodeListResponseParcel response(nodes);

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<CommanderGetNodeListResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        ASSERT_EQ(nodes[i].id, receivedResponse->get_response().get_nodes()[i].id);
        ASSERT_EQ(nodes[i].name, receivedResponse->get_response().get_nodes()[i].name);
        ASSERT_EQ(nodes[i].state, receivedResponse->get_response().get_nodes()[i].state);
    }
}

TEST_F(FlatBuffersInterconnectTest, CommanderGetNodeInfoResponseParcel)
{
    std::vector<Commander::PropertyPair> properties = {{"one", "1"}, {"two", "2"}};

    CommanderGetNodeInfoResponseParcel response(42, properties);

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<CommanderGetNodeInfoResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    ASSERT_TRUE(receivedResponse->get_response().get_node_id() == 42);
    for (size_t i = 0; i < properties.size(); ++i)
    {
        ASSERT_EQ(properties[i].name, receivedResponse->get_response().get_node_info()[i].name);
        ASSERT_EQ(properties[i].value, receivedResponse->get_response().get_node_info()[i].value);
    }
}

TEST_F(FlatBuffersInterconnectTest, CommanderDoNodeListUpdateResponseParcel)
{
    CommanderDoNodeListUpdateResponseParcel response;

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<CommanderDoNodeListUpdateResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
}

TEST_F(FlatBuffersInterconnectTest, CommanderDoShowErrorResponseParcel)
{
    CommanderDoShowErrorResponseParcel response(Commander::CommanderErrorKind::NodeNotExist, "Node xxx not exist");

    auto serialized = static_cast<const IParcel&>(response).serialize(serializer_);
    auto deserialized = deserializer_.deserialize(std::move(serialized));

    auto receivedResponse = dynamic_cast<CommanderDoShowErrorResponseParcel*>(deserialized.get());
    ASSERT_TRUE(receivedResponse != nullptr);
    ASSERT_TRUE(receivedResponse->get_response().get_error_kind() == response.get_response().get_error_kind());
    ASSERT_TRUE(receivedResponse->get_response().get_message() == response.get_response().get_message());
}