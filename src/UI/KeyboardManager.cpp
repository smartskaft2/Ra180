
#include "UI/KeyboardManager.h"
#include "Utils/Log.h"

#include <chrono>

namespace Ra180 {

    KeyboardManager::KeyboardManager(const std::chrono::milliseconds minPollRateMs)
        : _minPollRateMs(minPollRateMs)
    {
        RA180_LOG_TRACE("KeyboardManager: Created. Minimal poll rate: {:d}ms", _minPollRateMs.count());
    }

    KeyboardManager::~KeyboardManager()
    {
        RA180_LOG_TRACE("KeyboardManager: Destroyed.");
    }

    bool KeyboardManager::pollSingleKeyPress(KeyCode& keyCode)
    {
        const time_point now         = clock::now();
        const duration   elapsedTime = std::chrono::duration_cast<duration>(now - _lastPoll);

        if (elapsedTime >= _minPollRateMs)
        {
            _lastPoll = now;
            return pollSingleKeyPressImpl(keyCode);
        }

        return false;
    }

} // namespace Ra180 