#pragma once

#include "States/Radio180State.h"

namespace Ra180 {

    class Radio180;

    class KLAR : public Radio180State
    {
    public:
        KLAR(Radio180& radio);
    };

} // namespace Ra180

