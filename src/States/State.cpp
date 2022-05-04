

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

    void State::AddAction(const StateAction& action)
    {
        _stateTransitions.push_back(action);
    }

    void State::ClearTransitions()
    {
        _stateTransitions.clear();
    }

    bool State::TransitionOK(const StateTransition& transition, const Event& event)
    {
        bool transitionOK{ false };
        if (transition._eventType == event.GetType())
        {
            transitionOK = true;
            for (const auto& satisfiesGuard : transition._guardCallbacks)
            {
                if (!satisfiesGuard(event))
                {
                    transitionOK = false;
                    break;
                }
            }
        }
        return transitionOK;
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
                if (transition._nextStateCreationCallback)
                {
                    pNextState = std::move(transition._nextStateCreationCallback());
                }
                RA180_LOG_TRACE("State: State '{}' consumed event '{}'", _name, toString(event));
                return true;
            }
        }
        RA180_LOG_TRACE("State: State '{}' returned event '{}'", _name, toString(event));
        return false;
    };

} // namespace Ra180