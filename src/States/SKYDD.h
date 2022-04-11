#pragma once

#include "States/Radio180State.h"

namespace Ra180 {

    class Radio180;

    class SKYDD : public Radio180State
    {
    public:
        SKYDD(Radio180& radio);
    };

} // namespace Ra180

