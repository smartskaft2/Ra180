#pragma once

#include <atomic>
#include <chrono>
#include <functional>
#include <thread>
#include <vector>
#include <mutex>

namespace Ra180 {

    class Timer
    {
    public:
        Timer();

        int SetTimeout(const std::chrono::milliseconds timeout,
                       const std::function<void()>     callback = nullptr,
                       const bool                      recurring = false);
        bool StopTimeout(const int timeoutID, const bool suppressWarning = false);

    private:
        using Clock = std::chrono::system_clock;
        struct Timeout;

    private:
        int InsertTimeout(Timeout&& timeout);

        void Run();
        void HandleTimeouts();
        void Sleep();

    private:
        std::vector<Timeout>    _timeouts{};              // Sorted timeouts (near to far in time)
        std::thread             _thread{};                // The timer's thread
        std::mutex              _mutex{};                 // Used for thread safety when accessing the timeouts vector
        std::condition_variable _wakeUpCondition{};       // Used to notify sleeping thread of changed timeouts vector
        std::atomic<bool>       _timeoutsChanged{ false }; // Used for predicates during thread sleep
        std::atomic<bool>       _alive{ true };
    };


    struct Timer::Timeout {

        //Timeout(std::chrono::milliseconds timeout, std::function<void()> callback = nullptr, bool recurring = false);

        /*Timeout() = default;
        Timeout(const Timeout&)            = default;
        Timeout(Timeout&&)                 = default;
        Timeout& operator=(const Timeout&) = default;
        Timeout& operator=(Timeout&&)      = default;
        ~Timeout()                         = default;*/

        bool operator<(const Timeout & rhs) const;
        static int GenerateID();

        std::chrono::milliseconds      _timeout{ 0 };
        std::function<void()>          _callback{ nullptr };
        bool                           _recurring{ false };

        std::chrono::time_point<Clock> _timeoutPoint{ Clock::now() + _timeout };
        int                            _id{ GenerateID() };

    };

    inline Timer& GlobalTimer()
    {
        static Timer timer{};
        return timer;
    }

} // namespace Ra180

