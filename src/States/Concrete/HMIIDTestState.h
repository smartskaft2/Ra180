#pragma once

#include "State.h"
#include "KeyEvent.h"
#include "Radio180.h"

namespace Ra180 {

class HMIIDTestState : public State
{
public:
    HMIIDTestState() : State("HMIID Test State")
    {
        AddAction({ Event::Type::KeyEvent, {&HMIIDTestState::IsHMIIDKey}, {&HMIIDTestState::PrintHMIIDKey} });
    }

    static bool IsHMIIDKey(const Event& event)
    {
        constexpr int MAX_HMIID = static_cast<int>(Radio180::HMIID::_9);

        const KeyEvent& keyEvent = static_cast<const KeyEvent&>(event);
        for (int i{}; i <= MAX_HMIID; ++i)
        {
            if (keyEvent.GetKeyCode() == ToKeyCode(static_cast<Radio180::HMIID>(i)))
            {
                LastFoundHMIID = static_cast<Radio180::HMIID>(i);
                return true;
            }
        }
        return false;
    }

    static void PrintHMIIDKey(const Event& event)
    {
        const KeyEvent& keyEvent = static_cast<const KeyEvent&>(event);
        RA180_LOG_DEBUG("--- KeyCode '{}' -> HMIID '{}'", toString(keyEvent.GetKeyCode()), toString(LastFoundHMIID));
    }

    static Radio180::HMIID LastFoundHMIID;
};
Radio180::HMIID HMIIDTestState::LastFoundHMIID{static_cast<Radio180::HMIID>(-1)};

} // namespace Ra180

