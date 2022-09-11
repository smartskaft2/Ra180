#include <clmtpch.h>

#include "Display.h"

namespace Ra180
{
    static constexpr size_t DISPLAY_WIDTH = 8;

    void Display::SetMessage(const std::string& message)
    {
        m_Message = message;
        m_Offset  = 0;
    }

    void Display::Reset()
    {
        m_Message = "";
        m_Offset  = 0;
    }

    void Display::Draw()
    {
        DrawImpl(GetSubString());
    }

    std::string Display::GetSubString()
    {
        std::string subString;
        if (m_Offset < m_Message.size())
        {
            subString = m_Message.substr(m_Offset, DISPLAY_WIDTH);
        }
        else
        {
            subString = "";
        }

        if (subString.size() < DISPLAY_WIDTH)
        {
            subString += std::string(DISPLAY_WIDTH - subString.size(), ' ');
        }

        return subString;
    }

    void Display::NextSubString()
    {
        m_Offset += min(m_Message.size(), DISPLAY_WIDTH); // min macro defined... :(
        m_Offset  = min(m_Offset, m_Message.size());
    }


} // namespace Ra180