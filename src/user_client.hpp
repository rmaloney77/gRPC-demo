#include <iostream>
#include <memory>
#include <grpcpp/grpcpp.h>

#include "userservice.pb.h"
#include "userservice.grpc.pb.h"

class UserClient {
public:
    UserClient(std::shared_ptr<grpc::Channel> channel);
    UserClient(std::unique_ptr<game::User::StubInterface> stub);

public:
    std::string SayHello(const std::string& user);

private:
    std::unique_ptr<game::User::StubInterface> stub;
};


