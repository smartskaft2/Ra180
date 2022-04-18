#include "States/TID.h"
#include "States/TIDChange.h"

#include "Events/Event.h"
#include "Events/KeyEvent.h"

namespace Ra180 {

    using namespace std::placeholders;

TIDChange::TIDChange(Radio180& radio) : Radio180State("TIDChange", "T:", radio)
{
    StateTransition transitionToTID{};
    transitionToTID._eventType = Event::Type::KeyEvent;
    transitionToTID._guardCallbacks = { KeyPressedGuard(ToKeyCode(HMIID::SLT)) };
    transitionToTID._nextStateCreationCallback = [&] { return CreateState<TID>(); };

    StateTransition transitionToSelf{};
    transitionToSelf._eventType = Event::Type::KeyEvent;
    transitionToSelf._guardCallbacks = { IsNumberKeyGuard, 
                                         std::bind(&TIDChange::IsIncompleteGuard, std::ref(*this), _1) };
    transitionToSelf._actionCallbacks = { std::bind(&TIDChange::AppendDigit, std::ref(*this), _1) };
    transitionToSelf._nextStateCreationCallback = [&] { return std::move(_nextState); };

    AddTransition(transitionToTID);
    AddTransition(transitionToSelf);
}

void TIDChange::Enter()
{
    std::function<void()> callback = std::bind(&TIDChange::FlashIndicator, std::ref(*this));
    _timeoutID = _timer.SetTimeout(std::chrono::seconds{ 1 }, callback, true);
}

void TIDChange::Exit()
{
    _timer.UnsetTimeout(_timeoutID);
    Radio180State::Exit();
}

void TIDChange::FlashIndicator()
{
    static bool on{ true };
    on = !on;
    _radio.GetDisplay().Print(_displayText + (on ? '_' : ' '));
}

bool TIDChange::IsCompleteGuard(const Event& event)
{
    return _ctDigits >= 6;
}
bool TIDChange::IsIncompleteGuard(const Event& event)
{
    return !IsCompleteGuard(event);
}

void TIDChange::AppendDigit(const Event& event)
{
    std::stringstream ss;
    ss << _displayText << DigitKey2Digit(dynamic_cast<const KeyEvent&>(event).GetKeyCode());
    _displayText = ss.str();
    _ctDigits++;

    if (IsCompleteGuard(event))
    {
        _nextState = CreateTIDAndSetTime();
    }
}

int TIDChange::DigitKey2Digit(const KeyCode keyCode)
{
    switch (keyCode)
    {
        case (ToKeyCode(HMIID::_0)): return 0;
        case (ToKeyCode(HMIID::_1)): return 1;
        case (ToKeyCode(HMIID::_2)): return 2;
        case (ToKeyCode(HMIID::_3)): return 3;
        case (ToKeyCode(HMIID::_4)): return 4;
        case (ToKeyCode(HMIID::_5)): return 5;
        case (ToKeyCode(HMIID::_6)): return 6;
        case (ToKeyCode(HMIID::_7)): return 7;
        case (ToKeyCode(HMIID::_8)): return 8;
        case (ToKeyCode(HMIID::_9)): return 9;

        default:
            return -1;
    }
    return 0;
}

std::unique_ptr<IState> TIDChange::CreateTIDAndSetTime()
{
    auto tid = std::make_unique<TID>(_radio);

    // Convert string to time
    std::stringstream ss{ _displayText };
    char c1, c2;
    int i1, i2;
    ss >> c1;
    ss >> c2;
    unsigned int time{ 0 };
    tid->_time = decltype(tid->_time){};

    ss >> c1; i1 = c1 - '0';
    ss >> c2; i2 = c2 - '0';
    tid->_time += std::chrono::hours(i1 * 10 + i2);
    ss >> c1; i1 = c1 - '0';
    ss >> c2; i2 = c2 - '0';
    tid->_time += std::chrono::minutes(i1 * 10 + i2);
    ss >> c1; i1 = c1 - '0';
    ss >> c2; i2 = c2 - '0';
    tid->_time += std::chrono::seconds(i1 * 10 + i2);

    return std::move(tid);
}


} // namespace Ra180