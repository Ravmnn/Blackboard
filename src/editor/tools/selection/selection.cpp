#include <blackboard/editor/tools/selection/selection.hpp>

#include <blackboard/editor/editor.hpp>




using bb::editor::Selection;




Selection::Selection(EditorEnvironment& environment) noexcept : Tool(environment),
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
    return editor().canvas.mouse_position();
}




void Selection::on_enabled() noexcept
{
    start_position_ = position();
}