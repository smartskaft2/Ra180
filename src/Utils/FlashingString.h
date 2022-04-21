#pragma once

#include "Radio/IDisplay.h"
#include "Utils/Timer.h"

#include <string>
#include <string_view>
#include <chrono>
#include <atomic>
#include <mutex>
#include <thread>

namespace Ra180 {

    class FlashingString
    {
    public:
        FlashingString(IDisplay& display, 
                       Timer& timer, 
                       const std::chrono::milliseconds rate = std::chrono::milliseconds{600});

        ~FlashingString();

        const std::string& String() const;
        const char* const c_str() const;

        void Start();
        void Stop();
        bool IsFlashing() const;

        void Set(std::string string);
        void Append(std::string_view string);
        void Pop(std::size_t n = 1);

        bool Compare(std::string_view stringView) const;

    public:
        FlashingString& operator+=(std::string_view stringView);

    private:
        void Flash();
        std::mutex& MutexForImmutable() const;

    private:
        IDisplay& _display;
        Timer&    _timer;
        const std::chrono::milliseconds _rate;
        std::string _string{};
        int         _timeoutID{-1};
        bool        _visible{false};
        std::mutex  _mutex{};
    };

} // namespace Ra180

