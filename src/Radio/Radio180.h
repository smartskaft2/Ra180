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

    constexpr KeyCode ToKeyCode(const Radio180::HMIID hmiid, const bool throwOnFailure = true)
    {
        // Looks like the numpad of the RA180 
        //
        //  * 1-9 in a [3x3] matrix, start from top left, row major
        //  * Bottom (fourth) row is {*, 0, #}
        //
        //  This might be a bit confusing at first, but the aim is to
        //  practice muscle memory for those dark night. :)
        //
        //  Unfortunately NumLock cannot be used, since it locks or unlocks the other keys.
        // 
        //  ToDo: Make configurable
        //
        switch (hmiid)
        {
            case Radio180::HMIID::Return:  return KeyCode::PageDown;
            case Radio180::HMIID::ÄND:     return KeyCode::PageUp;
            case Radio180::HMIID::SLT:     return KeyCode::End;
            case Radio180::HMIID::_0:      return KeyCode::NumPad_Decimal;
            case Radio180::HMIID::_1:      return KeyCode::NumPad_7;
            case Radio180::HMIID::_2:      return KeyCode::NumPad_8;
            case Radio180::HMIID::_3:      return KeyCode::NumPad_9;
            case Radio180::HMIID::_4:      return KeyCode::NumPad_4;
            case Radio180::HMIID::_5:      return KeyCode::NumPad_5;
            case Radio180::HMIID::_6:      return KeyCode::NumPad_6;
            case Radio180::HMIID::_7:      return KeyCode::NumPad_1;
            case Radio180::HMIID::_8:      return KeyCode::NumPad_2;
            case Radio180::HMIID::_9:      return KeyCode::NumPad_3;
            case Radio180::HMIID::_Star:   return KeyCode::NumPad_0;
            case Radio180::HMIID::_Square: return KeyCode::NumPad_Return;

            default:
                if (throwOnFailure)
                {
                    throw std::logic_error("Unsupported HMIID to KeyCode convertion (value : " + std::to_string(static_cast<int>(hmiid)) + " )");
                }
                else
                {
                    return static_cast<KeyCode>(-1);
                }
        }
    }

    constexpr Radio180::HMIID ToHMIID(const KeyCode keyCode, const bool throwOnFailure = true)
    {
        constexpr int MAX_HMIID = static_cast<int>(Radio180::HMIID::_9);
        for (int i{}; i <= MAX_HMIID; ++i)
        {
            if (keyCode == ToKeyCode(static_cast<Radio180::HMIID>(i)))
            {
                return static_cast<Radio180::HMIID>(i);
            }
        }

        if (throwOnFailure)
        {
            throw std::logic_error("Unsupported KeyCode to HMIID convertion (value : " + std::to_string(static_cast<int>(keyCode)) + " )");
        }
        else
        {
            return static_cast<Radio180::HMIID>(-1);
        }
    }

} // namespace Ra180

std::ostream& operator<<(std::ostream& os, Ra180::Radio180::HMIID hmiid);