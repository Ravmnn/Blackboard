#include <blackboard/editor/editor_selection_environment.hpp>

#include <blackboard/editor/editor.hpp>




using bb::editor::EditorSelectionEnvironment;




EditorSelectionEnvironment::EditorSelectionEnvironment(Editor& editor) noexcept : EditorEnvironment(editor),
    selection(*this)
{
    tools_.push_back(&selection);

    set_current_tool(selection);


    left_button.min_drag_distance = 5;
}




void EditorSelectionEnvironment::update() noexcept
{
    EditorEnvironment::update();

    selection_effect.update();
}




void EditorSelectionEnvironment::draw() noexcept
{
    BeginBlendMode(BLEND_MULTIPLIED);
    draw_selected_strokes();
    EndBlendMode();

    EditorEnvironment::draw();
}


void EditorSelectionEnvironment::draw_selected_strokes() noexcept
{
    if (editor.stroke_manager.meshes.size() == 0)
        return;

    selection_mesh_renderer_.overwrite_outline_thickness = SelectionOutlineBaseThickness / editor.canvas.raylib_camera().zoom;

    auto* const last_mesh_renderer = editor.stroke_manager.renderer.mesh_renderer;
    auto* const last_mesh_outline_renderer = editor.stroke_manager.renderer.mesh_outline_renderer;

    editor.stroke_manager.renderer.mesh_renderer = nullptr;
    editor.stroke_manager.renderer.mesh_outline_renderer = &selection_mesh_renderer_;

    selection_effect.enable();
    editor.stroke_manager.renderer.draw_stroke_meshes(in_selection_strokes_);
    editor.stroke_manager.renderer.draw_stroke_meshes(selected_strokes);
    selection_effect.disable();

    editor.stroke_manager.renderer.mesh_outline_renderer = last_mesh_outline_renderer;
    editor.stroke_manager.renderer.mesh_renderer = last_mesh_renderer;
}




void EditorSelectionEnvironment::on_enabled() noexcept
{
    EditorEnvironment::on_enabled();

    editor.dynamic_background_color = false;
}


void EditorSelectionEnvironment::on_disabled() noexcept
{
    EditorEnvironment::on_disabled();

    selected_strokes.clear();
}




void EditorSelectionEnvironment::on_left_button_click() noexcept
{
    editor.set_current_environment(editor.draw_environment);
}


void EditorSelectionEnvironment::on_left_button_drag_start() noexcept
{
    selected_strokes.clear();
    current_tool()->enable();
}


void EditorSelectionEnvironment::on_left_button_drag_end() noexcept
{
    current_tool()->disable();
    add_in_selection_strokes_to_selection();
}


void EditorSelectionEnvironment::add_in_selection_strokes_to_selection() noexcept
{
    for (const auto& in_selection_stroke : in_selection_strokes_)
        if (!std::ranges::contains(selected_strokes, in_selection_stroke))
            selected_strokes.push_back(in_selection_stroke);

    in_selection_strokes_.clear();
}




void EditorSelectionEnvironment::on_right_button_release() noexcept
{
    on_left_button_drag_end();
}


void EditorSelectionEnvironment::on_right_button_drag_start() noexcept
{
    current_tool()->enable();
}


void EditorSelectionEnvironment::on_right_button_drag_end() noexcept
{
    on_left_button_drag_end();
}