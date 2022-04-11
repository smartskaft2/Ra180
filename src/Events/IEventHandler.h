#pragma once

#include "Events/Event.h"

namespace Ra180 {
    class IEventHandler
    {
    public:
        virtual bool OnEvent(const Event& event) = 0;

    public:
        virtual ~IEventHandler() = default;
    };

} // namespace Ra180