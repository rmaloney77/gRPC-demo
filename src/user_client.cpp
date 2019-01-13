#include <iostream>
#include <memory>
#include <grpcpp/grpcpp.h>

#include "userservice.pb.h"
#include "userservice.grpc.pb.h"

class UserClient {
public:
    UserClient(std::shared_ptr<grpc::Channel> channel)
      : stub_(game::User::NewStub(channel)) {}

    std::string SayHello(const std::string& user) {
        game::HelloRequest request;
        request.set_name(user);

        game::HelloReply reply;

        grpc::ClientContext context;

        // The actual RPC.
        grpc::Status status = stub_->SayHello(&context, request, &reply);

        // Act upon its status.
        if (status.ok()) {
            return reply.message();
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return "RPC failed";
        }
   }

private:
    std::unique_ptr<game::User::Stub> stub_;
};

int main(int argc, char **argv) {
    UserClient user_client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    std::string user("world");
    std::string reply = user_client.SayHello(user);
    std::cout << "Greeter received: " << reply << std::endl;
    return 0;
}
