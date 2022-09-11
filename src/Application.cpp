#include <clmtpch.h>

#include "./Application.h"
#include "DisplayLayer.h"
#include "ImGuiDisplay.h"

#include <Clementine.h>

namespace Clementine
{

std::unique_ptr<Clementine::Application> CreateApplication()
{
    return std::make_unique<Ra180::Application>();
}

} // namespace Clementine

namespace Ra180
{

Application::Application() : Clementine::Application({ 0.1f, 0.3f, 0.1f, 1.0f })
{
    auto p_Display = std::make_unique<ImGuiDisplay>();
    p_Display->SetMessage("bla bla bla...");
    auto p_DisplayLayer = new DisplayLayer(std::move(p_Display));

    PushLayer(p_DisplayLayer);
    CLMT_LOG_INFO("Application constructed.");
}

} // namespace Ra180

