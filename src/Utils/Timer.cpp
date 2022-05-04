#include "Utils/Log.h"
#include "Utils/Timer.h"
#include "Utils/toString.h"

#include <vector>
#include <chrono>
#include <thread>
#include <functional>

namespace Ra180 {

    //Timer::Timeout::Timeout(std::chrono::milliseconds timeout, std::function<void()> callback, bool recurring)
    //    : _timeout(timeout), _timeoutPoint(Clock::now() + _timeout), _callback(callback), _recurring(recurring)
    //{
    //    static std::atomic<int> id{};
    //    ++id;
    //    _id = id.load();
    //}

    int Timer::Timeout::GenerateID()
    {
        static std::atomic<int> id{};
        ++id;
        return id.load();
    }

    bool Timer::Timeout::operator<(const Timeout& rhs) const
    {
        return rhs._timeoutPoint <= _timeoutPoint;
    }

    Timer::Timer()
    {
        _thread = std::thread(&Timer::Run, std::ref(*this));
        RA180_LOG_TRACE("Timer created on thread {}.", toString(_thread.get_id()));
        _thread.detach();
    }

    int Timer::InsertTimeout(Timeout&& timeout)
    {
        int id = timeout._id;
        _timeouts.insert(std::lower_bound(_timeouts.begin(), _timeouts.end(), timeout),
                         std::move(timeout));
        return id;
    }
 
    int Timer::SetTimeout(const std::chrono::milliseconds timeout,
                          const std::function<void()>     callback,
                          const bool                      recurring)
    {
        int id;
        {
            // Lock thread - unlocked when leaving function
            std::lock_guard<std::mutex> lock(_mutex);

            // Insert Timeout in sorted vector
            id = InsertTimeout({timeout, callback, recurring});
        }
        RA180_LOG_TRACE("Timer: Timeout set (id: {:d}).", id);

        // Wake up the thread for re-calcuation of sleep time
        _timeoutsChanged.store(true);
        _wakeUpCondition.notify_one();

        // Return the timeout ID
        return id;
    }

    bool Timer::StopTimeout(const int timeoutID, const bool suppressWarning)
    {
        bool timeoutChanged{ false };
        {
            // Lock thread - unlocked when leaving function
            std::lock_guard<std::mutex> lock(_mutex);

            // Find timeout
            auto it = std::find_if(_timeouts.begin(), _timeouts.end(), [=](const Timeout& timeout)
            {
                return timeoutID == timeout._id;
            });

            // Found? Erase it!
            if (it != _timeouts.end())
            {
                _timeouts.erase(it);
                timeoutChanged = true; // Sucesss!
                RA180_LOG_TRACE("Timer: Timeout unset (id: {:d}).", timeoutID);
            }

            // Else, log warning
            else if (!suppressWarning)
            {
                RA180_LOG_WARNING("Attempt to unset an invalid timeout. The ID {} do not match any active timeouts.", timeoutID);
            }
        }

        if (timeoutChanged)
        {
            _timeoutsChanged.store(true);
            _wakeUpCondition.notify_one();
        }

        return timeoutChanged;
    }
    
    
    void Timer::Run()
    {
        while (_alive)
        {
            Sleep();
            HandleTimeouts();
        }
    }

    void Timer::HandleTimeouts()
    {
        std::lock_guard<std::mutex> lock(_mutex);

        // Exit early if no timeouts
        if (_timeouts.empty())
        {
            return;
        }

        // If called early, wait for timeout point
        while (Clock::now() <= _timeouts.back()._timeoutPoint)
        {
        }

        // For each passed timeout point, run its callback and remove it away
        bool doReSort{ false };
        for (long n{ (long)_timeouts.size() - 1}; n >= 0; --n)
        {
            if (Clock::now() < _timeouts.at(n)._timeoutPoint)
                break;

            /*RA180_LOG_TRACE("Timer: Timeout! (id: {:d})", _timeouts.at(n)._id);*/
            _timeouts.at(n)._callback();

            if (_timeouts.at(n)._recurring)
            {
                _timeouts.at(n)._timeoutPoint += _timeouts.at(n)._timeout;
                doReSort = true;
            }
            else
            {
                _timeouts.erase(_timeouts.begin() + n);
            }
        }

        if (doReSort)
            std::sort(_timeouts.begin(), _timeouts.end());
    }

    void Timer::Sleep()
    {
        using namespace std::chrono_literals;

        // Helper lambda, to make thread sleep again on spurious wake ups
        const auto timeoutsChanged = [&] { return _timeoutsChanged.load(); };

        // Lock thread, wait for timeout or changed timeout vector
        std::unique_lock<std::mutex> lock( _mutex );

        // If no timeouts -> Sleep until timeout is added
        while (_timeouts.empty())
        {
            _timeoutsChanged.store(false);
            _wakeUpCondition.wait(lock, timeoutsChanged);
        }

        // Sleep until right before the next timeout. Reset timeouts changed flag
        const auto wakeUpPoint = _timeouts.back()._timeoutPoint - 100ns;
        _timeoutsChanged.store(false);
        _wakeUpCondition.wait_until(lock, wakeUpPoint, timeoutsChanged);
    }

} // namespace Ra180

