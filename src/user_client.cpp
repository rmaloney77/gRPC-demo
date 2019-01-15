#include <grpcpp/grpcpp.h>
#include <cstdio>

#include "userservice.pb.h"
#include "userservice.grpc.pb.h"
#include "user_client.hpp"

UserClient::UserClient(std::shared_ptr<grpc::Channel> channel)
      : stub(game::User::NewStub(channel)) {
}

UserClient::UserClient(std::unique_ptr<game::User::StubInterface> stub) 
      : stub(std::move(stub)) {
}

bool UserClient::UsernameAvailable(const std::string &user) {
    game::UserDetails request;
    request.set_username(user);
    game::UserDetailsResponse resp;
    grpc::ClientContext context;
    grpc::Status status = stub->UsernameAvailable(&context, request, &resp);
    if (status.ok()) {
        return resp.result();
    } 
    fprintf(stderr, "RPC Failed (%d): %s\n", status.error_code(), status.error_message().c_str());
    return false; 
}

bool UserClient::UsernameAvailableAsync(const std::string& user) {
    game::UserDetails request;
    request.set_username(user);
    game::UserDetailsResponse resp;
    grpc::ClientContext context;
    grpc::CompletionQueue cq;
    grpc::Status status;
    std::unique_ptr<grpc::ClientAsyncResponseReaderInterface<game::UserDetailsResponse> > rpc(stub->PrepareAsyncUsernameAvailable(&context, request, &cq));
    rpc->StartCall();
    rpc->Finish(&resp, &status, (void*)1);
    void* got_tag;
    bool ok = false;
    GPR_ASSERT(cq.Next(&got_tag, &ok));
    GPR_ASSERT(got_tag == (void*)1);
    if (status.ok()) {
        return resp.result();
    } 
    fprintf(stderr, "RPC Failed (%d): %s\n", status.error_code(), status.error_message().c_str());
    return false; 
}

bool UserClient::CreateUserDetails(game::UserDetails &ud) {
    game::UserDetails resp;
    grpc::ClientContext context;
    grpc::Status status = stub->CreateUserDetails(&context, ud, &resp);
    if (status.ok()) {
        ud.set_id(resp.id());
        return true;
    } 
    fprintf(stderr, "RPC Failed (%d): %s\n", status.error_code(), status.error_message().c_str());
    resp.set_id(0);
    return false; 
}

std::vector<game::GameStatistic> UserClient::GetGameStatistics(uint32_t user_id, uint32_t game_id) {
    game::StatisticsRequest req;
    req.set_user_id(user_id);
    req.set_game_id(game_id);
    grpc::ClientContext context;
    std::unique_ptr<grpc::ClientReaderInterface<game::GameStatistic> > reader(stub->GetStatistics(&context, req));
    std::vector<game::GameStatistic> results;
    game::GameStatistic gs; 
    while (reader->Read(&gs)) {
        results.push_back(gs);
    }
    grpc::Status ignore = reader->Finish();
    return results;
}

bool UserClient::UsernameValid(const std::string&){
}

bool UserClient::EmailValid(const std::string&) {
}

game::UserDetails UserClient::GetUserDetailsByUsername(const std::string&) {
}    

game::UserDetails UserClient::GetUserDetailsByUniqueID(uint32_t id) {
}

bool UserClient::UpdateUserDetails(game::UserDetails&) {
}
