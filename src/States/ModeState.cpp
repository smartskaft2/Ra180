#include "ModeState.h"

namespace Ra180 {

    ModeState::ModeState(std::string name, std::string displayText, Radio180& radio, const Radio180::Mode mode)
        : Radio180State(std::move(name), std::move(displayText), radio), _mode(mode)
    {
    }

    void ModeState::Enter()
    {
        Radio180State::Enter();
        _radio.SetMode(_mode);
    }

} // namespace Ra180
