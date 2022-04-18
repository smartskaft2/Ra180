#pragma once

#include "Events/Event.h"
#include "States/IState.h"
#include "UI/KeyCode.h"

#include <functional>
#include <memory>
#include <vector>

namespace Ra180 {

    struct StateTransition
    {
        using GuardCallback         = std::function<bool(const Event&)>;
        using ActionCallback        = std::function<void(const Event&)>;
        using StateCreationCallback = std::function<std::unique_ptr<IState>()>;

        Event::Type                 _eventType{};
        std::vector<GuardCallback>  _guardCallbacks{};
        std::vector<ActionCallback> _actionCallbacks{};
        StateCreationCallback       _nextStateCreationCallback{};

        // Helper functors - Guards
        struct KeyPressedGuard
        {
            const KeyCode _keyCode;
            bool operator()(const Event& event);
        };   

    };

} // namespace Ra180