#pragma once

#include "States/ModeState.h"

namespace Ra180 {

    class Radio180;

    class KLAR : public ModeState
    {
    public:
        KLAR(Radio180& radio);
    };

} // namespace Ra180

