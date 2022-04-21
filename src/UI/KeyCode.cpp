#include "UI/KeyCode.h"
#include "Utils/toString.h"

#include <iostream>
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const Ra180::KeyCode keyCode)
{
    using Ra180::KeyCode;

    switch (keyCode)
    {
        case KeyCode::_0:   return os << '0';
        case KeyCode::_1:   return os << '1';
        case KeyCode::_2:   return os << '2';
        case KeyCode::_3:   return os << '3';
        case KeyCode::_4:   return os << '4';
        case KeyCode::_5:   return os << '5';
        case KeyCode::_6:   return os << '6';
        case KeyCode::_7:   return os << '7';
        case KeyCode::_8:   return os << '8';
        case KeyCode::_9:   return os << '9';

        case KeyCode::A:    return os << 'A';
        case KeyCode::B:    return os << 'B';
        case KeyCode::C:    return os << 'C';
        case KeyCode::D:    return os << 'D';
        case KeyCode::E:    return os << 'E';
        case KeyCode::F:    return os << 'F';
        case KeyCode::G:    return os << 'G';
        case KeyCode::H:    return os << 'H';
        case KeyCode::I:    return os << 'I';
        case KeyCode::J:    return os << 'J';
        case KeyCode::K:    return os << 'K';
        case KeyCode::L:    return os << 'L';
        case KeyCode::M:    return os << 'M';
        case KeyCode::N:    return os << 'N';
        case KeyCode::O:    return os << 'O';
        case KeyCode::P:    return os << 'P';
        case KeyCode::Q:    return os << 'Q';
        case KeyCode::R:    return os << 'R';
        case KeyCode::S:    return os << 'S';
        case KeyCode::T:    return os << 'T';
        case KeyCode::U:    return os << 'U';
        case KeyCode::V:    return os << 'V';
        case KeyCode::W:    return os << 'W';
        case KeyCode::X:    return os << 'X';
        case KeyCode::Y:    return os << 'Y';
        case KeyCode::Z:    return os << 'Z';
        case KeyCode::Å:    return os << 'Å';
        case KeyCode::Ä:    return os << 'Ä';
        case KeyCode::Ö:    return os << 'Ö';

        case KeyCode::ArrowUp:          return os << "ArrowUp";
        case KeyCode::ArrowDown:        return os << "ArrowDown";
        case KeyCode::ArrowLeft:        return os << "ArrowLeft";
        case KeyCode::ArrowRight:       return os << "ArrowRight";

        case KeyCode::ControlLeft:      return os << "ControlLeft";
        case KeyCode::ControlRight:     return os << "ControlRight";
        case KeyCode::ShiftLeft:        return os << "ShiftLeft";
        case KeyCode::ShiftRight:       return os << "ShiftRight";

        case KeyCode::Tab:              return os << "Tab";
        case KeyCode::Pause:            return os << "Pause";
        case KeyCode::Return:           return os << "Return";
        case KeyCode::Escape:           return os << "Escape";

        case KeyCode::Insert:           return os << "Insert";
        case KeyCode::Delete:           return os << "Delete";
        case KeyCode::Home:             return os << "Home";
        case KeyCode::End:              return os << "End";
        case KeyCode::PageUp:           return os << "PageUp";
        case KeyCode::PageDown:         return os << "PageDown";

        case KeyCode::NumPad_0:         return os << "0 (NumPad)";
        case KeyCode::NumPad_1:         return os << "1 (NumPad)";
        case KeyCode::NumPad_2:         return os << "2 (NumPad)";
        case KeyCode::NumPad_3:         return os << "3 (NumPad)";
        case KeyCode::NumPad_4:         return os << "4 (NumPad)";
        case KeyCode::NumPad_5:         return os << "5 (NumPad)";
        case KeyCode::NumPad_6:         return os << "6 (NumPad)";
        case KeyCode::NumPad_7:         return os << "7 (NumPad)";
        case KeyCode::NumPad_8:         return os << "8 (NumPad)";
        case KeyCode::NumPad_9:         return os << "9 (NumPad)";

        case KeyCode::NumPad_Return:    return os << "Return (NumPad)";
        case KeyCode::NumPad_Decimal:   return os << ", (NumPad)";
        case KeyCode::NumPad_Add:       return os << "+ (NumPad)";
        case KeyCode::NumPad_Subtract:  return os << "- (NumPad)";
        case KeyCode::NumPad_Multiply:  return os << "* (NumPad)";
        case KeyCode::NumPad_Divide:    return os << "/ (NumPad)";
        case KeyCode::NumPad_NumLock:   return os << "Num Lock (NumPad)";

        default:
            throw std::logic_error("Unsupported key code " + Ra180::toString(static_cast<int>(keyCode)));
    }
}


template<unsigned int NDigits>
std::ostream& toHex(std::ostream& os, int value)
{
    return os << "0x" << std::uppercase << std::setfill('0') << std::setw(NDigits) << std::hex << value;
}

std::ostream& 
Ra180::writeSupportedKeys(std::ostream& os, 
                          const std::function<std::ostream& (std::ostream&, const KeyCode)> appendLineCallback)
{
    os << "======= Supported keys: =======";
    for (const KeyCode keyCode : SupportedKeysCodes())
    {
        os << "\n   " << keyCode << " (" << "0x" << std::uppercase << std::setfill('0') << std::setw(4) // Appends hexadecimal value
            << std::hex << static_cast<unsigned>(keyCode) << ') ';                                       // of key code

        if (appendLineCallback)
        {
            appendLineCallback(os << "\t: ", keyCode);
        }
    }
    return os << "\n" << std::endl;
}