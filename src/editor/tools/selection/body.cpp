#include <blackboard/editor/tools/selection/body.hpp>

#include <blackboard/draw.hpp>
#include <blackboard/editor/editor.hpp>
#include <blackboard/editor/tools/selection/selection.hpp>




using bb::editor::SelectionBody,
    bb::Draw,
    bb::math::Rect;




SelectionBody::SelectionBody(Selection& selection) noexcept :
    rectangle_position_({}, {}, 0.6, 35),
    rectangle_size_({}, {}, 0.6, 35),

    selection(selection)
{
    selection.editor.environment_changed.subscribe([this]() noexcept { on_editor_environment_changed(); }, "editor::SelectionBody::editor_environment_changed_event_callback");
}




void SelectionBody::update() noexcept
{
    if (selection.active())
        set_rectangle_to_selection_two_points();
    else
        set_rectangle_idle();

    update_animations();
}


void SelectionBody::update_animations() noexcept
{
    rectangle_position_.update();
    rectangle_size_.update();
}


void SelectionBody::set_rectangle_to_selection_two_points() noexcept
{
    const Rectangle rectangle = Rect::from_two_points(selection.start_position(), selection.end_position());

    rectangle_position_ = { rectangle.x, rectangle.y };
    rectangle_size_ = { rectangle.width, rectangle.height };
}


void SelectionBody::set_rectangle_idle() noexcept
{
    Vector2 position = selection.position();
    position -= Vector2{ IdleSize, IdleSize } / 2;

    rectangle_position_ = position;
    rectangle_size_ = { IdleSize, IdleSize };
}




void SelectionBody::draw() noexcept
{
    if (Vector2Length(rectangle_size_) <= 1)
    {
        DrawCircleV(rectangle_position_, Radius / 3, rectangle_outline_color_);
        return;
    }

    const Rectangle rectangle = Rect::from_two_points(rectangle_position_, rectangle_position_ + rectangle_size_);

    Draw::rounded_rectangle(rectangle, Radius, rectangle_color_);
    Draw::rounded_rectangle_outline(rectangle, Radius, 2, rectangle_outline_color_);
}




void SelectionBody::on_editor_environment_changed() noexcept
{
    rectangle_position_.set_value_immediately(selection.position());
}