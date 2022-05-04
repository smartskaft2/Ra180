
#include "Events/Event.h"
#include "Radio/Radio180.h"
#include "States/ModeState.h"
#include "States/Concrete/FRÅN.h"
#include "States/Concrete/KLAR.h"
#include "States/Concrete/SKYDD.h"
#include "States/Concrete/TID.h"

namespace Ra180 {

    KLAR::KLAR(Radio180& radio) : ModeState("KLAR", "klar", radio, Radio180::Mode::KLAR)
    {
        AddTransition({ Event::Type::KeyEvent, {KeyPressedGuard(KeyCode::ArrowUp)},      {}, [&]{ return CreateState<SKYDD>(); }});
        AddTransition({ Event::Type::KeyEvent, {KeyPressedGuard(KeyCode::ArrowDown)},    {}, [&]{ return CreateState<FRÅN>();  }});
        AddTransition({ Event::Type::KeyEvent, {KeyPressedGuard(ToKeyCode(HMIID::TID))}, {}, [&]{ return CreateState<TID>();   }});
    }

} // namespace Ra180