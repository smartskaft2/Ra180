

#include "toString.h"
#include "Events/Event.h"
#include "Utils/Log.h"
#include "States/IState.h"
#include "States/State.h"
#include "States/StateTransition.h"

#include <ranges>
#include <algorithm>
#include <memory>
#include <vector>
#include <string>

namespace Ra180 {

    State::State(std::string name) 
        : _name(std::move(name))
    {
        RA180_LOG_TRACE("State: Creates state '{}'", _name);
    }

    const std::string& State::GetName() const
    {
        return _name;
    }

    void State::Enter()
    {
        RA180_LOG_TRACE("State: Enters state '{}'", _name);
    };

    void State::Exit()
    {
        RA180_LOG_TRACE("State: Exits state '{}'", _name);
    }

    void State::AddTransition(const StateTransition& transition)
    {
        _stateTransitions.push_back(transition);
    }

    void State::ClearTransitions()
    {
        _stateTransitions.clear();
    }

    bool State::TransitionOK(const StateTransition& transition, const Event& event)
    {
        if (transition._eventType == event.GetType())
        {
            for (const auto& satisfiesGuard : transition._guardCallbacks)
            {
                if (!satisfiesGuard(event))
                {
                    break;
                }
            }
            return true;
        }
        return false;
    }

    bool State::OnEvent(std::unique_ptr<IState>& pNextState, const Event& event)
    {
        RA180_LOG_TRACE("State: State '{}' handling event '{}'", _name, toString(event));

        for (const auto& transition : _stateTransitions)
        {
            if (TransitionOK(transition, event))
            {
                for (const auto& action : transition._actionCallbacks)
                {
                    action(event);
                }
                pNextState = std::move(transition._nextStateCreationCallback());
                return true;
            }
        }

        return false;
    };

} // namespace Ra180