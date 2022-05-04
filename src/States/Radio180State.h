#pragma once

#include "Events/Event.h"
#include "Radio/Radio180.h"
#include "States/State.h"

#include <string>
#include <memory>

namespace Ra180 {

    class Radio180State : public State
    {
    public:
        Radio180State(std::string name, std::string displayText, Radio180& radio);

        void Enter() override;
        void Exit() override;
    
    protected:
        using HMIID = Radio180::HMIID;

        template<typename TState, typename... TArgs>
        std::unique_ptr<IState> CreateState(TArgs&&... args)
        {
            return std::make_unique<TState>(_radio, std::forward<TArgs>(args)...);
        }

        std::unique_ptr<IState> ReturnToMode();

        static bool IsNumberKeyGuard(const Event& event);

        struct NumberKeyPressedGuard
        {
            bool operator()(const Event& event);
        };

    protected:
        std::string _displayText;
        Radio180&   _radio;
    };

} // namespace Ra180