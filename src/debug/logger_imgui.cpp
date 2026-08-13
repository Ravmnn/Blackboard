#include <blackboard/debug/logger_imgui.hpp>

#include <blackboard/debug/logger.hpp>
#include <blackboard/debug/imgui_widget.hpp>




using bb::debug::LoggerImGui;




void LoggerImGui::draw() noexcept
{
    if (!is_open)
        return;

    ImGuiWidget::begin_window("Logger", { 700, 500 }, is_open);
        ImGui::TextWrapped("Log file: %s", Logger::log_file_path().value_or("unloaded").c_str());
        ImGui::NewLine();
        ImGui::Separator();


        if (ImGui::Button("Copy"))
            ImGui::SetClipboardText(Logger::get_all_logs().c_str());

        ImGuiWidget::selectable_readonly_multi_line_text("logger::logs", Logger::get_all_logs());

    ImGuiWidget::end_window();
}