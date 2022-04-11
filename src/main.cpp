#include "Log.h"
#include "Events/Event.h"
#include "States/State.h"
#include "States/StateMachine.h"
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

    auto pFirst = std::make_unique<State>("First");
    State* pSecond = new State("Second"); // State machine will own memory
    State* pThird  = new State("Third");  // State machine will own memory

    pFirst->AddTransition(StateTransition{ Event::Type::Undefined,
                                         {[](const auto&) { RA180_LOG_DEBUG("Transition Guard  #1: Undefined (returns true)");  return true; }},
                                         {[](const auto&) { RA180_LOG_DEBUG("Transition Action #1: Undefined "); }},
                                         [&]() { return std::unique_ptr<State>{pSecond}; } });
    pSecond->AddTransition(StateTransition{ Event::Type::PowerOff,
                                         {[](const auto&) { RA180_LOG_DEBUG("Transition Guard  #1: PowerOff (returns true)"); return true; }},
                                         {[](const auto&) { RA180_LOG_DEBUG("Transition Action #1: PowerOff"); }},
                                         [&]() { return std::unique_ptr<State>{pThird}; } });
    pThird->AddTransition(StateTransition{ Event::Type::FRÅN,
                                         {[](const auto&) { RA180_LOG_DEBUG("Transition Guard  #1: FRÅN (returns true)"); return true; }},
                                         {[](const auto&) { RA180_LOG_DEBUG("Transition Action #1: FRÅN"); }},
                                         [&]() { return std::unique_ptr<State>{nullptr}; } });
    pThird->AddTransition(StateTransition{ Event::Type::KLAR,
                                         {[](const auto&) { RA180_LOG_DEBUG("Transition Guard:  KLAR #1 (returns true)"); return true; }},
                                         {[](const auto&) { RA180_LOG_DEBUG("Transition Action: KLAR #1"); }},
                                         []() { return std::make_unique<State>("Final State"); }});

    StateMachine stateMachine{};
    stateMachine.Initialize(std::move(pFirst));

    stateMachine.OnEvent(Event::Type::Undefined);
    stateMachine.OnEvent(Event::Type::PowerOff);
    stateMachine.OnEvent(Event::Type::PowerOff);
    stateMachine.OnEvent(Event::Type::Undefined);
    stateMachine.OnEvent(Event::Type::FRÅN);
    stateMachine.OnEvent(Event::Type::KLAR);

    return 0;
}