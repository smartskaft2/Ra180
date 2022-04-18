#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "OS/WindowsKeyboardManager.h"
#include "Radio/Radio180.h"
#include "Radio/LogDisplay.h"
#include "States/State.h"
#include "States/StateMachine.h"
#include "States/FRÅN.h"
#include "UI/KeyCode.h"
#include "UI/KeyboardManager.h"
#include "Utils/Log.h"
#include "Utils/toString.h"
#include "Utils/sleepUntil.h"

#include <memory>
#include <chrono>

using namespace Ra180;
using namespace std::chrono_literals;


int main(int argc, char* argv[])
{
    Log::Init();
   
    RA180_LOG_DEBUG("-----------------------------------------------");
    RA180_LOG_DEBUG("Radio180 app started");
    for (int a{}; a < (argc-1); ++a)
    {
        RA180_LOG_DEBUG("Input argument #{:d}: {}", a, argv[a]);
    }
    RA180_LOG_DEBUG("-----------------------------------------------");

    Radio180 radio{std::make_unique<LogDisplay>("display.txt")};

    StateMachine stateMachine{};
    stateMachine.Initialize(std::make_unique<FRÅN>(radio));
    
    WindowsKeyboardManager keyboardManager{ 290ms };

    using engineRate = std::chrono::duration<int, std::ratio<1, 30>>;
    auto  timePoint = std::chrono::system_clock::now() + engineRate{ 1 };

    KeyCode pressedKey;
    bool aborted{ false };
    while (!aborted)
    {
        if (keyboardManager.pollSingleKeyPress(pressedKey))
        {
            RA180_LOG_DEBUG("Key pressed: {}", toString(pressedKey));
            
            // Special key press: Escape -> Shut down program if radio is already shut off. Otherwise, shut it off.
            if (pressedKey == KeyCode::Escape)
            {
                aborted = (radio.GetMode() == Radio180::Mode::FRÅN);
                if (!aborted)
                {
                    RA180_LOG_DEBUG("User shut off power to the radio with the [ESC].");
                    RA180_LOG_DEBUG("Press [UP] to start it again, or [ESC] again to terminate the program.");
                    stateMachine.OnEvent(Event::Type::PowerOff);
                }
            }

            // Else, notify current state of key event
            else
            {
                stateMachine.OnEvent(KeyEvent{ pressedKey });
            }
        }

        // Sleep until next time to run engine
        SleepUntil(timePoint);
        timePoint += engineRate{ 1 };
    }

    RA180_LOG_DEBUG("User terminated the program. Click [Enter] to exit...");
    std::string input;
    std::getline(std::cin, input);

    return 0;
}