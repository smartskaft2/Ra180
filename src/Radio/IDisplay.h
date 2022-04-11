#pragma once

#include <string>

namespace Ra180 {
        
    class IDisplay
    {
    public:
        virtual void Clear() = 0;
        virtual void Print(const std::string &text) = 0;
        virtual unsigned int Width() const = 0;

    public:
        virtual ~IDisplay() = default;
    };

} // namespace Ra180 