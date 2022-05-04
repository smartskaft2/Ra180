#pragma once

#include "States/Radio180State.h"
#include "Utils/Timer.h"
#include "Utils/Timee.h"
#include "Utils/Clock.h"

#include <chrono>

namespace Ra180 {

    class Radio180;

    class TID : public Radio180State
    {
    public:
        TID(Radio180& radio);

        void Enter() override;
        void Exit() override;

    private:
        static std::string StringifyTime(Time::TimePoint time);

    private:
        Clock& _clock;
        int    _tickedCallbackID{ -1 };
    };

} // namespace Ra180
