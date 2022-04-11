#include "Events/Event.h"
#include "Radio/Radio180.h"
#include "Radio/LogDisplay.h"
#include "States/State.h"
#include "States/StateMachine.h"
#include "States/FRÅN.h"
#include "Utils/Log.h"
#include "Utils/toString.h"

#include <memory>

using namespace Ra180;

Event::Type ToEvent(const std::string& str)
{
    if (0 == str.compare("PowerOff"))
    {
        return Event::Type::PowerOff;
    }
    if (0 == str.compare("FRÅN"))
    {
        return Event::Type::FRÅN;
    }
    if (0 == str.compare("KLAR"))
    {
        return Event::Type::KLAR;
    }
    if (0 == str.compare("SKYDD"))
    {
        return Event::Type::SKYDD;
    }
    return static_cast<Event::Type>(-1);
}

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

    std::string input;
    while (true)
    {
        RA180_LOG_DEBUG("\n NEW INPUT:");
        if (std::getline(std::cin, input))
        {
            if (0 == input.compare("exit"))
            {
                break;
            }

            const Event::Type newEvent = ToEvent(input);
            
            if (newEvent > static_cast<Event::Type>(-1))
            {
                RA180_LOG_DEBUG("Event '{}' handled: {}", toString(newEvent), toString(stateMachine.OnEvent(newEvent)));
            }
        }
    }

    RA180_LOG_DEBUG("User terminated the program. Click [Enter] to exit...");
    std::getline(std::cin, input);

    return 0;
}