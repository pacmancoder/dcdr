project(dcdr-webui)

set(COPIED_JS_FILE ${PROJECT_SOURCE_DIR}/DcdrFlatBuffers.js)
get_target_property(GENERATED_JS_FILE dcdr-interconnect-flatbuffers GENERATED_JS_FILE)

add_custom_command(
        OUTPUT ${COPIED_JS_FILE}
        COMMAND cp ${GENERATED_JS_FILE} ${COPIED_JS_FILE}
)

add_custom_target(${PROJECT_NAME} DEPENDS
        dcdr-interconnect-flatbuffers
        ${COPIED_JS_FILE})