#include "user_client.hpp"

#include <cstdio>
#include <grpcpp/grpcpp.h>

int main(int argc, char **argv) {
    UserClient user_client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    std::string user("world");
    bool result = user_client.UsernameAvailableAsync("test_user");
    fprintf(stdout, "Username Available: %d\n", result);

    return 0;
}
