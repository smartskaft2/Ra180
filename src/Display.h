#pragma once

#include <string>

namespace Ra180
{

class Display
{
public:
    ~Display() = default;

    void SetMessage(const std::string& message);
    void Reset();
    void Draw();
    void NextSubString();

private:
    std::string GetSubString();
    virtual void DrawImpl(const std::string &message) = 0;

protected:
    std::string m_Message = "";
    size_t      m_Offset  = 0;

};

} // namespace Ra180