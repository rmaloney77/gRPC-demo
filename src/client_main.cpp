#include "user_client.hpp"
#include <grpcpp/grpcpp.h>

int main(int argc, char **argv) {
    UserClient user_client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    std::string user("world");
    std::string reply = user_client.SayHello(user);
    std::cout << "Greeter received: " << reply << std::endl;
    return 0;
}
