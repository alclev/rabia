#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include <cstdlib>
#include <iostream>

struct Config {
    std::string Role;           // ctrl | svr | cli
    std::string Id;             // 0 | 1 | 2 | ...
    std::string ControllerAddr; // controller's ip:port
    std::string ProjectFolder;  // the project's folder
    std::string LogLevel;       // debug | info | warn

    // If Role == svr, the following 4 fields should be filled
    std::string SvrIp;           // server ip
    std::string ProxyPort;       // proxy port (connect by clients)
    std::string NetworkPort;     // network port (connect by all servers)
    std::vector<std::string> Peers; // the array of all servers' SvrIp:NetworkPort

    // If Role == cli, the following field should be filled
    std::string ProxyAddr; // the client proxy's SvrIp:ProxyPort

    // For all roles, the following fields should be filled
    bool ClosedLoop; // whether clients are closed-loop clients

    int NServers;            // the num. of server instances
    int NFaulty;             // the num. of faulty servers (< 1/2 NServers)
    int NClients;            // the num. of clients
    int NConcurrency;        // the num. of concurrent consensus instances (= concurrency >= 1)
    int NClientRequests;     // the num. of requests PER client, open-loop only
    int ClientThinkTime;     // the think time between sending two requests (ms)
    int ClientBatchSize;     // the num. of DB operations in a client's request
    int ProxyBatchSize;      // the num. of client requests in a consensus object
    std::chrono::milliseconds ProxyBatchTimeout; // the max. time between submitting requests (ms, Millisecond)
    int NetworkBatchSize;    // reserved
    std::chrono::milliseconds NetworkBatchTimeout; // reserved (ms, Millisecond)

    int NMinusF;       // the "constant" n - f
    int Majority;
    int MajorityPlusF;
    int FaultyPlusOne;

    uint32_t LenLedger;     // the length of a ledger ring buffer
    int LenBlockArray;      // the length of each ledger block's array
    int LenChannel;         // the length of buffer channels (excepted the channel Q in a Block Block)
    int LenPQueue;          // the length of each priority queue's initial capacity in a consensus instance
    int IoBufSize;          // the size of each underlying buffer in bufio.Reader and bufio.Writer
    int TcpBufSize;         // the size of each TCP write buffer and TCP read buffer
    int KeyLen;             // the length of KV-store key string
    int ValLen;             // the length of KV-store value string

    std::chrono::milliseconds SvrLogInterval;    // a server logger's sleep time after generating a log
    std::chrono::milliseconds ClientLogInterval; // a client logger's sleep time after generating a log
    std::chrono::milliseconds ClientTimeout;     // closed-loop only, a client exits after ClientTimeout
    std::chrono::milliseconds ConsensusStartAfter; // after this time, the consensus executor will start working (this variable is for saturating the system with open-loop clients)
    int StorageMode;         // 0: the dictionary KV store, 1: Redis GET&SET, 2: Redis MGET&MSET
    std::vector<std::string> RedisAddr;

    void printConfig();
};

void loadConfigs(Config &config);
void loadEnvVars1(Config &config);
void loadEnvVars2(Config &config);
void CalcConstants(Config &config);

