#pragma once

#include <iostream>

namespace Ra180 {

    class Event
    {
        public:
            enum class Type;

            Event(const Type type);
            virtual ~Event();

            Type GetType() const;

            virtual std::ostream& write(std::ostream& os) const;

        private:
            const Type _type;
    };

    // Event type definition
    enum class Event::Type
    {
        Undefined = 0,
        PowerOff,
        FRÅN,
        KLAR,
        SKYDD
    };

} // namespace Ra180

std::ostream& operator<<(std::ostream& os, const Ra180::Event& event);
std::ostream& operator<<(std::ostream& os, const Ra180::Event::Type eventType);
