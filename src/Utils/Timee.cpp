#include "Utils/Timee.h"

#include <chrono>

namespace Ra180 { 

Time::SystemTime Time::System()
{
    return SystemClock::now();
}

Time::TimePoint Time::Local()
{
    return System2Local(System());
}

Time::TimePoint Time::System2Local(const SystemTime timePoint)
{
    const auto localTime = std::chrono::current_zone()->to_local(timePoint);
    return std::chrono::time_point_cast<Duration>(localTime);
}

} // namespace Ra180