#pragma once

#include "States/Radio180State.h"
#include "Utils/Timer.h"

#include <string>
#include <iostream>
#include <memory>

namespace Ra180 {

    class TIDChange : public Radio180State
    {
    public:
        TIDChange(Radio180& radio);

        void Enter() override;
        void Exit() override;

    private:
        void FlashIndicator();
        
        bool IsCompleteGuard(const Event&);
        bool IsIncompleteGuard(const Event&);

        void AppendDigit(const Event&);
        static int DigitKey2Digit(const KeyCode keyCode);

        std::unique_ptr<IState> CreateTIDAndSetTime();

    private:
        int   _ctDigits{};
        Timer _timer{};
        int   _timeoutID{ -1 };
        std::unique_ptr<IState> _nextState{ nullptr };
    };

} // namespace Ra180

