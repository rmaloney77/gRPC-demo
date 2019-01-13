#include <iostream>
#include <grpcpp/grpcpp.h>
#include <memory>

#include "userservice.pb.h"
#include "userservice.grpc.pb.h"

//With help from:
//https://github.com/tensorflow/tensorflow/blob/master/tensorflow/core/distributed_runtime/rpc/grpc_server_lib.cc
class NoReusePortOption : public grpc::ServerBuilderOption {
    public:
        void UpdateArguments(grpc::ChannelArguments* args) override;
        void UpdatePlugins(std::vector<std::unique_ptr<::grpc::ServerBuilderPlugin>>* plugins) override;
};

class UserServiceImpl final : public game::User::Service {
    grpc::Status SayHello(grpc::ServerContext* context, const game::HelloRequest* request, game::HelloReply* reply) override;
};

