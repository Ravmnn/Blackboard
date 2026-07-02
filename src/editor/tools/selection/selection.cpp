#include <blackboard/editor/tools/selection/selection.hpp>

#include <blackboard/draw.hpp>
#include <blackboard/editor/editor.hpp>




using bb::editor::Selection,
    bb::Draw,
    bb::math::Rect;




Selection::Selection(Editor& editor) noexcept : Tool(editor),
    body(*this)
{}




void Selection::update() noexcept
{
    end_position_ = position();

    body.update();
}




void Selection::draw() noexcept
{
    body.draw();
}




Vector2 Selection::position() const noexcept
{
    return editor_.canvas.mouse_position();
}




void Selection::on_enabled() noexcept
{
    start_position_ = position();
}