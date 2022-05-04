
#include "Events/Event.h"
#include "Radio/Radio180.h"
#include "States/ModeState.h"
#include "States/Concrete/KLAR.h"
#include "States/Concrete/SKYDD.h"
#include "States/Concrete/TID.h"

namespace Ra180 {

    SKYDD::SKYDD(Radio180& radio) : ModeState("SKYDD", "skydddddddd", radio, Radio180::Mode::SKYDD)
    {
        AddTransition({ Event::Type::KeyEvent, {KeyPressedGuard(KeyCode::ArrowDown)},    {}, [&]{ return CreateState<KLAR>(); }});
        AddTransition({ Event::Type::KeyEvent, {KeyPressedGuard(ToKeyCode(HMIID::TID))}, {}, [&]{ return CreateState<TID>();  }});
    }

} // namespace Ra180