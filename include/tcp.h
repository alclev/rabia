#pragma once 

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <utility>

// Define the buffer size, port, and server IP
constexpr int BUFFER_SIZE = 1024;
constexpr int PORT = 8080;
constexpr const char* SERVER_IP = "127.0.0.1";

// Alias for byte type
typedef uint8_t byte;

namespace server_tcp {

    // Initialize server and return (server, client) socket
    std::pair<int, int> connect();

    // Send data to the client
    void send(int client_sd, const std::vector<byte> &data);

    // Receive data from the client
    void recv(int client_sd, std::vector<byte> &data);

    // Close the server socket
    void close_server(int server_sd);
}

namespace client_tcp {

    // Initialize client and connect to the server
    int connect();

    // Send data to the server
    void send(int client_sd, const std::vector<byte> &data);

    // Receive data from the server
    void recv(int client_sd, std::vector<byte> &data);

    // Close the client socket
    void close_client(int client_sd);
}
