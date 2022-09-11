#include <clmtpch.h>
    
#include "DisplayLayer.h"
#include "Display.h"
#include <Clementine/Log.h>
#include <Clementine/KeyCode.h>
#include <Clementine/Events/KeyPressedEvent.h>
#include <Clementine/Events/Event.h>
#include <Clementine/Events/EventDispatcher.h>
//#include <Clementine.h>

namespace Ra180
{

DisplayLayer::DisplayLayer(std::unique_ptr<Display> p_display) : m_p_Display(std::move(p_display))
{
    CLMT_LOG_TRACE("Display layer created.");
}

const Display& DisplayLayer::GetDisplay() const
{
    return *m_p_Display;
}

void DisplayLayer::OnEvent(Clementine::Event& event)
{
    auto dispatcher = Clementine::EventDispatcher{ event };
    dispatcher.Dispatch<Clementine::KeyPressedEvent>([&](Clementine::KeyPressedEvent &keyEvent) -> bool
    {
        if (keyEvent.GetKeyCode() == static_cast<int>(Clementine::KeyCode::Enter))
        {
            m_p_Display->NextSubString();
            return true;
        }
        else
        {
            return false;
        }
    });
}

void DisplayLayer::OnImGuiRender()
{
    m_p_Display->Draw();
}

} // namespace Ra180