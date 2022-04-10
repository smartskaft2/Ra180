#include "Log.h"
#include "Events/Event.h"

using namespace Ra180;

int main(int argc, char* argv[])
{
	Log::Init();

	for (int a{}; a < (argc-1); ++a)
	{
		RA180_LOG_INFO("Input argument #{:d}: {}", a, argv[a]);
	}

	Event event{ Event::Type::Undefined };
	std::cout << event;
	return 0;
}