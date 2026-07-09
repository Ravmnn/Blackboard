#include <blackboard/editor/editor_selection_environment.hpp>

#include <blackboard/editor/editor.hpp>




using bb::editor::EditorSelectionEnvironment;




// TODO: cool background for selection mode
EditorSelectionEnvironment::EditorSelectionEnvironment(Editor& editor) noexcept : EditorEnvironment(editor),
    selection(*this)
{
    tools_.push_back(&selection);

    set_current_tool(selection);


    negative_effect_.default_color = RED;


    left_button.min_drag_distance = 5;
    left_button.drag_start.subscribe([this](auto&) noexcept { current_tool()->enable(); });
    left_button.drag_end.subscribe([this](const auto&) noexcept { current_tool()->disable(); });

    left_button.click.subscribe([&](const auto&) noexcept { editor.set_current_environment(editor.draw_environment); });

    right_button.release.subscribe([this](const auto&) noexcept { current_tool()->disable(); });
}




void EditorSelectionEnvironment::update() noexcept
{
    EditorEnvironment::update();

    negative_effect_.grayness_threshold = use_negative_colors ? 0.65 : 0;
    negative_effect_.update();
}




void EditorSelectionEnvironment::draw() noexcept
{
    draw_selected_strokes();

    EditorEnvironment::draw();
}


void EditorSelectionEnvironment::draw_selected_strokes() noexcept
{
    if (editor.canvas.stroke_meshes.size() == 0)
        return;

    selection_outline_stroke_mesh_renderer_.outline_thickness = SelectionOutlineBaseThickness / editor.canvas.raylib_camera().zoom;

    negative_effect_.enable();
    editor.canvas.stroke_renderer.set_mesh_renderer(selection_outline_stroke_mesh_renderer_);
    editor.canvas.draw_strokes();
    editor.canvas.stroke_renderer.set_mesh_renderer(editor.default_stroke_mesh_renderer());
    negative_effect_.disable();
}




void EditorSelectionEnvironment::on_enabled() noexcept
{
    EditorEnvironment::on_enabled();

    editor.dynamic_background_color = false;
}