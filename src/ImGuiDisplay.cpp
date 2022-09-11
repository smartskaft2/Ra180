#include <clmtpch.h>
#include "ImGuiDisplay.h"
#include <ImGui/imgui.h>

namespace Ra180
{

void ImGuiDisplay::DrawImpl(const std::string& message)
{
    // Create new ImGUI window for display
    ImGuiWindowFlags windowFlags = 0;
    windowFlags |= ImGuiWindowFlags_NoCollapse;
    windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
    //windowFlags |= ImGuiWindowFlags_NoResize;
    ImGui::Begin("Radio Display", nullptr, windowFlags);
    
    ImGui::Indent(10);
    ImGui::NewLine();

    // Draw display
    float fontHeight = ImGui::GetTextLineHeight();
    ImVec2 size = { message.size() * fontHeight, 2.5f * fontHeight};
    
    ImGui::BeginGroup();
    ImGui::TextColored({ 1, 1, 0, 1 }, message.c_str());
    ImGui::EndGroup();
   
    auto rectMin = ImGui::GetItemRectMin();
    auto rectMax = ImGui::GetItemRectMax();
    rectMin.x -= 5;
    rectMin.y -= 5;
    rectMax.x += 5;
    rectMax.y += 5;
    auto rectColor = IM_COL32(255, 255, 0, 100);
    ImGui::GetWindowDrawList()->AddRect(rectMin, rectMax, rectColor, 0.5f, 0, 0.5f);

    // Optional: Edit display message directly (For debugging)
    DrawEditTree();

    // End editing of display's ImGui window
    ImGui::End();
}

void ImGuiDisplay::DrawEditTree()
{
    ImGui::NewLine();

    const auto ResizeMessageBuffer = [](ImGuiInputTextCallbackData* p_data) -> int
    {
        std::string* p_message = (std::string*)p_data->UserData;
        IM_ASSERT(p_data->Buf == p_message->c_str());
        p_message->resize(p_data->BufTextLen);
        p_data->Buf = p_message->data();
        return 0;
    };

    if (ImGui::TreeNode("Edit display variables"))
    {
        ImGui::NewLine();

        // Display Offset
        ImGui::Text("Display offset: %i", m_Offset);
        ImGui::SameLine();
        if (ImGui::ArrowButton("##left", ImGuiDir_Left))   m_Offset -= 8;
        ImGui::SameLine();
        if (ImGui::ArrowButton("##right", ImGuiDir_Right)) m_Offset += 8;

        ImGui::NewLine();

        // Display message
        ImGui::Text("Display message: ");
        ImGui::SameLine();
        ImGui::InputText("##message",
                         (char*)m_Message.c_str(),
                         m_Message.capacity() + 1,
                         ImGuiInputTextFlags_CallbackResize,
                         ResizeMessageBuffer,
                         &m_Message);

        ImGui::TreePop();
    }
}

} // namespace Ra180