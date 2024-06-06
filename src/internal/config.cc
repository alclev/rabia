#include "config.h"
#include <sstream>

void loadConfigs(Config &config){
#ifdef DEBUG
    _log("loadConfigs called");
#endif
    loadEnvVars1(config);
    loadEnvVars2(config);
    CalcConstants(config);
    /* Placeholder for Redis */
}

void loadEnvVars1(Config &c) {
#ifdef DEBUG
    _log("loadEnvVars1 called");
#endif
    if (const char* role = std::getenv("RC_Role")) {
        c.Role = role;
    }
    else if (const char* projectFolder = std::getenv("RC_Folder")) {
        c.ProjectFolder = projectFolder;
    }
    else if (const char* svrIp = std::getenv("RC_SvrIp")) {
        c.SvrIp = svrIp;
    }
    else if (const char* proxyPort = std::getenv("RC_PPort")) {
        c.ProxyPort = proxyPort;
    }
    else if (const char* networkPort = std::getenv("RC_NPort")) {
        c.NetworkPort = networkPort;
    }
    else if (const char* peers = std::getenv("RC_Peers")) {
        std::istringstream ss(peers);
        std::string peer;
        while (std::getline(ss, peer, ' ')) {
            c.Peers.push_back(peer);
        }
    }
    else if (const char* proxyAddr = std::getenv("RC_Proxy")) {
        c.ProxyAddr = proxyAddr;
    }
}

void loadEnvVars2(Config &c) {
#ifdef DEBUG
    _log("loadEnvVars2 called");
#endif
    if (const char* controllerAddr = std::getenv("RC_Ctrl")) {
        c.ControllerAddr = controllerAddr;
    }
    else if (const char* logLevel = std::getenv("RC_LLevel")) {
        c.LogLevel = logLevel;
    }
    else if (const char* closedLoop = std::getenv("Rabia_ClosedLoop")) {
        c.ClosedLoop = std::string(closedLoop) == "true";
    }
    else if (const char* nServers = std::getenv("Rabia_NServers")) {
        c.NServers = std::stoi(nServers);
    }
    else if (const char* nFaulty = std::getenv("Rabia_NFaulty")) {
        c.NFaulty = std::stoi(nFaulty);
    }
    else if (const char* nClients = std::getenv("Rabia_NClients")) {
        c.NClients = std::stoi(nClients);
    }
    else if (const char* clientNRequests = std::getenv("Rabia_ClientNRequests")) {
        c.NClientRequests = std::stoi(clientNRequests);
    }
    else if (const char* clientThinkTime = std::getenv("Rabia_ClientThinkTime")) {
        c.ClientThinkTime = std::stoi(clientThinkTime);
    }
    else if (const char* clientBatchSize = std::getenv("Rabia_ClientBatchSize")) {
        c.ClientBatchSize = std::stoi(clientBatchSize);
    }
    else if (const char* proxyBatchSize = std::getenv("Rabia_ProxyBatchSize")) {
        c.ProxyBatchSize = std::stoi(proxyBatchSize);
    }
    else if (const char* proxyBatchTimeout = std::getenv("Rabia_ProxyBatchTimeout")) {
        c.ProxyBatchTimeout = std::chrono::milliseconds(std::stoi(proxyBatchTimeout));
    }
    else if (const char* networkBatchSize = std::getenv("Rabia_NetworkBatchSize")) {
        c.NetworkBatchSize = std::stoi(networkBatchSize);
    }
    else if (const char* networkBatchTimeout = std::getenv("Rabia_NetworkBatchTimeout")) {
        c.NetworkBatchTimeout = std::chrono::milliseconds(std::stoi(networkBatchTimeout));
    }
    else if (const char* clientTimeout = std::getenv("Rabia_ClientTimeout")) {
        c.ClientTimeout = std::chrono::seconds(std::stoi(clientTimeout));
    }
}

void CalcConstants(Config &c){
#ifdef DEBUG
    _log("CalcConstants called");
#endif
    c.NMinusF = c.NServers - c.NFaulty;
	c.Majority = c.NServers/2 + 1;
	c.MajorityPlusF = c.NServers/2 + c.NFaulty + 1;
	c.FaultyPlusOne = c.NFaulty + 1;

	if (c.NClientRequests == 0) {
		c.NClientRequests = 10000000; // the default value
	}
	c.LenLedger = 10000;
	c.LenBlockArray = 10;
	c.LenChannel = 500000;

	c.IoBufSize = 4096 * 4000;
	c.TcpBufSize = 7000000;
	c.KeyLen = 8;
	c.ValLen = 8;

    int time_factor = 1000;

	c.SvrLogInterval = std::chrono::milliseconds(4 * time_factor);
	c.ClientLogInterval = std::chrono::milliseconds(15 * time_factor);
	c.ConsensusStartAfter = std::chrono::milliseconds(0 * time_factor); // for open-loop testings, redundant?
}

void Config::printConfig(){
#ifdef DEBUG
    _log("Config::printConfig called");
#endif
    std::cout << "Role: " << Role << std::endl;
    std::cout << "Id: " << Id << std::endl;
    std::cout << "ControllerAddr: " << ControllerAddr << std::endl;
    std::cout << "ProjectFolder: " << ProjectFolder << std::endl;
    std::cout << "LogLevel: " << LogLevel << std::endl;
    std::cout << "SvrIp: " << SvrIp << std::endl;
    std::cout << "ProxyPort: " << ProxyPort << std::endl;
    std::cout << "NetworkPort: " << NetworkPort << std::endl;
    std::cout << "Peers: ";
    for (const auto& peer : Peers) {
        std::cout << peer << " ";
    }
    std::cout << std::endl;
    std::cout << "ProxyAddr: " << ProxyAddr << std::endl;
    std::cout << "ClosedLoop: " << ClosedLoop << std::endl;
    std::cout << "NServers: " << NServers << std::endl;
    std::cout << "NFaulty: " << NFaulty << std::endl;
    std::cout << "NClients: " << NClients << std::endl;
    std::cout << "NConcurrency: " << NConcurrency << std::endl;
    std::cout << "NClientRequests: " << NClientRequests << std::endl;
    std::cout << "ClientThinkTime: " << ClientThinkTime << std::endl;
    std::cout << "ClientBatchSize: " << ClientBatchSize << std::endl;
    std::cout << "ProxyBatchSize: " << ProxyBatchSize << std::endl;
    std::cout << "ProxyBatchTimeout: " << ProxyBatchTimeout.count() << std::endl;
    std::cout << "NetworkBatchSize: " << NetworkBatchSize << std::endl;
    std::cout << "NetworkBatchTimeout: " << NetworkBatchTimeout.count() << std::endl;
    std::cout << "NMinusF: " << NMinusF << std::endl;
    std::cout << "Majority: " << Majority << std::endl;
    std::cout << "MajorityPlusF: " << MajorityPlusF << std::endl;
    std::cout << "FaultyPlusOne: " << FaultyPlusOne << std::endl;
    std::cout << "LenLedger: " << LenLedger << std::endl;
    std::cout << "LenBlockArray: " << LenBlockArray << std::endl;
    std::cout << "LenChannel: " << LenChannel << std::endl;
    std::cout << "LenPQueue: " << LenPQueue << std::endl;
    std::cout << "IoBufSize: " << IoBufSize << std::endl;
    std::cout << "TcpBufSize: " << TcpBufSize << std::endl;
    std::cout << "KeyLen: " << KeyLen << std::endl;
    std::cout << "ValLen: " << ValLen << std::endl;
    std::cout << "SvrLogInterval: " << SvrLogInterval.count() << std::endl;
    std::cout << "ClientLogInterval: " << ClientLogInterval.count() << std::endl;
    std::cout << "ClientTimeout: " << ClientTimeout.count() << std::endl;
    std::cout << "ConsensusStartAfter: " << ConsensusStartAfter.count() << std::endl;
    std::cout << "StorageMode: " << StorageMode << std::endl;
    std::cout << "RedisAddr: ";
    for (const auto& addr : RedisAddr) {
        std::cout << addr << " ";
    }
    std::cout << std::endl;
}