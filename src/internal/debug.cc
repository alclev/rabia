#include "debug.h"
#include <iostream>
#include <string>
#include <cstdlib>

/* Debugging log */
void _log(const std::string& msg){
    std::cerr << msg << std::endl;
}

void _logf(const char* format, ...){
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

/* Error log and exit */
void _err(const std::string& msg){
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}
