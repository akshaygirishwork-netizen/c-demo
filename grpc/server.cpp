#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "calc.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using calc::Calculator;
using calc::AddRequest;
using calc::AddReply;

class CalculatorServiceImpl final : public Calculator::Service {
public:
    Status Add(ServerContext* context,
               const AddRequest* request,
               AddReply* reply) override {

        int result = request->a() + request->b();
        std::cout << "Received: " << request->a()
                  << " + " << request->b() << std::endl;

        reply->set_result(result);
        return Status::OK;
    }
};

int main() {
    std::string server_address("0.0.0.0:50051");
    CalculatorServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address,
                             grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
    return 0;
}
