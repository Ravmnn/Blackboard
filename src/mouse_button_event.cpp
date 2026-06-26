#include <blackboard/mouse_button_event.hpp>

#include <raymath.h>

#include <blackboard/ui/clickable.hpp>




using bb::MouseButtonEvent, bb::ui::Clickable;




void MouseButtonEvent::update() noexcept
{
    update_is_late_mode();
    update_mouse_button_events();

    if (clickable && !clickable->is_hover())
        return;

    if (IsMouseButtonDown(button_id) && is_late_ && !late_pressed_)
    {
        late_press.trigger();
        late_pressed_ = true;
    }

    if (IsMouseButtonPressed(button_id)) trigger_press_event();
    if (IsMouseButtonReleased(button_id)) trigger_release_event();
    if (IsMouseButtonDown(button_id)) trigger_down_event();

    update_drag_state();
}


void MouseButtonEvent::update_is_late_mode() noexcept
{
    if (late_mode_stopwatch_.elapsed_ms() >= time_to_enter_late_mode)
        is_late_ = enable_late_mode;

    if (!is_down())
        late_mode_stopwatch_.reset();
}


void MouseButtonEvent::update_mouse_button_events() noexcept
{
    down.update();
    press.update();
    release.update();
    click.update();
    drag_start.update();
    drag_end.update();

    late_down.update();
    late_press.update();
    late_release.update();
    late_click.update();
    late_drag_start.update();
    late_drag_end.update();
}


void MouseButtonEvent::update_drag_state() noexcept
{
    if (!press_position_)
        return;

    if (!is_drag_ && distance_from_press_position() >= min_drag_distance)
    {
        is_drag_ = true;

        if (!is_late_ || !exclusive_late_mode)
            drag_start.trigger();

        if (is_late_)
            late_drag_start.trigger();
    }
}




void MouseButtonEvent::trigger_press_event() noexcept
{
    press_position_ = mouse_position_provider.screen_mouse_position();
    late_mode_stopwatch_.reset();

    press.trigger();
}


void MouseButtonEvent::trigger_release_event() noexcept
{
    if (!is_late_ || !exclusive_late_mode)
        release.trigger();

    if (is_late_)
        late_release.trigger();


    if (is_drag_)
    {
        if (!is_late_ || !exclusive_late_mode)
            drag_end.trigger();

        if (is_late_)
            late_drag_end.trigger();
    }

    else if (!clickable || press_position_.has_value())
    {
        if (!is_late_ || !exclusive_late_mode)
            click.trigger();

        if (is_late_)
            late_click.trigger();
    }


    is_drag_ = false;
    is_late_ = false;
    late_pressed_ = false;
    press_position_.reset();
}


void MouseButtonEvent::trigger_down_event() noexcept
{
    if (!is_late_ || !exclusive_late_mode)
        down.trigger();

    if (is_late_)
        late_down.trigger();
}




float MouseButtonEvent::distance_from_press_position() const noexcept
{
    if (!press_position_)
        return 0;

    return Vector2Distance(*press_position_, mouse_position_provider.screen_mouse_position());
}