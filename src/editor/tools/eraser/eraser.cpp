#include <blackboard/editor/tools/eraser/eraser.hpp>

#include <blackboard/editor/canvas.hpp>




using bb::editor::Eraser;




Eraser::Eraser(Canvas& canvas) noexcept : Tool(canvas),
    body(*this)
{}




void Eraser::update() noexcept
{
    body.update();
}




void Eraser::draw() noexcept
{
    body.draw();
}




Vector2 Eraser::position() const noexcept
{
    return canvas_.mouse_position();
}