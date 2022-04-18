
#include "Events/Event.h"
#include "Radio/Radio180.h"
#include "States/SKYDD.h"
#include "States/KLAR.h"
#include "States/ModeState.h"

namespace Ra180 {

    SKYDD::SKYDD(Radio180& radio) : ModeState("SKYDD", "skydddddddd", radio, Radio180::Mode::SKYDD)
    {
        AddTransition({ Event::Type::KeyEvent, {KeyPressedGuard(KeyCode::ArrowDown)},    {}, [&]{ return CreateState<KLAR>(); }});
    }

} // namespace Ra180