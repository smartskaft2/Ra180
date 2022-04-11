#pragma once

#include "Radio/IDisplay.h"

#include <filesystem>
#include <string>
#include <stdexcept>

namespace Ra180 {

    class LogDisplay : public IDisplay
    {
    public:
        LogDisplay(std::filesystem::path displayFilePath, const unsigned int displayWidth = 8);

        void Clear() override;
        void Print(const std::string& text) override;
        unsigned int Width() const override;

    private:
        const std::filesystem::path _displayFilePath;
        const unsigned int _displayWidth;
    };

} // namespace Ra180 
