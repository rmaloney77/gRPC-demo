#include <iostream>
#include <memory>

#include "user_server.hpp"

//With help from:
//https://github.com/tensorflow/tensorflow/blob/master/tensorflow/core/distributed_runtime/rpc/grpc_server_lib.cc
void NoReusePortOption::UpdateArguments(grpc::ChannelArguments* args) {
    args->SetInt(GRPC_ARG_ALLOW_REUSEPORT, 0);
}

void NoReusePortOption::UpdatePlugins(std::vector<std::unique_ptr<::grpc::ServerBuilderPlugin>>*plugins) {
}

grpc::Status UserServiceImpl::SayHello(grpc::ServerContext* context, const game::HelloRequest* request, game::HelloReply* reply) {
    std::string prefix("(Server) Hello ");
    reply->set_message(prefix + request->name());
    return grpc::Status::OK;
}



