#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <cstdint>
#include "config.h"
#include "debug.h"

void proxyRun(uint32_t idx){

}

void runServer(uint32_t idx){

}

void runClient(uint32_t idx){

}

int main(){
    Config config;
    loadConfigs(config);
#ifdef DEBUG
    _log("----DEBUGGING LOG----");
#endif

    try{
        std::unordered_map<std::string, int> roleMap = { {"ctrl", 0}, {"svr", 1}, {"cli", 2} };
        auto role = roleMap.find(config.Role);
        if(role == roleMap.end())
            throw std::runtime_error("Invalid role");
        switch(role->second){
            case 0:
                /* Controller */
#ifdef DEBUG
                _log("Controller");
#endif

                break;
            case 1:
                /* Server */
#ifdef DEBUG
                _log("Server");
#endif
                break;
            case 2:
                /* Client */
#ifdef DEBUG
                _log("Client");
#endif
                break;
            default:
                std::cout << "Invalid role" << std::endl;
                return EXIT_FAILURE;
        }
    } catch (const std::exception& e) {
        std::ostringstream oss;
        oss << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}