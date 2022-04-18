
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "UI/KeyCode.h"
#include "States/StateTransition.h"

bool Ra180::StateTransition::KeyPressedGuard::operator()(const Event& event)
{
    const KeyEvent* pKeyEvent = dynamic_cast<const KeyEvent* const>(&event);
    return pKeyEvent && pKeyEvent->GetKeyCode() == _keyCode;
}