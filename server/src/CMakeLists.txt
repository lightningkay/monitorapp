set(PROTOCOL_DIR ${PROJECT_SOURCE_DIR}/protocol)
add_custom_command(OUTPUT query.pb.cc query.pb.h response.pb.cc response.pb.h
  COMMAND protoc
  ARGS --cpp_out . ${PROTOCOL_DIR}/query.proto ${PROTOCOL_DIR}/response.proto -I${PROTOCOL_DIR}
  DEPENDS ${PROTOCOL_DIR}/query.proto ${PROTOCOL_DIR}/response.proto
  VERBATIM )

set_source_files_properties(query.pb.cc response.pb.cc PROPERTIES COMPILE_FLAGS "-Wno-conversion")

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR}/src)
set(SOURCEFILES main.cc
                codec.cc
                monitorserver.cc
                query.pb.cc
                response.pb.cc)
add_executable(webmonitor ${SOURCEFILES})
set_target_properties(webmonitor PROPERTIES COMPILE_FLAGS "-Wno-error=shadow")

target_link_libraries(webmonitor muduo_net)
target_link_libraries(webmonitor protobuf z)
