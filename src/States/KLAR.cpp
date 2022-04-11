
#include "Events/Event.h"
#include "Radio/Radio180.h"
#include "States/KLAR.h"
#include "States/SKYDD.h"
#include "States/FR�N.h"
#include "States/Radio180State.h"

namespace Ra180 {

    KLAR::KLAR(Radio180& radio) : Radio180State("KLAR", "klar", radio)
    {
        AddTransition({ Event::Type::SKYDD, {}, {}, [&]{ return CreateState<SKYDD>(); } });
        AddTransition({ Event::Type::FR�N,   {}, {}, [&]{ return CreateState<FR�N>();   } });
    }

} // namespace Ra180