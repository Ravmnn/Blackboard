#include <blackboard/debug/imgui_widget.hpp>

#include <format>

#include <blackboard/debug/imgui_style_set.hpp>




using bb::debug::ImGuiWidget;




void ImGuiWidget::begin_window(const std::string& name, const ImVec2& size, bool& is_open, const std::optional<ImVec2>& minimum_size) noexcept
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, !minimum_size ? size : *minimum_size);
    ImGui::Begin(name.c_str(), &is_open);
}


void ImGuiWidget::end_window() noexcept
{
    ImGui::End();
    ImGui::PopStyleVar();
}




void ImGuiWidget::begin_frame_child(const std::string& id) noexcept
{
    ImGuiStyleSet::push_frame_translucid_background();
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 10, 8 });

    ImGui::BeginChild(id.c_str(), {}, ImGuiChildFlags_FrameStyle);

    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}


void ImGuiWidget::end_frame_child() noexcept
{
    ImGui::EndChild();
}




void ImGuiWidget::selectable_readonly_multi_line_text(const std::string& id, const std::string& text, const ImVec2& size) noexcept
{
    std::string buffer = text;

    if (buffer.back() != '\0')
        buffer.push_back('\0');

    ImGuiStyleSet::push_frame_translucid_background();
    ImGui::InputTextMultiline(std::format("##{}", id).c_str(), buffer.data(), buffer.size(), size, ImGuiInputTextFlags_ReadOnly);
    ImGui::PopStyleColor();
}