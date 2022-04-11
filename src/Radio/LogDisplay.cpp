
#include "Utils/Log.h"
#include "Radio/LogDisplay.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <stdexcept>

namespace Ra180 {

    LogDisplay::LogDisplay(std::filesystem::path displayFilePath, const unsigned int displayWidth)
        : _displayFilePath(std::move(displayFilePath)), _displayWidth(displayWidth)
    {
        if (_displayFilePath.empty())
        {
            throw std::logic_error("LogDisplay created with invalid file path (empty)");
        }
        RA180_LOG_TRACE("LogDisplay created. Display width: {:d}, Display file: '{}'", _displayWidth, _displayFilePath.string());
    }

    unsigned int LogDisplay::Width() const
    {
        return _displayWidth;
    }

    void LogDisplay::Clear()
    {
        Print("");
    }

    void LogDisplay::Print(const std::string& text)
    {
        std::ofstream displayFile{ _displayFilePath, std::ios_base::app };
        if (displayFile.is_open())
        {
            // Make sure string to display is not wider than the display width
            const std::string toDisplay{ text.substr(0, _displayWidth) };

            // Create any trailing whitespace padding
            std::string padding{};
            if (toDisplay.size() < _displayWidth)
            {
                padding = std::string(_displayWidth - toDisplay.size(), ' ');
            }
            else if (text.size() > _displayWidth)
            {
                RA180_LOG_WARNING("LogDisplay: Attempting to display too many characters, which are cut off. String: '{}'", text);
            }

            // Print to file
            displayFile << '|' << toDisplay << padding << "|\n";
        }
        else
        {
            RA180_LOG_ERROR("LogDisplay: Could not open file '{}' for writing.", _displayFilePath.string());
        }
    }

} // namespace Ra180