#!/bin/bash
# flatc should be in path!
flatc --cpp dncp.fbs
flatc --js dncp.fbs
mv dncp_generated.h ../../dcdr-interconnect/src/serialization/FlatBuffers.h
mv dncp_generated.js ../../dcdr-webui/DcdrFlatBuffers.js
cp ../../libs/flatbuffers-git/js/flatbuffers.js ../../dcdr-webui/flatbuffers.js
