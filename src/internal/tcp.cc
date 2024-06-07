#include "debug.h"
#include "tcp.h"

namespace server_tcp{
/* Initialize server and return (server, client) socket */
    int connect(){
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if(serverSocker < 0){
            _err("Error creating socket");
        }
        sockaddr_in serverAddr;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(PORT);
#ifdef DEBUG
        _logf("Server socket created with address %s and port %d", inet_ntoa(serverAddress.sin_addr), ntohs(serverAddress.sin_port));   
#endif
        if(bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
            _err("Error binding socket");
        }
        /* 5 is the backlog value for the pending connections on the serverSocket */
        if(listen(serverSocket, 5) < 0){
            _err("Error listening on socket");
        }
        sockaddr_in clientAddress;
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, sizeof(clientAddress));
        if(clientSocket < 0){
            _err("Error accepting connection");
        }
#ifdef DEBUG
        _logf("Client connected with address %s and port %d", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
#endif
        return std::make_pair(serverSocket, clientSocket);
    }
    void send(int client_sd, const std::vector<byte> &data){
        if(send(client_sd, data.data(), data.size(), 0) < 0){
            _err("Error sending data");
        }
#ifdef DEBUG
        _logf("Bytes sent to client with socket descriptor %d", client_sd);
#endif
    }
    void recv(int client_sd, std::vector<byte> &data){
        data.resize(BUFFER_SIZE);
        int n = recv(client_sd, data.data(), data.size(), 0);
        if(n < 0){
            _err("Error receiving data");
        }
        data.resize(n);
#ifdef DEBUG
        _logf("Bytes received from client with socket descriptor %d", client_sd);
#endif
    }
    void close_server(int ){
        close(server_sd);
#ifdef DEBUG
        _logf("Client socket descriptor %d closed", client_sd);
#endif
    }
}

namespace client_tcp{
    int connect(){
        int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if(clientSocket < 0){
            _err("Error creating socket");
        }
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
        serverAddress.sin_port = htons(PORT);
#ifdef DEBUG
        _logf("Server socket created with address %s and port %d", inet_ntoa(serverAddress.sin_addr), ntohs(serverAddress.sin_port));
#endif
        if(connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
            _err("Error connecting to server");
        }
#ifdef DEBUG
        _logf("Connected to server with address %s and port %d", inet_ntoa(serverAddress.sin_addr), ntohs(serverAddress.sin_port));
#endif
        return clientSocket;
    }
    void send(int client_sd, const std::vector<byte> &data){
        if(send(client_sd, data.data(), data.size(), 0) < 0){
            _err("Error sending data");
        }
#ifdef DEBUG
        _logf("Bytes sent to server with socket descriptor %d", client_sd);
#endif
    }
    void recv(int client_sd, std::vector<byte> &data){
        data.resize(BUFFER_SIZE);
        int n = recv(client_sd, data.data(), data.size(), 0);
        if(n < 0){
            _err("Error receiving data");
        }
        data.resize(n); 
#ifdef DEBUG
        _logf("Bytes received from server with socket descriptor %d", client_sd);
#endif
    }
    void close_client(int client_sd){
        close(client_sd);
#ifdef DEBUG
        _logf("Server socket descriptor %d closed", client_sd);
#endif
    }
}
