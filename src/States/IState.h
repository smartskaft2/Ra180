#pragma once

#include "Events/Event.h"

#include <memory>
#include <string>

namespace Ra180
{
    class IState
    {
    public:
        virtual const std::string& GetName() const = 0;
        virtual bool OnEvent(std::unique_ptr<IState>& pNextState, const Event& event) = 0;
        virtual void Enter() = 0;
        virtual void Exit()  = 0;



    public:
        virtual ~IState() = default;

    protected:
        IState()                             = default;
        IState(const IState&)                = default;
        IState& operator=(const IState&)     = default;
        IState(IState&&)            noexcept = default;
        IState& operator=(IState&&) noexcept = default;
    };
}