#include <iostream>
#include <memory>

#include "user_server.hpp"

void NoReusePortOption::UpdateArguments(grpc::ChannelArguments* args) {
    args->SetInt(GRPC_ARG_ALLOW_REUSEPORT, 0);
}

void NoReusePortOption::UpdatePlugins(std::vector<std::unique_ptr<::grpc::ServerBuilderPlugin>>*plugins) {
}

grpc::Status UserServiceImpl::UsernameAvailable(grpc::ServerContext* context, const game::UserDetails *request, game::UserDetailsResponse *reply) {
    reply->set_result(true);
    return grpc::Status::OK;
}

grpc::Status UserServiceImpl::CreateUserDetails(grpc::ServerContext* context, const game::UserDetails *request, game::UserDetails *reply) {
    reply->set_id(7);
    reply->set_username(request->username());
    reply->set_email(request->email());
    return grpc::Status::OK;
}


grpc::Status UserServiceImpl::GetStatistics(grpc::ServerContext* context, const game::StatisticsRequest *request, grpc::ServerWriter<game::GameStatistic>* writer) {
    game::GameStatistic stat[3];
    for (size_t i = 0; i < 3; ++i) {
        writer->Write(stat[i]);
    }
    return grpc::Status::OK;
}
