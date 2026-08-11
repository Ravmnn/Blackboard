#include <blackboard/debug/profiler_imgui.hpp>

#include <sstream>

#include <imgui.h>

#include <blackboard/debug/profiler_items.hpp>




using bb::debug::ProfilerIMGUI;




void ProfilerIMGUI::draw(const ProfilerItem& item) noexcept
{
    if (!is_open)
        return;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 800, 400 });
    ImGui::Begin("Profiler", &is_open);

    draw_item(item);

    ImGui::End();
    ImGui::PopStyleVar();
}


void ProfilerIMGUI::draw_item(const ProfilerItem& item) noexcept
{
    int flags = ImGuiTreeNodeFlags_DrawLinesToNodes | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed
                        | ImGuiTreeNodeFlags_SpanAvailWidth;

    if (item.items.empty())
        flags |= ImGuiTreeNodeFlags_Leaf;

    if (!ImGui::TreeNodeEx(item.id().c_str(), flags))
        return;

    draw_time(item);
    for (const auto& item : item.items)
        draw_item(*item);

    ImGui::TreePop();
}


void ProfilerIMGUI::draw_time(const ProfilerItem& item) noexcept
{
    const auto average = Stopwatch::elapsed_from_ns(item.average_time_ns());

    std::stringstream text;
    text << average.ms << "." << average.ns << "ms";

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(text.str().c_str()).x);
    ImGui::Text("%s", text.str().c_str());
}