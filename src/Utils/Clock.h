#pragma once

#include "Utils/Log.h"
#include "Utils/Timee.h"

#include <atomic>
#include <thread>
#include <type_traits>

namespace Ra180 {

    class Clock
    {
        using Tick    = std::chrono::duration<int, std::ratio<1>>;      // 1 second
        using PreTick = std::chrono::duration<int, std::ratio<1,1000>>; // 1 millisecond

    public:
        int  AddTickedCallback(std::function<void()> callback);
        void RemoveTickedCallback(const int callbackID);
        void Initialize(const Time::TimePoint time = Time::Local() );

        inline Time::TimePoint Time() const { return _time.load(); }
        inline void SetTime(const Time::TimePoint time) { _time.store(time); }

    private:
        void TickClock();
        void Run();

    private:
        std::atomic<Time::TimePoint> _time       = Time::Local();
        Time::SystemTime             _lastTicked = Time::System();
        std::thread                  _thread     = std::thread{};

        std::vector<std::pair<int, std::function<void()>>> _callbacks{};
    };

} // namespace Ra180