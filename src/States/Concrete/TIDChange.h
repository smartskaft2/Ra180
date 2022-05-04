#pragma once

#include "Radio/Radio180.h"
#include "States/UserInputState.h"
#include "Utils/Timer.h"

#include <string>
#include <iostream>
#include <memory>

namespace Ra180 {

    class TIDChange : public UserInputState
    {
    public:
        TIDChange(Radio180& radio, Timer& timer);

    /*    void Enter() override;
        void Exit() override;*/

    private:
       /* void FlashIndicator();
        
        bool IsCompleteGuard(const Event&);
        bool IsIncompleteGuard(const Event&);

        void AppendDigit(const Event&);
        static int DigitKey2Digit(const KeyCode keyCode);

        std::unique_ptr<IState> CreateTIDAndSetTime();*/

        std::unique_ptr<IState> CreateNextState();
        static Time::TimePoint String2TimePoint(const std::string_view timeString);


    private:
        Clock& _clock;
        std::string _value{};
        /*int   _ctDigits{};
        Timer _timer{};
        int   _timeoutID{ -1 };
        std::unique_ptr<IState> _nextState{ nullptr };*/
    };

} // namespace Ra180

