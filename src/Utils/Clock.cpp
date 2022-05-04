#include "Utils/Clock.h"
#include "Utils/Log.h"
#include "Utils/Timee.h"

#include <atomic>
#include <thread>
#include <type_traits>

namespace Ra180 {

    int Clock::AddTickedCallback(std::function<void()> callback)
    {
        static int nextID{ 0 };
        _callbacks.push_back(std::make_pair(nextID, callback));
        return nextID++;
    }

    void Clock::RemoveTickedCallback(const int callbackID)
    {
        _callbacks.erase(std::remove_if(_callbacks.begin(), _callbacks.end(), [callbackID](const auto& idCbPair)
        {
            return idCbPair.first == callbackID;
        }));
    }

    void Clock::Initialize(const Time::TimePoint time)
    {
        _time.store(time);
        RA180_LOG_INFO("Clock initialized to {0}, with {1:d} callbacks.", std::format("{:%H:%M:%S}", time), _callbacks.size());
        _thread = std::thread([&] { Run(); });
    }

    void Clock::TickClock()
    {
        _lastTicked = Time::SystemClock::now();
        _time.store(_time.load() + Tick(1));
    }

    void Clock::Run()
    {
        Time::SystemTime nextTick;

        // Runs until program terminates
        while (true)
        {
            // Tick clock
            TickClock();
            nextTick = _lastTicked + Tick(1);

            // Run callbacks
            for (const auto& callback : _callbacks)
            {
                callback.second();
            }

            // Sleep until next tick
            std::this_thread::sleep_until(nextTick - PreTick(1));
            while (Time::SystemClock::now() < nextTick)
                ;
        }
    }

} // namespace Ra180