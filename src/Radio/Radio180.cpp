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

    float Radio180::Voltage() const
    {
        return MIN_BATTERY_VOLTAGE_V + _batteryLevel * (MAX_BATTERY_VOLTAGE_V - MIN_BATTERY_VOLTAGE_V);
    }

} // namespace Ra180
