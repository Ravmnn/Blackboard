#include <blackboard/mouse_button_event.hpp>

#include <raymath.h>

#include <blackboard/ui/clickable.hpp>




using bb::MouseButtonEvent, bb::ui::Clickable;




MouseButtonEvent::MouseButtonEvent(const int button_id, const MousePositionProvider& mouse_position_provider) noexcept
    : mouse_position_provider(mouse_position_provider), button_id(button_id)
{
    enable();
}




void MouseButtonEvent::update() noexcept
{
    if (!active())
        return;

    update_is_late_mode();
    update_mouse_button_events();

    if (clickable && !clickable->is_hover())
        return;

    update_first_late_mode_press();

    if (is_button_pressed()) trigger_press_event();
    if (is_button_released()) trigger_release_event();
    if (is_button_down()) trigger_down_event();

    update_drag_state();
}


void MouseButtonEvent::update_is_late_mode() noexcept
{
    if (!is_button_down())
        late_mode_stopwatch_.reset();

    if (late_mode_stopwatch_.elapsed_ms() >= time_to_enter_late_mode && !is_drag_)
        is_late_ = enable_late_mode;
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


void MouseButtonEvent::update_first_late_mode_press() noexcept
{
    if (!is_button_down() || !is_late_ || late_pressed_)
        return;

    late_press.trigger(*this);
    late_pressed_ = true;
}


void MouseButtonEvent::update_drag_state() noexcept
{
    if (!press_position_)
        return;

    if (!is_drag_ && distance_from_press_position() >= min_drag_distance)
    {
        is_drag_ = true;

        if (!is_late_ || !exclusive_late_mode)
            drag_start.trigger(*this);

        if (is_late_)
            late_drag_start.trigger(*this);
    }
}




void MouseButtonEvent::trigger_press_event() noexcept
{
    press_position_ = mouse_position_provider.screen_mouse_position();
    late_mode_stopwatch_.reset();

    press.trigger(*this);
}


void MouseButtonEvent::trigger_release_event() noexcept
{
    if (!is_late_ || !exclusive_late_mode)
        release.trigger(*this);

    if (is_late_)
        late_release.trigger(*this);

    if (is_drag_)
    {
        if (!is_late_ || !exclusive_late_mode)
            drag_end.trigger(*this);

        if (is_late_)
            late_drag_end.trigger(*this);
    }

    else if (!clickable || press_position_.has_value())
    {
        if (!is_late_ || !exclusive_late_mode)
            click.trigger(*this);

        if (is_late_)
            late_click.trigger(*this);
    }


    reset_state();
}


void MouseButtonEvent::trigger_down_event() noexcept
{
    if (!is_late_ || !exclusive_late_mode)
        down.trigger(*this);

    if (is_late_)
        late_down.trigger(*this);
}




void MouseButtonEvent::reset_state() noexcept
{
    is_drag_ = false;
    is_late_ = false;
    late_pressed_ = false;
    press_position_.reset();
}




float MouseButtonEvent::distance_from_press_position() const noexcept
{
    if (!press_position_)
        return 0;

    return Vector2Distance(*press_position_, mouse_position_provider.screen_mouse_position());
}