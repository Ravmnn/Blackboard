#include <blackboard/debug/profiler_imgui.hpp>

#include <implot.h>

#include <blackboard/debug/imgui_style_set.hpp>
#include <blackboard/debug/imgui_layout.hpp>
#include <blackboard/debug/imgui_widget.hpp>
#include <blackboard/debug/profiler_items.hpp>




using bb::debug::ProfilerImGui;




void ProfilerImGui::draw(ProfilerItem& item) noexcept
{
    if (!is_open)
        return;

    ImGuiWidget::begin_window("Profiler", { 800, 600 }, is_open);

    draw_fps();
    draw_chart(item);
    draw_items(item);

    ImGuiWidget::end_window();
}




void ProfilerImGui::draw_fps() noexcept
{
    ImGui::Text("FPS: %i", GetFPS());
}




void ProfilerImGui::draw_chart(ProfilerItem& item) noexcept
{
    const ImVec2 plot_size = { 770, 330 };

    // "... - 20" to fix wrong centralization (i don't know why it calculates wrongly)
    ImGuiLayout::center_horizontally({ plot_size.x - 20, plot_size.y });
    if (!ImPlot::BeginPlot("Profiler Chart", plot_size, get_chart_flags()))
        return;

    draw_pie_chart(item);

    ImPlot::EndPlot();
}


void ProfilerImGui::draw_pie_chart(ProfilerItem& item) noexcept
{
    const auto data = get_items_chart_node(item);
    const auto labels = std::get<0>(data);
    const auto values = std::get<1>(data);

    ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_NoDecorations, ImPlotAxisFlags_NoDecorations);
    ImPlot::PlotPieChart(labels.data(), values.data(), (int)labels.size(), 0.5, 0.5, 0.4);
}


int ProfilerImGui::get_chart_flags() noexcept
{
    return ImPlotFlags_NoInputs | ImPlotFlags_Equal | ImPlotFlags_NoFrame;
}




std::tuple<std::vector<const char*>, std::vector<double>> ProfilerImGui::get_items_chart_node(ProfilerItem& item) noexcept
{
    std::vector<const char*> labels;
    std::vector<double> values;

    get_items_chart_node(item, labels, values);

    return { labels, values };
}


void ProfilerImGui::get_items_chart_node(ProfilerItem& item, std::vector<const char*>& labels, std::vector<double>& values) noexcept
{
    if (item.items.empty())
    {
        labels.push_back(item.id().c_str());
        values.push_back(Stopwatch::ns_to_ms_double(item.average_time_ns()).count());
    }

    for (auto& sub_item : item.items)
        get_items_chart_node(*sub_item, labels, values);
}




void ProfilerImGui::draw_items(ProfilerItem& item) noexcept
{
    ImGuiWidget::begin_frame_child("profiler::items");
    draw_item(item);
    ImGuiWidget::end_frame_child();
}


void ProfilerImGui::draw_item(ProfilerItem& item) noexcept
{
    const bool open = ImGui::TreeNodeEx(item.id().c_str(), get_tree_node_flags(item));
    draw_time(item);

    if (!open)
        return;

    for (const auto& item : item.items)
        draw_item(*item);

    ImGui::TreePop();
}


int ProfilerImGui::get_tree_node_flags(const ProfilerItem& item) noexcept
{
    int flags = ImGuiTreeNodeFlags_DrawLinesToNodes | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed
                        | ImGuiTreeNodeFlags_SpanAvailWidth;

    if (item.items.empty())
        flags |= ImGuiTreeNodeFlags_Leaf;

    return flags;
}




void ProfilerImGui::draw_time(ProfilerItem& item) noexcept
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(3) << Stopwatch::ns_to_ms_double(item.average_time_ns()).count() << "ms";

    const std::string text = stream.str();

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(text.c_str()).x);
    ImGui::Text("%s", text.c_str());
}