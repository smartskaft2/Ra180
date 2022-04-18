#pragma once

#include "Radio/IDisplay.h"
#include "UI/KeyCode.h"

#include <memory>

namespace Ra180 {

    constexpr float MIN_BATTERY_VOLTAGE_V = 10; // [V]
    constexpr float MAX_BATTERY_VOLTAGE_V = 13; // [V]

    class IDisplay;
    class Radio180State;

    class Radio180
    {
        friend class Radio180State;
    public:
        enum class Mode  { FRÅN, KLAR, SKYDD };
        enum class HMIID { Return, ÄND, SLT, _Star, _Square, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, TID = _1, KDA = _4 };

    public:
        Radio180(std::unique_ptr<IDisplay> pDisplay);

    public:
        float GetVoltage() const;
        Mode GetMode() const;
        void SetMode(const Mode mode);
        IDisplay& GetDisplay();

    private:
        std::unique_ptr<IDisplay> _pDisplay;
        float _batteryLevel{ 0.9f };
        Mode _mode{ Mode::FRÅN };
    };

    constexpr KeyCode ToKeyCode(const Radio180::HMIID hmiid)
    {
        // Looks like the numpad of the RA180 
        //
        //  * 1-9 in a [3x3] matrix, start from top left, row major
        //  * Bottom (fourth) row is {*, 0, #}
        //
        //  This might be a bit confusing at first, but the aim is to
        //  practice muscle memory for those dark night. :)
        //
        //  ToDo: Make configurable
        //
        switch (hmiid)
        {
            case Radio180::HMIID::Return:  return KeyCode::Delete;
            case Radio180::HMIID::ÄND:     return KeyCode::PageUp;
            case Radio180::HMIID::SLT:     return KeyCode::End;
            case Radio180::HMIID::_0:      return KeyCode::NumPad_2;
            case Radio180::HMIID::_1:      return KeyCode::NumPad_NumLock;
            case Radio180::HMIID::_2:      return KeyCode::NumPad_Divide;
            case Radio180::HMIID::_3:      return KeyCode::NumPad_Multiply;
            case Radio180::HMIID::_4:      return KeyCode::NumPad_7;
            case Radio180::HMIID::_5:      return KeyCode::NumPad_8;
            case Radio180::HMIID::_6:      return KeyCode::NumPad_9;
            case Radio180::HMIID::_7:      return KeyCode::NumPad_4;
            case Radio180::HMIID::_8:      return KeyCode::NumPad_5;
            case Radio180::HMIID::_9:      return KeyCode::NumPad_6;
            case Radio180::HMIID::_Star:   return KeyCode::NumPad_1;
            case Radio180::HMIID::_Square: return KeyCode::NumPad_3;

            default:
                throw std::logic_error("Unsupported HMIID for convertion to KeyCode.");
        }
    }

} // namespace Ra180
