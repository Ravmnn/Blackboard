#include <blackboard/debug/inspector_imgui.hpp>

#include <blackboard/debug/imgui_widget.hpp>
#include <blackboard/editor/editor.hpp>




using
bb::debug::InspectorImGui,
bb::editor::StrokeMeshNode,
bb::editor::Editor;




void InspectorImGui::draw() noexcept
{
    if (!is_open)
        return;

    ImGuiWidget::begin_window("Inspector", { 500, 400 }, is_open);

    draw_inspection();

    ImGuiWidget::end_window();
}


void InspectorImGui::draw_inspection() noexcept
{
    if (!editor)
        return;

    const auto* node = editor->get_stroke_mesh_node_under_point(editor->canvas().mouse_position());

    if (!node)
        return;

    draw_node_highlight(*node);

    ImGuiWidget::text_value("Position", node->position());
    ImGuiWidget::text_value("Thickness", node->thickness());
    ImGuiWidget::text_value("Color", node->color());
    ImGuiWidget::text_value("Outline Thickness", node->outline_thickness());
    ImGuiWidget::text_value("Outline Color", node->outline_color());
    ImGuiWidget::text_value("Curvature", node->curvature());
    ImGuiWidget::text_value("Is Begin", node->is_begin());
    ImGuiWidget::text_value("Is End", node->is_end());
    ImGuiWidget::text_value("Is Extremity", node->is_extremity());
    ImGuiWidget::text_value("Forward Direction", node->forward_direction());
    ImGuiWidget::text_value("Backward Direction", node->backward_direction());
    ImGuiWidget::text_value("Up Normal", node->up_normal());
    ImGuiWidget::text_value("Down Normal", node->down_normal());
    ImGuiWidget::text_value("Index", node->sample.index);
    ImGuiWidget::text_value("Max Index", node->sample.max_index);
    ImGuiWidget::text_value("T", node->sample.t());
}


void InspectorImGui::draw_node_highlight(const StrokeMeshNode& node) noexcept
{
    const Vector2 screen_position = GetWorldToScreen2D(node.position(), editor->canvas().raylib_camera());
    ImGui::GetBackgroundDrawList()->AddCircle({ screen_position.x, screen_position.y }, 7, IM_COL32(255, 0, 0, 255));
}