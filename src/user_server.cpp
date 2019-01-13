#include <iostream>
#include <grpcpp/grpcpp.h>
#include <memory>

#include "userservice.pb.h"
#include "userservice.grpc.pb.h"

//With help from:
//https://github.com/tensorflow/tensorflow/blob/master/tensorflow/core/distributed_runtime/rpc/grpc_server_lib.cc
class NoReusePortOption : public grpc::ServerBuilderOption {
 public:
  void UpdateArguments(grpc::ChannelArguments* args) override {
    args->SetInt(GRPC_ARG_ALLOW_REUSEPORT, 0);
  }

  void UpdatePlugins(std::vector<std::unique_ptr<::grpc::ServerBuilderPlugin>>*
                         plugins) override {
  }
};

class UserServiceImpl final : public game::User::Service {
    grpc::Status SayHello(grpc::ServerContext* context, const game::HelloRequest* request, game::HelloReply* reply) override {
    std::string prefix("Hello YO");
    reply->set_message(prefix + request->name());
    return grpc::Status::OK;
  }
};

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

