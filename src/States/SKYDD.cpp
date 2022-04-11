
#include "Events/Event.h"
#include "Radio/Radio180.h"
#include "States/SKYDD.h"
#include "States/KLAR.h"
#include "States/Radio180State.h"

namespace Ra180 {

    SKYDD::SKYDD(Radio180& radio) : Radio180State("SKYDD", "skydddddddd", radio)
    {
        AddTransition({ Event::Type::KLAR, {}, {}, [&]{ return CreateState<KLAR>(); } });
    }

} // namespace Ra180