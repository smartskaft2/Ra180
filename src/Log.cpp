
#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

namespace Ra180 {

    std::shared_ptr<spdlog::logger> Log::s_logger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T.%e, %l,\t%n]:\t%v%$"); // E.g. [19:25:06.234, Error, Ra180]: Bla, bla, bla... 

        s_logger = spdlog::stdout_color_mt("Ra180");
        s_logger->set_level(spdlog::level::trace);
        s_logger->trace("Ra180 logger initialized.");

    }

} // namespace Ra180