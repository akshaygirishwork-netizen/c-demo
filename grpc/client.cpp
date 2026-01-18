#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "calc.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using calc::Calculator;
using calc::AddRequest;
using calc::AddReply;

class CalculatorClient {
public:
    CalculatorClient(std::shared_ptr<Channel> channel)
        : stub_(Calculator::NewStub(channel)) {}

    int Add(int a, int b) {
        AddRequest request;
        request.set_a(a);
        request.set_b(b);

        AddReply reply;
        ClientContext context;

        Status status = stub_->Add(&context, request, &reply);

        if (status.ok()) {
            return reply.result();
        } else {
            std::cout << "RPC failed" << std::endl;
            return -1;
        }
    }

private:
    std::unique_ptr<Calculator::Stub> stub_;
};

int main() {
    CalculatorClient client(
        grpc::CreateChannel("localhost:50051",
                             grpc::InsecureChannelCredentials()));

    int result = client.Add(10, 20);
    std::cout << "Result from server: " << result << std::endl;

    return 0;
}
