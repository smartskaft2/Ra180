#include "Radio/Radio180.h"
#include "States/Concrete/DAT.h"
#include "States/Concrete/KLAR.h"
#include "States/Concrete/SKYDD.h"
#include "Utils/Log.h"
#include "Utils/toString.h"
#include "Utils/Timee.h"
#include "Utils/Clock.h"

#include <chrono>
#include <format>

namespace Ra180 {
    DAT::DAT(Radio180& radio)
        : Radio180State("DAT", StringifyTime(radio.GetClock().Time()), radio),
          _clock(_radio.GetClock())
    {
        /*AddTransition({ Event::Type::KeyEvent,
                       {KeyPressedGuard(ToKeyCode(HMIID::Return))},
                       {}, [&] { return CreateState<Blank>("[TID]"); } });*/

        AddTransition({ Event::Type::KeyEvent,
                       {KeyPressedGuard(ToKeyCode(HMIID::SLT))},
                       {}, [&] { return ReturnToMode(); } });
    }

    std::string DAT::StringifyTime(const Time::TimePoint time)
    {
        return std::format("DAT:{:%m%d}", time);
    }

} //  namespace Ra180
