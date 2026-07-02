#include <blackboard/editor/tools/selection/body.hpp>

#include <blackboard/draw.hpp>
#include <blackboard/editor/tools/selection/selection.hpp>




using bb::editor::SelectionBody,
    bb::Draw,
    bb::math::Rect;




SelectionBody::SelectionBody(Selection& selection) noexcept :
    selection(selection)
{}




void SelectionBody::update() noexcept
{

}




void SelectionBody::draw() noexcept
{
    if (!selection.active())
        return;

    const Rectangle rectangle = Rect::from_two_points(selection.start_position(), selection.end_position());
    Draw::rounded_rectangle(rectangle, 8, ColorAlpha(RED, 0.5));
    Draw::rounded_rectangle_outline(rectangle, 8, 2, ColorAlpha(RED, 0.85));
}