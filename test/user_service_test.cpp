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

TEST(user_service, create_details) {
    std::unique_ptr<game::MockUserStub> stub(new game::MockUserStub());
    game::HelloReply resp;
    resp.set_message("(Mock)Hello world");
    EXPECT_CALL(*(stub.get()), SayHello(_,_,_)).Times(AtLeast(1)).WillOnce(DoAll(SetArgPointee<2>(resp), Return(grpc::Status::OK)));
    UserClient client(std::move(stub));
    std::string resp_str = client.SayHello("Hello!");

    ASSERT_STREQ("(Mock)Hello world", resp_str.c_str());
}

TEST(user_service, update_details) {
      EXPECT_EQ(1, 1);
}


