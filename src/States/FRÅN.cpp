
#include "Events/Event.h"
#include "Radio/Radio180.h"
#include "States/FR�N.h"
#include "States/KLAR.h"
#include "States/Radio180State.h"
#include "States/StateTransition.h"
#include "Utils/Log.h"

namespace Ra180 {

    namespace {
        bool BatteryOK(const Radio180& radio)
        {
            const float voltage = radio.GetVoltage();
            RA180_LOG_TRACE("State FR�N: Battery voltage is {:02.1f} (Threshold: {:02.1f})", voltage, MIN_BATTERY_VOLTAGE_V);
            return voltage >= MIN_BATTERY_VOLTAGE_V;
        }
    } // namespace

    FR�N::FR�N(Radio180& radio) : Radio180State("FR�N", "", radio)
    {
        StateTransition transitionToKLAR{};
        transitionToKLAR._eventType                 = Event::Type::KeyEvent;
        transitionToKLAR._guardCallbacks            = { KeyPressedGuard{KeyCode::ArrowUp},
                                                        [&](const Event&) { return BatteryOK(this->_radio); } };
        transitionToKLAR._nextStateCreationCallback = [&]{ return CreateState<KLAR>(); };

        ClearTransitions(); // Remove transition to self
        AddTransition(transitionToKLAR);
    }

} // namespace Ra180