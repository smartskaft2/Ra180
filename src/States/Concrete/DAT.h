#pragma once

#include "States/Radio180State.h"
#include "Utils/Timer.h"
#include "Utils/Timee.h"
#include "Utils/Clock.h"

#include <chrono>

// ToDo: Support auto-updating of changed date 

namespace Ra180 {

    class Radio180;

    class DAT : public Radio180State
    {
    public:
        DAT(Radio180& radio);

    private:
        static std::string StringifyTime(Time::TimePoint time);

    private:
        Clock& _clock;
    };

} // namespace Ra180
