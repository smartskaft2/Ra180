#pragma once

#include "UI/KeyboardManager.h"
#include "UI/KeyCode.h"

namespace Ra180 {

    class WindowsKeyboardManager : public KeyboardManager
    {
    public:
        WindowsKeyboardManager(const std::chrono::milliseconds pollRateMs) : KeyboardManager(pollRateMs)
        {
        };

    protected:
        bool pollSingleKeyPressImpl(KeyCode& keyCode) override;
    };

} // namespace Ra180

