#include <blackboard/editor/mouse_button_event.hpp>

#include <raymath.h>




void MouseButtonEvent::update() noexcept
{
    on_press.update();
    on_release.update();
    on_down.update();

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
        on_drag_start.trigger();
    }
}


void MouseButtonEvent::trigger_press_event() noexcept
{
    press_position_ = mouse_position_provider.mouse_position();

    on_press.trigger();
}


void MouseButtonEvent::trigger_release_event() noexcept
{
    on_release.trigger();

    if (is_drag_)
        on_drag_end.trigger();
    else
        on_click.trigger();

    is_drag_ = false;
    press_position_.reset();
}


void MouseButtonEvent::trigger_down_event() noexcept
{
    on_down.trigger();
}




float MouseButtonEvent::distance_from_press_position() const noexcept
{
    if (!press_position_)
        return 0;

    return Vector2Distance(*press_position_, mouse_position_provider.mouse_position());
}