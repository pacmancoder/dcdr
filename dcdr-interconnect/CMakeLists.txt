project(dcdr-interconnect)

set(DCDR_INTERCONNECT_INCLUDES
        include/dcdr/messaging/IRequest.h
        include/dcdr/messaging/IResponse.h
        include/dcdr/messaging/IRequestProcessor.h
        include/dcdr/messaging/IResponseProcessor.h
        include/dcdr/messaging/IRequestSerializer.h
        include/dcdr/messaging/IResponseSerializer.h
        include/dcdr/messaging/IRequestDeserializer.h

        include/dcdr/messaging/FlatBuffersRequestSerializer.h
        include/dcdr/messaging/FlatBuffersRequestDeserializer.h
        include/dcdr/messaging/ConnectRequest.h
        include/dcdr/messaging/ClientConnection.h
        include/dcdr/messaging/ServerConnection.h

        src/serialization/FlatBuffers.h)

set(DCDR_INTERCONNECT_SOURCES
        src/messaging/FlatBuffersRequestSerializer.cpp
        src/messaging/FlatBuffersRequestDeserializer.cpp
        src/messaging/ConnectRequest.cpp
        src/messaging/ClientConnection.cpp
        src/messaging/ServerConnection.cpp)


set(SOURCE_FILES ${DCDR_INTERCONNECT_INCLUDES} ${DCDR_INTERCONNECT_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${FlatBuffers_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)