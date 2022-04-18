#pragma once

#include "Radio/IDisplay.h"

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
        Radio180(std::unique_ptr<IDisplay> pDisplay);

    public:
        float Voltage() const;

    private:
        std::unique_ptr<IDisplay> _pDisplay;
        float _batteryLevel{ 0.9f };
    };

} // namespace Ra180