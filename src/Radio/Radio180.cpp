#include "Radio/IDisplay.h"
#include "Radio/Radio180.h"
#include "Utils/Log.h"

#include <memory>
#include <stdexcept>

namespace Ra180 {

    Radio180::Radio180(std::unique_ptr<IDisplay> pDisplay)
        : _pDisplay(std::move(pDisplay))
    {
        if (!_pDisplay)
        {
            throw std::logic_error("Radio created with invalid display (nullptr)");
        }
        RA180_LOG_TRACE("Radio created");
    };

    float Radio180::GetVoltage() const
    {
        return MIN_BATTERY_VOLTAGE_V + _batteryLevel * (MAX_BATTERY_VOLTAGE_V - MIN_BATTERY_VOLTAGE_V);
    }

    Radio180::Mode Radio180::GetMode() const
    {
        return _mode;
    }

    void Radio180::SetMode(const Mode mode)
    {
        _mode = mode;
    }

    IDisplay& Radio180::GetDisplay()
    {
        return *_pDisplay;
    }

} // namespace Ra180

std::ostream& operator<<(std::ostream& os, Ra180::Radio180::HMIID hmiid)
{
    using HMIID = Ra180::Radio180::HMIID;

    switch (hmiid)
    {
        case HMIID::Return:  return os << "Return";
        case HMIID::ÄND:     return os << "ÄND";
        case HMIID::SLT:     return os << "SLT";
        case HMIID::_0:      return os << "_0";
        case HMIID::_1:      return os << "_1";
        case HMIID::_2:      return os << "_2";
        case HMIID::_3:      return os << "_3";
        case HMIID::_4:      return os << "_4";
        case HMIID::_5:      return os << "_5";
        case HMIID::_6:      return os << "_6";
        case HMIID::_7:      return os << "_7";
        case HMIID::_8:      return os << "_8";
        case HMIID::_9:      return os << "_9";
        case HMIID::_Star:   return os << "_Star";
        case HMIID::_Square: return os << "_Square";
        default:
            throw std::logic_error("Unsupported HMIID for streaming operator.");
    }
}