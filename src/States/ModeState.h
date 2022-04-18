#pragma once

#include "Radio/Radio180.h"
#include "States/Radio180State.h"

namespace Ra180 {

    class ModeState : public Radio180State
    {
    public:
        ModeState(std::string name, std::string displayText, Radio180& radio, const Radio180::Mode mode);

        void Enter() override;

    private:
        const Radio180::Mode _mode;
    };


} // namespace Ra180
