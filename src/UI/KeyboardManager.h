#pragma once

#include "UI/KeyCode.h"

#include <chrono>

namespace Ra180 {

    class KeyboardManager
    {
    public:
        using clock = std::chrono::system_clock;
        using time_point = std::chrono::time_point<clock>;
        using duration = std::chrono::milliseconds;

    public:
        KeyboardManager(const std::chrono::milliseconds minPollRateMs);
        virtual ~KeyboardManager();

    public:
        bool pollSingleKeyPress(KeyCode& keyCode);
    
    protected:
        virtual bool pollSingleKeyPressImpl(KeyCode& keyCode) = 0;

    private:
        const duration _minPollRateMs;
        time_point _lastPoll{};
    };

} // namespace Ra180

