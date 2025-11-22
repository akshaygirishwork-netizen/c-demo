
# gRPC

gRPC is a high-performance Remote Procedure Call (RPC) framework developed by Google.
It allows a client application to directly call functions on a remote server as if it were a local function.

It uses HTTP/2 for transport and Protocol Buffers (Protobuf) as the data format, making communication fast, efficient, and language-independent.

# How gRPC Communication Works Between Systems

gRPC allows two systems — a client and a server — to communicate with each other over a network using remote procedure calls (RPCs).

The communication happens over HTTP/2, and the data exchanged is serialized using Protocol Buffers (Protobuf), which makes it lightweight and fast.

## Advantages of gRPC

### High Performance:
Uses HTTP/2, which supports multiplexing and binary data — faster and lighter than REST or plain TCP.

### Efficient Data Format:
Uses Protocol Buffers, which are smaller and faster than JSON or XML.

### Cross-Language Support:
Works across many languages like C++, Python, Go, Java, etc., with automatic code generation.

### Real-Time Communication:
Supports streaming — client and server can send continuous data (useful for live updates).

### Strongly Typed APIs:
Service interfaces and message structures are defined in .proto files — reducing errors and making communication predictable.

Built-in Error Handling and Security:
Provides standard status codes.
