
#include "Events/Event.h"
#include "Radio/Radio180.h"
#include "States/KLAR.h"
#include "States/SKYDD.h"
#include "States/FRÅN.h"
#include "States/ModeState.h"

namespace Ra180 {

    KLAR::KLAR(Radio180& radio) : ModeState("KLAR", "klar", radio, Radio180::Mode::KLAR)
    {
        AddTransition({ Event::Type::KeyEvent, {KeyPressedGuard(KeyCode::ArrowUp)},      {}, [&]{ return CreateState<SKYDD>(); }});
        AddTransition({ Event::Type::KeyEvent, {KeyPressedGuard(KeyCode::ArrowDown)},    {}, [&]{ return CreateState<FRÅN>();  }});
    }

} // namespace Ra180