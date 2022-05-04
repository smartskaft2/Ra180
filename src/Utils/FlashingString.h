#pragma once

#include "Radio/IDisplay.h"
#include "Utils/Timer.h"

#include <string>
#include <string_view>
#include <chrono>
#include <atomic>
#include <mutex>
#include <thread>

namespace Ra180 {

    class FlashingString
    {
    public:
        FlashingString(IDisplay& display, 
                       Timer& timer, 
                       std::string initialString = "",
                       const std::chrono::milliseconds rate = std::chrono::milliseconds{ 600 });

        ~FlashingString();

        const std::string& String() const;
        const char* const c_str() const;

        std::size_t Size() const;

        void Start();
        void Stop();
        bool IsFlashing() const;
        bool IsFull() const;
        bool IsEmpty() const;

        void Set(std::string string);

        template<typename TString>
        void Append(TString&& string);
        //void Append(std::string_view string);

        void Pop(std::size_t n = 1);

        bool Compare(std::string_view stringView) const;

    public:
        FlashingString& operator+=(std::string_view stringView);

    private:
        void Flash();
        std::mutex& MutexForImmutable() const;

    private:
        IDisplay& _display;
        Timer&    _timer;
        const std::chrono::milliseconds _rate;
        std::string _string;
        std::size_t _offset{_string.size()};
        int         _timeoutID{-1};
        bool        _visible{false};
        std::mutex  _mutex{};
    };

    template<typename TString> inline
    void FlashingString::Append(TString&& string)
    {
        std::lock_guard<std::mutex> lock{ _mutex };
        if (_visible && !_string.empty())
        {
            _string.pop_back();
        }
        _string += std::forward<TString>(string);
        _visible = false;
    }

} // namespace Ra180

