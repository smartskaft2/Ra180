#pragma once

#include "States/ModeState.h"

namespace Ra180 {

    class Radio180;

    class SKYDD : public ModeState
    {
    public:
        SKYDD(Radio180& radio);
    };

} // namespace Ra180

