
#include "Utils/Log.h"
#include "Utils/toString.h"
#include "StateMachine.h"

namespace Ra180 {

    StateMachine::StateMachine()
    {
        RA180_LOG_TRACE("State machine: Created");
    }

    void StateMachine::Initialize(std::unique_ptr<IState> pInitialState)
    {
        if (!_currentState)
        {
            RA180_LOG_TRACE("State machine: Setting initial state '{}'", pInitialState->GetName());
            _currentState = std::move(pInitialState);
            _currentState->Enter();
        }
        else
        {
            throw std::logic_error("Trying to initialize the state machine more than once.");
        }
    }

    bool StateMachine::OnEvent(const Event& event)
    {
        if (!_currentState)
        {
            throw std::logic_error("Event dispatched before the state machine was initialized.");
        }

        std::unique_ptr<IState> pNextState{ nullptr };
        if (_currentState->OnEvent(pNextState, event))
        {
            if (pNextState)
            {
                RA180_LOG_TRACE("State machine: Transitioning from '{}' to '{}'...", _currentState->GetName(), pNextState->GetName());
                _currentState->Exit();
                _currentState = std::move(pNextState);
                _currentState->Enter();
                RA180_LOG_TRACE("State machine: Transition to '{}' finished.", _currentState->GetName());
            }
            return true;
        }
        else
        {
            return false;
        }
    }

} // namespace Ra180