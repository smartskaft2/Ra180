#pragma once

#include <chrono>

// Named Timee.h since Time.h seem to clash with time.h on Windows machines.

namespace Ra180 {

    struct Time
    {
        // Type aliases/abstractions
        using Duration    = std::chrono::milliseconds;
        using SystemClock = std::chrono::system_clock;
        using SystemTime  = std::chrono::system_clock::time_point;
        using TimePoint   = std::chrono::local_time<Duration>;

        // Methods 
        static SystemTime System();
        static TimePoint Local();

        // Conversions
        static TimePoint System2Local(const SystemTime timePoint);
    };

} // namespace Ra180

