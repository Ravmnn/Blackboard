#include <blackboard/editor/tools/eraser/eraser.hpp>

#include <algorithm>

#include <blackboard/editor/editor.hpp>
#include <blackboard/editor/stroke/stroke_mesh_collider.hpp>




using bb::editor::Eraser,
    bb::editor::StrokeMesh,
    bb::math::Segment;




Eraser::Eraser(EditorEnvironment& environment) noexcept : Tool(environment),
    body(*this)
{}




void Eraser::update() noexcept
{
    Tool::update();

    if (active())
        update_strokes_to_remove();

    if (got_inactive_)
        remove_strokes_from_remove_queue();

    body.update();
    last_position_ = position();
}


void Eraser::update_strokes_to_remove() noexcept
{
    const Segment segment = { last_position_, this->position() };

    if (StrokeMesh* const stroke = editor().get_stroke_intersecting_segment(segment))
        add_stroke_to_remove_queue(*stroke);
}




void Eraser::draw() noexcept
{
    body.draw();
}




Vector2 Eraser::position() const noexcept
{
    return editor().canvas.mouse_position();
}




void Eraser::add_stroke_to_remove_queue(StrokeMesh& stroke) noexcept
{
    for (auto& mesh_node : stroke)
        mesh_node.color().a = 150;

    if (!std::ranges::contains(strokes_to_remove_, &stroke))
        strokes_to_remove_.push_back(&stroke);
}


void Eraser::remove_strokes_from_remove_queue() noexcept
{
    for (auto& stroke : strokes_to_remove_)
        editor().stroke_manager.remove_mesh(*stroke);

    strokes_to_remove_.clear();
}