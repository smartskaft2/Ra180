#include "Utils/FlashingString.h"
#include "Utils/Log.h"

#include <string>
#include <string_view>
#include <chrono>

namespace Ra180 {

    FlashingString::FlashingString(IDisplay& display, 
                                   Timer& timer, 
                                   const std::chrono::milliseconds rate)
        : _display(display), _timer(timer), _rate(rate)
    {
    }

    FlashingString::~FlashingString()
    {
        if (_timeoutID >= 0)
        {
            _timer.UnsetTimeout(_timeoutID);
        }
    }

    const std::string& FlashingString::String() const
    {
        std::lock_guard<std::mutex> lock{ MutexForImmutable() };
        return _string;
    }

    const char* const FlashingString::c_str() const
    {
        std::lock_guard<std::mutex> lock{ MutexForImmutable() };
        return _string.c_str();
    }

    void FlashingString::Start()
    {
        std::lock_guard<std::mutex> lock{ _mutex };
        if (_timeoutID < 0)
        {
            using namespace std::chrono_literals;
            _timeoutID = _timer.SetTimeout(_rate, [&]{ this->Flash(); }, true);
        }
        else
        {
            RA180_LOG_WARNING("Attempt to start already started flashing caret ignored.");
        }
        _visible = false;
    }

    void FlashingString::Stop()
    {
        std::lock_guard<std::mutex> lock{ _mutex };
        if (_timeoutID >= 0)
        {
            if (_visible && !_string.empty())
            {
                _string.pop_back();
                _display.Clear();
                _display.Print(_string);
            }
            _timer.UnsetTimeout(_timeoutID);
            _timeoutID = -1;
        }
        else
        {
            RA180_LOG_WARNING("Attempt to stop already stopped flashing caret ignored.");
        }
    }

    bool FlashingString::IsFlashing() const
    {
        std::lock_guard<std::mutex> lock{ MutexForImmutable() };
        return _timeoutID >= 0;
    }

    void FlashingString::Set(std::string string)
    {
        std::lock_guard<std::mutex> lock{ _mutex };
        std::swap(_string, string); 
        _visible = false;
    }

    void FlashingString::Append(std::string_view stringView)
    {
        std::lock_guard<std::mutex> lock{ _mutex };
        if (_visible && !_string.empty())
        {
            _string.pop_back();
        }
        _string.append(stringView);
        _visible = false;
    }

    void FlashingString::Pop(std::size_t n)
    {
        std::lock_guard<std::mutex> lock{ _mutex };
        while (n-- > 0 && !_string.empty())
        {
            _string.pop_back();
        }
    }

    bool FlashingString::Compare(std::string_view stringView) const
    {
        std::lock_guard<std::mutex> lock{ MutexForImmutable() };
        return _string.compare(stringView) == 0;
    }

    FlashingString& FlashingString::operator+=(std::string_view stringView)
    { 
        Append(stringView); 
        return *this; 
    }

    void FlashingString::Flash()
    {
        {
            // Lock mutex, so no string changes interfere with setting/clearing caret
            std::lock_guard<std::mutex> lock{ _mutex };

            // Return early if the display cannot take fit new caret
            const bool fullDisplay = !_visible && _string.size() >= _display.Width();
            if (!fullDisplay)
            {
                // Else, add or remove caret
                _visible = !_visible;
                if (_visible)
                {
                    _string += '_';
                }
                else if (!_string.empty())
                {
                    _string.pop_back();
                }
            }
        }

        // Print new string
        _display.Clear();
        _display.Print(_string);
    }

    std::mutex& FlashingString::MutexForImmutable() const
    {
        return const_cast<FlashingString*>(this)->_mutex;
    }

} // namespace Ra180

