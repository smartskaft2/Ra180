#pragma once

#include "States/ModeState.h"

namespace Ra180 {

    class Radio180;

    class FRÅN : public ModeState
    {
    public:
        FRÅN(Radio180& radio);
    };

} // namespace Ra180

