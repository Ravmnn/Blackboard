#include <blackboard/debug/profiler_imgui.hpp>

#include <imgui.h>

#include <blackboard/debug/profiler_items.hpp>




using bb::debug::ProfilerIMGUI;




void ProfilerIMGUI::draw(const ProfilerGroupItem& group) noexcept
{
    ImGui::Begin("Profiler");
    ImGui::Button("Hello");
    ImGui::End();
}