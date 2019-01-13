#include <grpcpp/grpcpp.h>

#include "user_server.hpp"

int main(int argc, char* argv[]) {
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    UserServiceImpl service;
    grpc::ServerBuilder builder;
    builder.SetOption(std::unique_ptr<grpc::ServerBuilderOption>(new NoReusePortOption));
    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::cout << "Starting Server!\n";
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();
}
