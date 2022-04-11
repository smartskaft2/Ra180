

#include "Log.h"
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
            RA180_LOG_TRACE("State machine: Setting initial state state '{}'", pInitialState->GetName());
            _currentState = std::move(pInitialState);
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
            else
            {
                RA180_LOG_ERROR("State '{}' did not set a new state while consuming the event '{}'.", 
                                _currentState->GetName(), 
                                toString(event));
            }
        }
        return false;
    }

} // namespace Ra180