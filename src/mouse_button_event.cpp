#include <blackboard/mouse_button_event.hpp>

#include <raymath.h>

#include <blackboard/ui/clickable.hpp>




void MouseButtonEvent::update() noexcept
{
    press.update();
    release.update();
    down.update();
    click.update();
    drag_start.update();
    drag_end.update();

    if (clickable && !clickable->is_hover())
        return;

    if (IsMouseButtonPressed(button_id)) trigger_press_event();
    if (IsMouseButtonReleased(button_id)) trigger_release_event();
    if (IsMouseButtonDown(button_id)) trigger_down_event();

    update_drag_state();
}


void MouseButtonEvent::update_drag_state() noexcept
{
    if (!press_position_)
        return;

    if (!is_drag_ && distance_from_press_position() >= min_drag_distance_)
    {
        is_drag_ = true;
        drag_start.trigger();
    }
}


void MouseButtonEvent::trigger_press_event() noexcept
{
    press_position_ = mouse_position_provider.mouse_position();

    press.trigger();
    magic_ = true;
}


void MouseButtonEvent::trigger_release_event() noexcept
{
    release.trigger();

    if (is_drag_)
        drag_end.trigger();
    else if (!clickable || magic_)
        click.trigger();

    is_drag_ = false;
    press_position_.reset();
    magic_ = false;
}


void MouseButtonEvent::trigger_down_event() noexcept
{
    down.trigger();
}




float MouseButtonEvent::distance_from_press_position() const noexcept
{
    if (!press_position_)
        return 0;

    return Vector2Distance(*press_position_, mouse_position_provider.mouse_position());
}