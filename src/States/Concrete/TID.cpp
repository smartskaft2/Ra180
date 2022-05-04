#include "Radio/Radio180.h"
#include "States/Concrete/TID.h"
#include "States/Concrete/TIDChange.h"
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
    TID::TID(Radio180& radio)
        : Radio180State("TID", "T:", radio), _clock(_radio.GetClock())
    {
        AddTransition({ Event::Type::KeyEvent,
                       {KeyPressedGuard(ToKeyCode(HMIID::Return))}, 
                       {}, [&] { return CreateState<DAT>(); } });

        AddTransition({ Event::Type::KeyEvent,
                       {KeyPressedGuard(ToKeyCode(HMIID::ÄND))},
                       {}, [&] { return CreateState<TIDChange>(GlobalTimer()); } });

        AddTransition({ Event::Type::KeyEvent,
                       {KeyPressedGuard(ToKeyCode(HMIID::SLT))},
                       {}, [&] { return ReturnToMode(); }});
    }

    void TID::Enter()
    {
        // Update display text
        _displayText = StringifyTime(_clock.Time());

        // Print text through base class method
        Radio180State::Enter();

        // Setup timer callbacks to update time
        const auto updateDisplayedTime = [&]
        {
            _displayText = StringifyTime(_clock.Time());
            _radio.GetDisplay().Print(_displayText);
        };

        _tickedCallbackID = _clock.AddTickedCallback(updateDisplayedTime);
    }

    void TID::Exit()
    {
        _clock.RemoveTickedCallback(_tickedCallbackID);
        Radio180State::Exit();
    }

    std::string TID::StringifyTime(const Time::TimePoint time)
    {
        const auto timePointSeconds = std::chrono::time_point_cast<std::chrono::seconds>(time);
        return std::format("T:{0:%H%M}{1:%S}", time, timePointSeconds);
    }

} //  namespace Ra180
