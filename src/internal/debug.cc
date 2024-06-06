#include "debug.h"
#include <iostream>
#include <string>

void _log(const std::string& msg){
    std::cerr << msg << std::endl;
}
