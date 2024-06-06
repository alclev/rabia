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

namespace Logger {

/* Generates the log file path for a to-file logger, located in Rabia's "logs" folder */
std::string GetLogFilePathAndName(Config &c, const std::string &component, uint32_t svrId, uint32_t subId) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer),
             "logs/ns%d-nf%d-nc%d-nC%d-to%ld-tt%d-cb%d-pb%d-pt%ld-nb%d-nt%ld--%s-%d-%d.log",
             c.NServers, c.NFaulty, c.NClients, c.NConcurrency,
             static_cast<int64_t>(c.ClientTimeout.count()), c.ClientThinkTime, c.ClientBatchSize,
             c.ProxyBatchSize, static_cast<int64_t>(c.ProxyBatchTimeout.count()), c.NetworkBatchSize,
             static_cast<int64_t>(c.NetworkBatchTimeout.count()), component.c_str(), svrId, subId);
    return (std::filesystem::path(c.ProjectFolder) / buffer).string();
}

/* Converts Conf.LogLevel to spdlog's log level
 */spdlog::level::level_enum GetLogLevel(Config &c) {
    const std::string& level = c.LogLevel;
    if (level == "debug") return spdlog::level::debug;
    if (level == "info") return spdlog::level::info;
    if (level == "warn") return spdlog::level::warn;
    return spdlog::level::debug;  // Default to debug level
}

/* Initializes a spdlog Logger */
std::shared_ptr<spdlog::logger> InitLogger(Config &c, const std::string& component, uint32_t svrId, uint32_t subId, const std::string& loggerType) {
    // Create log folder if necessary

    std::filesystem::create_directories(c.ProjectFolder + "/logs");

    // Set the global log level
    spdlog::set_level(GetLogLevel(c));

    // Generate the log file's path and name
    auto logFilePath = GetLogFilePathAndName(c, component, svrId, subId);

    if (loggerType == "terminal") {
        return spdlog::stdout_color_mt(component);
    }
    if (loggerType == "file") {
        return spdlog::basic_logger_mt(component, logFilePath);
    }
    if (loggerType == "both") {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath, true);
        spdlog::sinks_init_list sink_list = { console_sink, file_sink };
        return std::make_shared<spdlog::logger>(component, sink_list);
    }

    throw std::invalid_argument("Invalid logger type");
}

} 