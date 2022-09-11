#pragma once

#include <Clementine/Events/Event.h>
#include <Clementine/Layer.h>
#include <memory>

namespace Ra180 {
    class Display;

    class DisplayLayer : public Clementine::Layer
    {
    public:
        DisplayLayer(std::unique_ptr<Display> p_display);

        const Display& GetDisplay() const;

        virtual void OnEvent(Clementine::Event& event) override;
        virtual void OnImGuiRender() override;

    private:
        std::unique_ptr<Display> m_p_Display;
    };
} // namespace Ra180