#modified version of https://github.com/grpc/grpc/blob/master/examples/cpp/helloworld/CMakeLists.txt
cmake_minimum_required(VERSION 3.2)
project(wb-app)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Protobuf REQUIRED)
message(STATUS "Using Protobuf ${PROTOBUF_VERSION}")

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(gRPC REQUIRED)
set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
message(STATUS "Using gRPC ${gRPC_VERSION}")

enable_testing()
find_package(GTest REQUIRED)
include_directories(BEFORE ${GTEST_INCLUDE_DIRS})

# Proto file
get_filename_component(user_service_proto "${CMAKE_CURRENT_SOURCE_DIR}/proto/userservice.proto" ABSOLUTE)
get_filename_component(user_service_proto_path "${user_service_proto}" PATH)

# Generated sources
set(user_service_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/userservice.pb.cc")
set(user_service_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/userservice.pb.h")
set(user_service_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/userservice.grpc.pb.cc")
set(user_service_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/userservice.grpc.pb.h")
add_custom_command(
      OUTPUT "${user_service_proto_srcs}" "${user_service_proto_hdrs}" "${user_service_grpc_srcs}" "${user_service_grpc_hdrs}"
      COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
      ARGS --grpc_out "generate_mock_code=true:${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${user_service_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${user_service_proto}"
      DEPENDS "${user_service_proto}")


add_executable(userservice "src/server_main.cpp" "src/user_server.cpp" ${user_service_proto_srcs} ${user_service_grpc_srcs})
target_link_libraries(userservice ${_GRPC_GRPCPP_UNSECURE} ${PROTOBUF_LIBRARIES})

add_executable(userasyncservice "src/server_async_main.cpp" "src/user_server.cpp" ${user_service_proto_srcs} ${user_service_grpc_srcs})
target_link_libraries(userasyncservice ${_GRPC_GRPCPP_UNSECURE} ${PROTOBUF_LIBRARIES})

add_executable(userclient "src/client_main.cpp" "src/user_client.cpp" ${user_service_proto_srcs} ${user_service_grpc_srcs})
target_link_libraries(userclient ${_GRPC_GRPCPP_UNSECURE} ${PROTOBUF_LIBRARIES})

add_executable(userasyncclient "src/client_async_main.cpp" "src/user_client.cpp" ${user_service_proto_srcs} ${user_service_grpc_srcs})
target_link_libraries(userasyncclient ${_GRPC_GRPCPP_UNSECURE} ${PROTOBUF_LIBRARIES})

add_executable(usertest "test/user_service_test.cpp" "src/user_server.cpp" "src/user_client.cpp" ${user_service_proto_srcs} ${user_service_grpc_srcs})
target_link_libraries(usertest ${_GRPC_GRPCPP_UNSECURE} ${PROTOBUF_LIBRARIES} ${GTEST_BOTH_LIBRARIES} gmock gmock_main)
GTEST_ADD_TESTS(usertest "" test/user_service_test.cpp)
