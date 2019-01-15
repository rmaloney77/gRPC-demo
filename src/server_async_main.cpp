#include <grpcpp/grpcpp.h>

#include "user_server.hpp"

//From https://github.com/grpc/grpc/blob/master/examples/cpp/helloworld/greeter_async_server.cc
class CallData {

    public:
        CallData(game::User::AsyncService* service, grpc::ServerCompletionQueue* cq)
            : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
          Proceed();
        }

    public:
        void Proceed() {
          if (status_ == CREATE) {
            status_ = PROCESS;
            service_->RequestUsernameAvailable(&ctx_, &request_, &responder_, cq_, cq_, this);
          } else if (status_ == PROCESS) {
            new CallData(service_, cq_);
            reply_.set_result(true);
            status_ = FINISH;
            responder_.Finish(reply_, grpc::Status::OK, this);
          } else {
            GPR_ASSERT(status_ == FINISH);
            delete this;
          }
        }

    private:
        game::User::AsyncService* service_;
        grpc::ServerCompletionQueue* cq_;
        grpc::ServerContext ctx_;
        game::UserDetails request_;
        game::UserDetailsResponse reply_;
        grpc::ServerAsyncResponseWriter<game::UserDetailsResponse> responder_;

        enum CallStatus { CREATE, PROCESS, FINISH };
        CallStatus status_;
};

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    game::User::AsyncService service;
    grpc::ServerBuilder builder;
    builder.SetOption(std::unique_ptr<grpc::ServerBuilderOption>(new NoReusePortOption));
    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    auto cq = builder.AddCompletionQueue();
    std::cout << "Starting Server!\n";
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    new CallData(&service, cq.get());
    void* tag;  
    bool ok;
    while (true) {
      GPR_ASSERT(cq->Next(&tag, &ok));
      GPR_ASSERT(ok);
      static_cast<CallData*>(tag)->Proceed();
    }
}
