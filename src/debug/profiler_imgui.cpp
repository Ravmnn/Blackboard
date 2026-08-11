#include <blackboard/debug/profiler_imgui.hpp>

#include <cmath>
#include <sstream>

#include <imgui.h>

#include <blackboard/debug/profiler_items.hpp>




using bb::debug::ProfilerIMGUI;




void ProfilerIMGUI::draw(ProfilerItem& item) noexcept
{
    if (!is_open)
        return;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 800, 400 });
    ImGui::Begin("Profiler", &is_open);

    draw_item(item);

    ImGui::End();
    ImGui::PopStyleVar();
}


void ProfilerIMGUI::draw_item(ProfilerItem& item) noexcept
{
    const bool open = ImGui::TreeNodeEx(item.id().c_str(), get_tree_node_flags(item));
    draw_time(item);

    if (!open)
        return;

    for (const auto& item : item.items)
        draw_item(*item);

    ImGui::TreePop();
}


int ProfilerIMGUI::get_tree_node_flags(const ProfilerItem& item) noexcept
{
    int flags = ImGuiTreeNodeFlags_DrawLinesToNodes | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed
                        | ImGuiTreeNodeFlags_SpanAvailWidth;

    if (item.items.empty())
        flags |= ImGuiTreeNodeFlags_Leaf;

    return flags;
}


void ProfilerIMGUI::draw_time(ProfilerItem& item) noexcept
{
    const auto average = Stopwatch::elapsed_from_ns(item.average_time_ns());

    std::stringstream text;
    text << average.ms << "." << std::round((float)average.ns / 1000.0f) << "ms";

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(text.str().c_str()).x);
    ImGui::Text("%s", text.str().c_str());
}