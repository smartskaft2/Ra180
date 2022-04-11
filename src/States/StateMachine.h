#pragma once

#include "States/IState.h"
#include "Events/IEventHandler.h"

#include <memory>
#include <stdexcept>

namespace Ra180 {

    class StateMachine : public IEventHandler
    {
    public:
        StateMachine();

        void Initialize(std::unique_ptr<IState> pInitialState);
        bool OnEvent(const Event& event) override;

    private:
        std::unique_ptr<IState> _currentState{};
    };

} // namespace Ra180