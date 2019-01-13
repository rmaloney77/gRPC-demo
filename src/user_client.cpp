#include <grpcpp/grpcpp.h>

#include "userservice.pb.h"
#include "userservice.grpc.pb.h"
#include "user_client.hpp"

UserClient::UserClient(std::shared_ptr<grpc::Channel> channel)
      : stub(game::User::NewStub(channel)) {
}

UserClient::UserClient(std::unique_ptr<game::User::StubInterface> stub) 
      : stub(std::move(stub)) {
}

std::string UserClient::SayHello(const std::string& user) {
    game::HelloRequest request;
    request.set_name(user);
    game::HelloReply reply;
    grpc::ClientContext context;
    grpc::Status status = stub->SayHello(&context, request, &reply);
    if (status.ok()) {
        return reply.message();
    } else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed";
    }
}

