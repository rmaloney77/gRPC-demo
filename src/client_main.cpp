#include "user_client.hpp"

#include <cstdio>
#include <grpcpp/grpcpp.h>

int main(int argc, char **argv) {
    UserClient user_client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    std::string user("world");
    bool result = user_client.UsernameAvailable("test_user");
    fprintf(stdout, "Username Available: %d\n", result);

    std::vector<game::GameStatistic> stats = user_client.GetGameStatistics(0,0);
    fprintf(stdout, "%ld Statistics Returned\n", stats.size());

    return 0;
}
