#include <blackboard/debug/imgui_layout.hpp>




using bb::debug::ImGuiLayout;




void ImGuiLayout::center_horizontally(const ImVec2& size) noexcept
{
    const float available_x = ImGui::GetContentRegionAvail().x;
    ImGui::SetCursorPosX((available_x - size.x) * 0.5f);
}