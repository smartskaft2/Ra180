#pragma once

#include "Display.h"

#include <string>

namespace Ra180 {

class ImGuiDisplay : public Display
{
private:
    void DrawImpl(const std::string& message) override;
    void DrawEditTree();
};

} // namespace Ra180 
