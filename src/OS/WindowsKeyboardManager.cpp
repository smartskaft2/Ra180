
#include "OS/WindowsKeyboardManager.h"
#include "UI/KeyboardManager.h"
#include "UI/KeyCode.h"
#include "Utils/Log.h"
#include "Utils/toString.h"

#include <Windows.h>

namespace Ra180 {

    namespace {
        constexpr bool KeyCodeToWindowsKeyCode(WCHAR& wchar, const KeyCode keyCode)
        {
            switch (keyCode)
            {
                case KeyCode::_0:   wchar = '0'; return true;
                case KeyCode::_1:   return wchar = '1';
                case KeyCode::_2:   return wchar = '2';
                case KeyCode::_3:   return wchar = '3';
                case KeyCode::_4:   return wchar = '4';
                case KeyCode::_5:   return wchar = '5';
                case KeyCode::_6:   return wchar = '6';
                case KeyCode::_7:   return wchar = '7';
                case KeyCode::_8:   return wchar = '8';
                case KeyCode::_9:   return wchar = '9';

                case KeyCode::A:    return wchar = 'A';
                case KeyCode::B:    return wchar = 'B';
                case KeyCode::C:    return wchar = 'C';
                case KeyCode::D:    return wchar = 'D';
                case KeyCode::E:    return wchar = 'E';
                case KeyCode::F:    return wchar = 'F';
                case KeyCode::G:    return wchar = 'G';
                case KeyCode::H:    return wchar = 'H';
                case KeyCode::I:    return wchar = 'I';
                case KeyCode::J:    return wchar = 'J';
                case KeyCode::K:    return wchar = 'K';
                case KeyCode::L:    return wchar = 'L';
                case KeyCode::M:    return wchar = 'M';
                case KeyCode::N:    return wchar = 'N';
                case KeyCode::O:    return wchar = 'O';
                case KeyCode::P:    return wchar = 'P';
                case KeyCode::Q:    return wchar = 'Q';
                case KeyCode::R:    return wchar = 'R';
                case KeyCode::S:    return wchar = 'S';
                case KeyCode::T:    return wchar = 'T';
                case KeyCode::U:    return wchar = 'U';
                case KeyCode::V:    return wchar = 'V';
                case KeyCode::X:    return wchar = 'X';
                case KeyCode::Y:    return wchar = 'Y';
                case KeyCode::Z:    return wchar = 'Z';
                case KeyCode::Å:    return wchar = 'Å';
                case KeyCode::Ä:    return wchar = 'Ä';
                case KeyCode::Ö:    return wchar = 'Ö';

                case KeyCode::ArrowUp:      return wchar = VK_UP;
                case KeyCode::ArrowDown:    return wchar = VK_DOWN;
                case KeyCode::ArrowLeft:    return wchar = VK_LEFT;
                case KeyCode::ArrowRight:   return wchar = VK_RIGHT;

                case KeyCode::ControlLeft:  return wchar = VK_LCONTROL;
                case KeyCode::ControlRight: return wchar = VK_CONTROL;
                case KeyCode::ShiftLeft:    return wchar = VK_LSHIFT;
                case KeyCode::ShiftRight:   return wchar = VK_SHIFT;

                case KeyCode::Tab:          return wchar = VK_TAB;
                case KeyCode::Pause:        return wchar = VK_PAUSE;
                case KeyCode::Return:       return wchar = VK_RETURN;
                case KeyCode::Escape:       return wchar = VK_ESCAPE;

                case KeyCode::Insert:       return wchar = VK_INSERT;
                case KeyCode::Delete:       return wchar = VK_DELETE;
                case KeyCode::Home:         return wchar = VK_HOME;
                case KeyCode::End:          return wchar = VK_END;
                case KeyCode::PageUp:       return wchar = VK_PRIOR;
                case KeyCode::PageDown:     return wchar = VK_NEXT;

                case KeyCode::NumPad_0:     return wchar = VK_NUMPAD0; 
                case KeyCode::NumPad_1:     return wchar = VK_NUMPAD1;
                case KeyCode::NumPad_2:     return wchar = VK_NUMPAD2;
                case KeyCode::NumPad_3:     return wchar = VK_NUMPAD3;
                case KeyCode::NumPad_4:     return wchar = VK_NUMPAD4;
                case KeyCode::NumPad_5:     return wchar = VK_NUMPAD5;
                case KeyCode::NumPad_6:     return wchar = VK_NUMPAD6;
                case KeyCode::NumPad_7:     return wchar = VK_NUMPAD7;
                case KeyCode::NumPad_8:     return wchar = VK_NUMPAD8;
                case KeyCode::NumPad_9:     return wchar = VK_NUMPAD9;

                case KeyCode::NumPad_Return:    return wchar = VK_RETURN;
                case KeyCode::NumPad_Decimal:   return wchar = VK_DECIMAL;
                case KeyCode::NumPad_Add:       return wchar = VK_ADD;
                case KeyCode::NumPad_Subtract:  return wchar = VK_SUBTRACT;
                case KeyCode::NumPad_Multiply:  return wchar = VK_MULTIPLY;
                case KeyCode::NumPad_Divide:    return wchar = VK_DIVIDE;
                case KeyCode::NumPad_NumLock:   return wchar = VK_NUMLOCK;

                default:
                    RA180_LOG_WARNING("KeyCodeToWindowsKeyCode: Unsupported KeyCode '{}'", toString(keyCode));
                    return false;
            }
        }
    }

    bool WindowsKeyboardManager::pollSingleKeyPressImpl(KeyCode& keyCode)
    {
        WCHAR wchar;
        for (const KeyCode key : SupportedKeysCodes())
        {
            if (KeyCodeToWindowsKeyCode(wchar, key) && GetAsyncKeyState(wchar))
            {
                keyCode = key;
                return true;
            }
        }
        return false;
    }

} // namespace Ra180 

