#pragma once

#include <chrono>
#include <thread>

namespace Ra180 {

    template <class TClock, class TDuration>
    void SleepUntil(std::chrono::time_point<TClock, TDuration> timePoint)
    {
        std::this_thread::sleep_until(timePoint - 10us);
        while (timePoint >= TClock::now())
            ;
    }

} // namespace Ra180 