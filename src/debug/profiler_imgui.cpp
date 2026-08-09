#include <blackboard/debug/profiler_imgui.hpp>

#include <sstream>

#include <imgui.h>

#include <blackboard/debug/profiler_items.hpp>




using bb::debug::ProfilerIMGUI;




void ProfilerIMGUI::draw(const ProfilerItem& item) noexcept
{
    if (!is_open)
        return;

    ImGui::Begin("Profiler", &is_open);

    draw_item(item);

    ImGui::End();
}


void ProfilerIMGUI::draw_item(const ProfilerItem& item) noexcept
{
    if (item.items.empty())
    {
        ImGui::Text("%s", item.id().c_str());
        draw_time(item);
    }

    else
    {
        if (!ImGui::TreeNode(item.id().c_str()))
            return;

        draw_time(item);

        for (const auto& item : item.items)
            draw_item(*item);

        ImGui::TreePop();
    }


}


void ProfilerIMGUI::draw_time(const ProfilerItem& item) noexcept
{
    std::stringstream text;
    text << item.captured_time() << "ms" << " " << item.average_time() << "ms" << " " << item.min_time() << "ms" << " " << item.max_time() << "ms";

    // TODO: decrease floating point precision

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(text.str().c_str()).x);
    ImGui::Text("%s", text.str().c_str());
}