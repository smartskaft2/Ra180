#pragma once

#include "Events/Event.h"
#include "Radio/IDisplay.h"
#include "Radio/Radio180.h"
#include "States/Radio180State.h"
#include "Utils/FlashingString.h"
#include "Utils/Timer.h"

#include <string>
#include <memory>

namespace Ra180 {

    class UserInputState : public Radio180State
    {
    public:
        UserInputState(std::string  name,
                       std::string  prefix, 
                       Radio180&    radio,
                       std::string& target,
                       Timer&       timer,
                       StateTransition::StateCreationCallback writtenStateCreationCallback,
                       StateTransition::StateCreationCallback abortedStateCreationCallback);

        void Enter() override;
        void Exit() override;

    protected:
        bool IsComplete() const;
        bool IsEmpty() const;

    private:
        void AppendNumber(const Event& event);
        void PopCharacter();
        void WriteToTarget();

    private:
        const std::string _prefix;
        FlashingString    _value;
        std::string&      _target;
        StateTransition::StateCreationCallback _writtenStateCreationCallback;
        StateTransition::StateCreationCallback _abortedStateCreationCallback;
    };

} // namespace Ra180

