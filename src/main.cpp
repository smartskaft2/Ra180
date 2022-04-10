#include "Log.h"
#include "Events/Event.h"
#include "States/State.h"
#include "Utils/toString.h"

#include <memory>

using namespace Ra180;

int main(int argc, char* argv[])
{
    Log::Init();

    for (int a{}; a < (argc-1); ++a)
    {
        RA180_LOG_INFO("Input argument #{:d}: {}", a, argv[a]);
    }

    Event event{ Event::Type::Undefined };

    State state{"Attila"};
    state.AddTransition(StateTransition{ Event::Type::Undefined,
                                         {[](const auto&) { RA180_LOG_DEBUG("Transition Guard #1:  Undefined #1 (returns true)");  return true; }, 
                                          [](const auto&) { RA180_LOG_DEBUG("Transition Guard #2:  Undefined #1 (returns false)"); return false; }},
                                         {[](const auto&) { RA180_LOG_DEBUG("Transition Action #1: Undefined #1"); }},
                                         []() { return std::make_unique<State>(); }});
    state.AddTransition(StateTransition{ Event::Type::Undefined,
                                         {[](const auto&) { RA180_LOG_DEBUG("Transition Guard #1:  Undefined #2 (returns true)"); return true; },
                                          [](const auto&) { RA180_LOG_DEBUG("Transition Guard #2:  Undefined #2 (returns true)"); return true; }},
                                         {[](const auto&) { RA180_LOG_DEBUG("Transition Action #1: Undefined #2"); },
                                          [](const auto&) { RA180_LOG_DEBUG("Transition Action #2: Undefined #2"); }},
                                         []() { return std::make_unique<State>(); } });
    state.AddTransition(StateTransition{ Event::Type::PowerOff,
                                         {[](const auto&) { RA180_LOG_DEBUG("Transition Guard:  PowerOff #1 (returns true)"); return true; }},
                                         {[](const auto&) { RA180_LOG_DEBUG("Transition Action: PowerOff #1"); }},
                                         []() { return std::make_unique<State>(); } });


    std::unique_ptr<IState> pNextState{nullptr};

    const Event eventUndefined{ Event::Type::Undefined };
    const Event eventPowerOff{  Event::Type::PowerOff };
    const Event evenKlar{        Event::Type::KLAR };

    RA180_LOG_DEBUG("OnEvent return value: {}", toString(state.OnEvent(pNextState, eventUndefined)).c_str());
    RA180_LOG_DEBUG("OnEvent return value: {}", toString(state.OnEvent(pNextState, eventPowerOff)).c_str());
    RA180_LOG_DEBUG("OnEvent return value: {}", toString(state.OnEvent(pNextState, evenKlar)).c_str());

    return 0;
}