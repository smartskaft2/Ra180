
#include "Events/KeyEvent.h"
#include "UI/KeyCode.h"
#include "Radio/Radio180.h"
#include "Radio/IDisplay.h"
#include "States/Radio180State.h"
#include "States/Concrete/FRÅN.h"
#include "States/Concrete/KLAR.h"
#include "States/Concrete/SKYDD.h"
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

    std::unique_ptr<IState> Radio180State::ReturnToMode()
    {
        switch (_radio.GetMode())
        {
            case (Radio180::Mode::FRÅN):  return std::make_unique<FRÅN>(_radio);
            case (Radio180::Mode::KLAR):  return std::make_unique<KLAR>(_radio);
            case (Radio180::Mode::SKYDD): return std::make_unique<SKYDD>(_radio);
            default:
                throw std::logic_error("Unsupported radio mode.");
        }
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

    bool Ra180::Radio180State::NumberKeyPressedGuard::operator()(const Event& event)
    {
        const KeyEvent* pKeyEvent = dynamic_cast<const KeyEvent* const>(&event);
        if (pKeyEvent)
        {
            switch (pKeyEvent->GetKeyCode())
            {
                case ToKeyCode(HMIID::_0):
                case ToKeyCode(HMIID::_1):
                case ToKeyCode(HMIID::_2):
                case ToKeyCode(HMIID::_3):
                case ToKeyCode(HMIID::_4):
                case ToKeyCode(HMIID::_5):
                case ToKeyCode(HMIID::_6):
                case ToKeyCode(HMIID::_7):
                case ToKeyCode(HMIID::_8):
                case ToKeyCode(HMIID::_9):
                    return true;
                default:
                    return false;
            }
        }
        else
        {
            return false;
        }
    }

} // namespace Ra180