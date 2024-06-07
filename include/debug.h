#pragma once

#include <string>
#include <cstdarg>

void _log(const std::string& msg);

void _logf(const char* format, ...);

void _err(const std::string& msg);