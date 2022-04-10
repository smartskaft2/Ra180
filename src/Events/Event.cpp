
#include "Events/Event.h"
#include "Log.h"
#include "Utils/toString.h"

#include <iostream>

namespace Ra180 {

Event::Event(const Type type) 
	: _type(type)
{
	RA180_LOG_TRACE("Event created. Type: '{}'", toString(_type));
}

Event::Type Event::GetType() const
{
	return _type;
}

std::ostream& Event::write(std::ostream& os) const
{
	return os << "Event (Type: " << _type << ')';
}


} // namespace Ra180

std::ostream& operator<<(std::ostream& os, const Ra180::Event& event)
{
	return event.write(os);
}

std::ostream& operator<<(std::ostream& os, const Ra180::Event::Type type)
{
	using Event = Ra180::Event;
	switch (type)
	{
		case Event::Type::Undefined: return os << "Undefined";

		default:
			std::stringstream ss;
			ss << "Undefined operator<< for event type with value " << static_cast<unsigned int>(type);
			throw std::logic_error(ss.str());
	}
}