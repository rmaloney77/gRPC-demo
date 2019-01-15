#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <grpcpp/grpcpp.h>
#include <memory>
#include "userservice.pb.h"
#include "userservice.grpc.pb.h"
#include "userservice_mock.grpc.pb.h"
#include "user_client.hpp"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::SetArgPointee;
using ::testing::Return;

TEST(user_service, check_username_avail) {
    std::unique_ptr<game::MockUserStub> stub(new game::MockUserStub());
    game::UserDetailsResponse resp;
    resp.set_result(true);
    EXPECT_CALL(*(stub.get()), UsernameAvailable(_,_,_)).Times(AtLeast(1)).WillOnce(DoAll(SetArgPointee<2>(resp), Return(grpc::Status::OK)));
    UserClient client(std::move(stub));
    bool result = client.UsernameAvailable("test_user");
    EXPECT_EQ(true, result);
}

TEST(user_service, create_details) {
    std::unique_ptr<game::MockUserStub> stub(new game::MockUserStub());
    game::UserDetails resp;
    resp.set_id(7);
    resp.set_username("test_user");
    resp.set_email("test@example.com");
    EXPECT_CALL(*(stub.get()), CreateUserDetails(_,_,_)).Times(AtLeast(1)).WillOnce(DoAll(SetArgPointee<2>(resp), Return(grpc::Status::OK)));
    UserClient client(std::move(stub));
    game::UserDetails user_details;
    user_details.set_id(0);
    user_details.set_username("test_user");
    user_details.set_email("test@example.com");
    bool result = client.CreateUserDetails(user_details);

    ASSERT_EQ(true, result);
    ASSERT_EQ(7, user_details.id());
}

