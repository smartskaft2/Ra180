#include "Radio/Radio180.h"
#include "States/TID.h"
#include "States/KLAR.h"
#include "States/SKYDD.h"
#include "Utils/Log.h"
#include "Utils/toString.h"

#include <chrono>

namespace Ra180 {


    TID::TID(Radio180& radio) : Radio180State("TID", "", radio), _time(clock::now())
    {
        AddTransition({ Event::Type::KeyEvent, {KeyPressedGuard(ToKeyCode(HMIID::SLT))}, {}, [&]{ return ReturnToMode(); }});
        //AddTransition({ Event::Type::KeyEvent, {KeyPressedGuard(ToKeyCode(HMIID::ÄND))}, {}, [&] { return CreateState<TIDChange>(); } });
        //AddTransition({ Event::Type::KeyEvent, {KeyPressedGuard(ToKeyCode(HMIID::Enter))}, {}, [&] { return CreateState<DAT>(); } });
    }

    void TID::Enter()
    {
        // Update display text
        _displayText = StringifyTime(_time);

        // Print text through base class method
        Radio180State::Enter();

        // Setup timer callbacks to update time
        const auto updateDisplayedTime = [&]
        {
            _time += std::chrono::seconds{ 1 };
            _displayText = StringifyTime(_time);
            _radio.GetDisplay().Print(_displayText);
        };

        _timeoutID = _timer.SetTimeout(std::chrono::seconds{ 1 }, updateDisplayedTime, true);
    }

    void TID::Exit()
    {
        _timer.UnsetTimeout(_timeoutID);
        Radio180State::Exit();
    }

    std::string TID::StringifyTime(const time_point time)
    {
        using namespace std::chrono;

        const time_zone* timeZone = current_zone();
        const local_time<seconds> localTime = timeZone->to_local(time_point_cast<seconds>(time));

        const int localHours   = duration_cast<hours>(localTime.time_since_epoch()).count()   % 24;
        const int localMinutes = duration_cast<minutes>(localTime.time_since_epoch()).count() % 60;
        const int localSeconds = duration_cast<seconds>(localTime.time_since_epoch()).count() % 60;

        std::stringstream ss;
        ss << "T:";
        ss << std::setw(2) << std::setfill('0') << localHours;
        ss << std::setw(2) << std::setfill('0') << localMinutes;
        ss << std::setw(2) << std::setfill('0') << localSeconds;
        return ss.str();
    }

} //  namespace Ra180
