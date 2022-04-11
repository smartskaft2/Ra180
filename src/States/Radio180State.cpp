#include "Radio/Radio180.h"
#include "Radio/IDisplay.h"
#include "States/Radio180State.h"
#include "Utils/Log.h"

#include <string>
#include <functional>

namespace Ra180 {

    Radio180State::Radio180State(std::string name, std::string displayText, Radio180 & radio)
        : State(std::move(name)), _displayText(std::move(displayText)), _radio(radio)
    {
    }

    void Radio180State::Enter()
    {
        State::Enter();
        RA180_LOG_TRACE("Radio180State: Clearing display");
        _radio._pDisplay->Clear();
        RA180_LOG_TRACE("Radio180State: Printing '{}'", _displayText);
        _radio._pDisplay->Print(_displayText);
    }

    void Radio180State::Exit()
    {
        RA180_LOG_TRACE("Radio180State: Clearing display");
        _radio._pDisplay->Clear();
    }

} // namespace Ra180