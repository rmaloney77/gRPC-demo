#include <iostream>
#include <grpcpp/grpcpp.h>
#include <memory>

#include "userservice.pb.h"
#include "userservice.grpc.pb.h"

//Added an option for disabling RESUSEPORT on Windows Subsystem for Linux; implementation from:
//https://github.com/tensorflow/tensorflow/blob/master/tensorflow/core/distributed_runtime/rpc/grpc_server_lib.cc
class NoReusePortOption : public grpc::ServerBuilderOption {
    public:
        void UpdateArguments(grpc::ChannelArguments* args) override;
        void UpdatePlugins(std::vector<std::unique_ptr<::grpc::ServerBuilderPlugin>>* plugins) override;
};

class UserServiceImpl final : public game::User::Service {
    grpc::Status UsernameAvailable(grpc::ServerContext* context, const game::UserDetails *request, game::UserDetailsResponse *reply) override;
    grpc::Status CreateUserDetails(grpc::ServerContext* context, const game::UserDetails *request, game::UserDetails *reply) override;
    grpc::Status GetStatistics(grpc::ServerContext* context, const game::StatisticsRequest *request, grpc::ServerWriter<game::GameStatistic>* writer) override;
};

