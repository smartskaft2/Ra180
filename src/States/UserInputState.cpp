#include "States/UserInputState.h"

#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Radio/IDisplay.h"
#include "States/State.h"
#include "States/StatesConstants.h"
#include "Utils/FlashingString.h"
#include "Utils/Log.h"
#include "Utils/Timer.h"
#include "Utils/toString.h"

#include <string>
#include <memory>

namespace Ra180 {


    UserInputState::UserInputState(std::string  name,
                                   std::string  prefix, 
                                   Radio180&    radio,
                                   std::string& target,
                                   Timer&       timer,
                                   StateTransition::StateCreationCallback writtenStateCreationCallback,
                                   StateTransition::StateCreationCallback abortedStateCreationCallback)

        : Radio180State(std::move(name), prefix, radio),
          _prefix(std::move(prefix)),
          _value(radio.GetDisplay(), timer, _prefix, INPUT_CARET_RATE),
          _target(target),
          _writtenStateCreationCallback(writtenStateCreationCallback),
          _abortedStateCreationCallback(abortedStateCreationCallback)
    {
        if (!writtenStateCreationCallback || !abortedStateCreationCallback)
        {
            throw std::logic_error("Invalid state creation callbacks are not allowed."); // Will end up in invalid state
        }

        const StateAction::GuardCallback  isIncomplete  = [&](const Event& event) { return !this->IsComplete(); };
        const StateAction::GuardCallback  isComplete    = [&](const Event& event) { return  this->IsComplete(); };
        const StateAction::GuardCallback  isNonEmpty    = [&](const Event& event) { return !this->IsEmpty();    };
        const StateAction::ActionCallback appendNumber  = [&](const Event& event) { this->AppendNumber(event);  };
        const StateAction::ActionCallback popCharacter  = [&](const Event& event) { this->PopCharacter();       };
        const StateAction::ActionCallback writeToTarget = [&](const Event& event) { this->WriteToTarget();      };

        // Add action to append numbers
        AddAction({ Event::Type::KeyEvent, {NumberKeyPressedGuard{}, isIncomplete}, {appendNumber} });

        // Add action to remove appended number
        AddAction({ Event::Type::KeyEvent, {KeyPressedGuard{ToKeyCode(HMIID::ÄND)}, isNonEmpty}, {popCharacter} });

        // Add abort transition
        AddTransition({ Event::Type::KeyEvent, {KeyPressedGuard{ToKeyCode(HMIID::SLT)}}, {}, {_abortedStateCreationCallback} });

        // Add completion transition
        AddTransition({ Event::Type::KeyEvent, {KeyPressedGuard{ToKeyCode(HMIID::Return)}, isComplete}, {writeToTarget}, {_writtenStateCreationCallback} });
    }

    void UserInputState::Enter()
    {
        Radio180State::Enter();
        _value.Start();
    }

    void UserInputState::Exit()
    {
        _value.Stop();
        Radio180State::Exit();
    }

    void UserInputState::AppendNumber(const Event& event)
    {
        const KeyEvent* pKeyEvent = dynamic_cast<const KeyEvent*>(&event);
        if (pKeyEvent)
        {
            const KeyCode         keyCode = pKeyEvent->GetKeyCode();
            const Radio180::HMIID hmiid   = ToHMIID(keyCode);
            if (static_cast<int>(hmiid) > -1)
            {
                const char c = toString(hmiid).at(1); // Second character in e.g. "_3"
                RA180_LOG_TRACE("Appending '{}' to State '{}' (from KeyCode '{}').", c, this->GetName(), toString(keyCode));
                _value.Append(c); // First character from numpad string, e.g. "3 (NumPad)"
            }
            else 
            {
                RA180_LOG_ERROR("The KeyCode of Event '{}' ('{}') could not be converted to a HMIID.", toString(event), toString(keyCode));
            }
        }
        else
        {
            RA180_LOG_ERROR("Event '{}' was not a key event.", toString(event));
        }
    }

    void UserInputState::PopCharacter()
    {
        _value.Pop();
    }

    void UserInputState::WriteToTarget()
    {
        _value.Stop();
        std::string toWrite = _value.String().substr(_prefix.size());
        _target = toWrite;
    }

    bool UserInputState::IsComplete() const
    {
        return _value.IsFull();
    }

    bool UserInputState::IsEmpty() const
    {
        return _value.IsEmpty();
    }


} // namespace Ra180

