#pragma once

#include <string> 
#include <memory> // std::shared_ptr
#include <spdlog/spdlog.h> // spdlog::level::level_enum and spdlog::logger

std::string GetLogFilePathAndName(Config &c, const std::string &component, uint32_t svrId, uint32_t subId);

spdlog::level::level_enum GetLogLevel(Config &c);

std::shared_ptr<spdlog::logger> InitLogger(Config &c, const std::string& component, uint32_t svrId, uint32_t subId, const std::string& loggerType);