#pragma once

#include "spdlog/spdlog.h"
#include <memory>

namespace Ra180 {

    class Log
    {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetLogger() { return s_logger; }

    private:
        static std::shared_ptr<spdlog::logger> s_logger;
    };

} // namespace Ra180

// Log macros
#define RA180_LOG_DEBUG(...)   ::Ra180::Log::GetLogger()->debug(__VA_ARGS__)
#define RA180_LOG_TRACE(...)   ::Ra180::Log::GetLogger()->trace(__VA_ARGS__)
#define RA180_LOG_INFO(...)    ::Ra180::Log::GetLogger()->info(__VA_ARGS__)
#define RA180_LOG_WARNING(...) ::Ra180::Log::GetLogger()->warn(__VA_ARGS__)
#define RA180_LOG_ERROR(...)   ::Ra180::Log::GetLogger()->error(__VA_ARGS__)
#define RA180_LOG_FATAL(...)   ::Ra180::Log::GetLogger()->fatal(__VA_ARGS__)