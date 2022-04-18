#pragma once

#include "States/Radio180State.h"
#include "Utils/Timer.h"

#include <chrono>

namespace Ra180 {

    class Radio180;

    class TID : public Radio180State
    {
        friend class TIDChange;

        using clock      = std::chrono::system_clock;
        using time_point = std::chrono::time_point<clock>;

    public:
        TID(Radio180& radio);

        void Enter() override;
        void Exit() override;

    private:
        static std::string StringifyTime(time_point time);

    private:
        time_point _time;
        Timer      _timer{};
        int        _timeoutID{ -1 };
    };


} // namespace Ra180
