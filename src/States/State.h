#pragma once
#include "Events/Event.h"
#include "States/IState.h"
#include "States/StateTransition.h"

#include <memory>
#include <vector>
#include <string>

namespace Ra180 {

    class State : public IState
    {
    public:
        explicit State(std::string name = "Unknown");

    public:
        bool OnEvent(std::unique_ptr<IState>& pNextState, const Event& event) override;
        void Enter() override;
        void Exit() override;

    //protected:
        void AddTransition(const StateTransition& transition);

    private:
        static bool TransitionOK(const StateTransition& transition, const Event& event);

    private:
        const std::string            _name{};
        std::vector<StateTransition> _stateTransitions{};
    };

} // namespace Ra180

