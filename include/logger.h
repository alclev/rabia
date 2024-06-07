#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <filesystem>
#include <string>
#include <stdexcept>
#include <chrono>
#include <cstdint>
#include <memory>

#include "config.h"  
#include "debug.h"

namespace Logger{
    std::string GetLogFilePathAndName(Config &c, const std::string &component, uint32_t svrId, uint32_t subId);

    spdlog::level::level_enum GetLogLevel(Config &c);

    std::shared_ptr<spdlog::logger> InitLogger(Config &c, const std::string& component, uint32_t svrId, uint32_t subId, const std::string& loggerType);
}