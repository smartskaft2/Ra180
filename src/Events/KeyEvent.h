#pragma once

#include "Events/Event.h"
#include "UI/KeyCode.h"

namespace Ra180 {

    class KeyEvent : public Event
    {
    public:
        KeyEvent(const KeyCode keyCode, const bool pressed = true)
            : Event(Type::KeyEvent), _keyCode(keyCode), _pressed(pressed)
        {
        }

        std::ostream& write(std::ostream& os) const override;

        inline KeyCode GetKeyCode() const { return _keyCode; };

    private:
        const KeyCode _keyCode;
        const bool    _pressed;
    };

} // namespace Ra180

