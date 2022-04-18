
#include "Events/KeyEvent.h"
#include "UI/KeyCode.h"
#include "Radio/Radio180.h"
#include "Radio/IDisplay.h"
#include "States/Radio180State.h"
#include "States/FRÅN.h"
#include "Utils/Log.h"

#include <string>
#include <functional>

namespace Ra180 {

    Radio180State::Radio180State(std::string name, std::string displayText, Radio180 & radio)
        : State(std::move(name)), _displayText(std::move(displayText)), _radio(radio)
    {
        // Go to state FRÅN from any state for PowerOff events
        AddTransition({ Event::Type::PowerOff, {}, {}, [&] { return CreateState<FRÅN>(); } });
    }

    void Radio180State::Enter()
    {
        State::Enter();
        RA180_LOG_TRACE("Radio180State: Clearing display");
        _radio._pDisplay->Clear();
        RA180_LOG_TRACE("Radio180State: Printing '{}'", _displayText);
        _radio._pDisplay->Print(_displayText);
    }

    void Radio180State::Exit()
    {
        RA180_LOG_TRACE("Radio180State: Clearing display");
        _radio._pDisplay->Clear();
    }

    bool Radio180State::IsNumberKeyGuard(const Event& event)
    {
        if (event.GetType() == Event::Type::KeyEvent)
        {
            const KeyEvent& keyEvent = dynamic_cast<const KeyEvent&>(event);
            if (KeyCode::NumPad_0 <= keyEvent.GetKeyCode() && keyEvent.GetKeyCode() <= KeyCode::NumPad_9) // ToDo: Make HMIID dependent
            {
                return true;
            }
        }
        return false;
    }

} // namespace Ra180