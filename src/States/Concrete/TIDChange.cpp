
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "States/Concrete/DAT.h"
#include "States/Concrete/TID.h"
#include "States/Concrete/TIDChange.h"
#include "Utils/Timee.h"

namespace Ra180 {

using namespace std::placeholders;

TIDChange::TIDChange(Radio180& radio, Timer& timer)
    : UserInputState("TIDChange", 
                     "T:", 
                     radio, 
                     _value, 
                     timer, 
                     [&] { _clock.SetTime(String2TimePoint(_value)); return CreateState<DAT>(); },
                     [&] { /* ................................... */ return CreateState<TID>(); }),
     _clock(_radio.GetClock())
{
}

std::unique_ptr<IState> TIDChange::CreateNextState()
{
    // ToDo: Add transition to DAT

    // Complete -> To DAT
    if (IsComplete())
    {
        _clock.SetTime(String2TimePoint(_value)); // Value will have new set time string
        return std::make_unique<DAT>(_radio);
    }

    // Otherwise, back to TID
    else
    {
        return std::make_unique<TID>(_radio);
    }

}

Time::TimePoint TIDChange::String2TimePoint(const std::string_view timeString)
{
    const Time::TimePoint      day{ std::chrono::floor<std::chrono::days>(Time::Local()) };
    const std::chrono::hours   hrs{ std::stoul(timeString.substr(0,2).data()) };
    const std::chrono::minutes min{ std::stoul(timeString.substr(2,2).data()) };
    const std::chrono::seconds sec{ std::stoul(timeString.substr(4,2).data()) };

    return Time::TimePoint{ day + hrs + min + sec };
}


} // namespace Ra180