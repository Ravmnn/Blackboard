#include <blackboard/editor/tools/selection/body.hpp>

#include <blackboard/draw.hpp>
#include <blackboard/editor/editor.hpp>
#include <blackboard/editor/tools/selection/selection.hpp>




using bb::editor::SelectionBody,
    bb::Draw,
    bb::math::Rect;




// TODO: selection should last until the user leave the selection mode
SelectionBody::SelectionBody(Selection& selection) noexcept :
    rectangle_position_({}, 6),
    rectangle_size_({}, 6),

    effect_spacing_animation_(60, 2),

    selection(selection)
{
    selection.changed_in.subscribe([this]() noexcept { on_selection_changed_in(); }, "editor::SelectionBody::selection_changed_in_callback");
}




void SelectionBody::update() noexcept
{
    if (selection.active())
        set_rectangle_to_selection_two_points();
    else
        set_rectangle_idle();

    update_animations();
    update_effects();
}


void SelectionBody::update_animations() noexcept
{
    rectangle_position_.update();
    rectangle_size_.update();

    effect_spacing_animation_.update();
}


void SelectionBody::update_effects() noexcept
{
    selection_effect.spacing = effect_spacing_animation_;

    selection_effect.update();
}


void SelectionBody::set_rectangle_to_selection_two_points() noexcept
{
    const Rectangle rectangle = Rect::from_two_points(selection.start_position(), selection.end_position());

    rectangle_position_ = { rectangle.x, rectangle.y };
    rectangle_size_ = { rectangle.width, rectangle.height };

    effect_spacing_animation_ = 60;
}


void SelectionBody::set_rectangle_idle() noexcept
{
    rectangle_position_ = selection.position() - Vector2{ IdleSize, IdleSize } / 2;
    rectangle_size_ = { IdleSize, IdleSize };

    effect_spacing_animation_ = 20;
}




void SelectionBody::draw() noexcept
{
    if (Vector2Length(rectangle_size_) <= 1)
    {
        DrawCircleV(rectangle_position_, Radius / 3, rectangle_outline_color_);
        return;
    }

    const Rectangle rectangle = Rect::from_two_points(rectangle_position_, rectangle_position_ + rectangle_size_);

    selection_effect.enable();
    Draw::rounded_rectangle(rectangle, Radius, rectangle_color_);
    selection_effect.disable();

    Draw::rounded_rectangle_outline(rectangle, Radius, 2, rectangle_outline_color_);
}




void SelectionBody::on_selection_changed_in() noexcept
{
    set_rectangle_idle();
    rectangle_position_.set_value_immediately(rectangle_position_.target);
}