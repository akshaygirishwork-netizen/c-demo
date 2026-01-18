CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

PROTO_SRC = calc.pb.cc calc.grpc.pb.cc
PROTO_HDR = calc.pb.h calc.grpc.pb.h

GRPC_CFLAGS = $(shell pkg-config --cflags grpc++ protobuf)
GRPC_LIBS   = $(shell pkg-config --libs grpc++ protobuf)

SERVER = server
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): server.cpp $(PROTO_SRC) $(PROTO_HDR)
	$(CXX) $(CXXFLAGS) server.cpp $(PROTO_SRC) \
	$(GRPC_CFLAGS) $(GRPC_LIBS) -o $(SERVER)

$(CLIENT): client.cpp $(PROTO_SRC) $(PROTO_HDR)
	$(CXX) $(CXXFLAGS) client.cpp $(PROTO_SRC) \
	$(GRPC_CFLAGS) $(GRPC_LIBS) -o $(CLIENT)

proto:
	protoc --cpp_out=. --grpc_out=. \
	--plugin=protoc-gen-grpc=`which grpc_cpp_plugin` \
	calc.proto

clean:
	rm -f $(SERVER) $(CLIENT) *.o *.pb.cc *.pb.h *.grpc.pb.cc *.grpc.pb.h

.PHONY: all proto clean
