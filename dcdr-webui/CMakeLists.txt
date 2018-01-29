project(dcdr-webui)

set(COPIED_DCDR_FLATBUFFERS_JS_FILE ${PROJECT_SOURCE_DIR}/DcdrFlatBuffers.js)
set(COPIED_FLATBUFFERS_JS_FILE ${PROJECT_SOURCE_DIR}/flatbuffers.js)
get_target_property(GENERATED_DCDR_FLATBUFFERS_JS_FILE dcdr-interconnect-flatbuffers GENERATED_JS_FILE)

add_custom_command(
        OUTPUT ${COPIED_DCDR_FLATBUFFERS_JS_FILE} ${COPIED_FLATBUFFERS_JS_FILE}
        COMMAND cp ${GENERATED_DCDR_FLATBUFFERS_JS_FILE} ${COPIED_DCDR_FLATBUFFERS_JS_FILE}
        COMMAND cp ${FlatBuffers_SOURCE_DIR}/js/flatbuffers.js ${COPIED_FLATBUFFERS_JS_FILE}
)

add_custom_target(${PROJECT_NAME} ALL DEPENDS
        dcdr-interconnect-flatbuffers
        ${COPIED_DCDR_FLATBUFFERS_JS_FILE}
        ${COPIED_FLATBUFFERS_JS_FILE})