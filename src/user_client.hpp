#include <iostream>
#include <memory>
#include <grpcpp/grpcpp.h>
#include <cstdint>
#include <vector>

#include "userservice.pb.h"
#include "userservice.grpc.pb.h"

class UserClient {
public:
    UserClient(std::shared_ptr<grpc::Channel> channel);
    UserClient(std::unique_ptr<game::User::StubInterface> stub);

public:
    bool UsernameAvailable(const std::string&);
    bool UsernameAvailableAsync(const std::string&);
    bool CreateUserDetails(game::UserDetails&);
    std::vector<game::GameStatistic> GetGameStatistics(uint32_t user_id, uint32_t game_id); 

public:
    //Unimplemented
    bool UsernameValid(const std::string&);
    bool EmailValid(const std::string&);
    game::UserDetails GetUserDetailsByUsername(const std::string&);
    game::UserDetails GetUserDetailsByUniqueID(uint32_t);
    bool UpdateUserDetails(game::UserDetails&);

private:
    std::unique_ptr<game::User::StubInterface> stub;
};


