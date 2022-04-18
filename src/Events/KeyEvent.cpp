#include "Events/KeyEvent.h"
#include "Events/Event.h"

#include <iostream>

namespace Ra180 {

    std::ostream& KeyEvent::write(std::ostream& os) const
    {
        return Event::write(os) << " [" << _keyCode << ']';
    }

} // namespace Ra180

