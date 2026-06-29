#include <blackboard/editor/mouse_late_mode_indicator.hpp>

#include <blackboard/draw.hpp>
#include <blackboard/animation/interpolate.hpp>




using bb::editor::MouseLateModeIndicator;




MouseLateModeIndicator::MouseLateModeIndicator(const MousePositionProvider& mouse_provider, MouseButtonSet& buttons) noexcept :
    ring_radius_(0, 0, 0.45, 17),
    ring_transparency_(0, 4),

    mouse_provider(mouse_provider),
    buttons(buttons)
{
    buttons.press.subscribe([this](const MouseButtonEvent& button) { on_button_press(button); }, "editor::MouseLateModeIndicator::press_event_callback");
    buttons.release.subscribe([this](const MouseButtonEvent& button) { on_button_release(button); }, "editor::MouseLateModeIndicator::release_event_callback");
}




void MouseLateModeIndicator::update() noexcept
{
    if (!buttons.mouse_buttons().empty())
        time_to_enter_late_mode_ = buttons.mouse_buttons().begin()->second->time_to_enter_late_mode;

    if (!pressed_button_id_)
    {
        ring_radius_ = base_ring_radius;
        ring_transparency_ = 0;
    }
    else
    {
        if (!stopwatch_finished())
            ring_radius_ = animation::Interpolate::linear(base_ring_radius, base_ring_radius * entering_late_mode_radius_factor_, get_stopwatch_progress());
        else
            ring_radius_ = base_ring_radius * entered_late_mode_radius_factor;

        ring_transparency_ = 255 * get_stopwatch_progress();
    }

    update_animations();
}


void MouseLateModeIndicator::update_animations() noexcept
{
    ring_radius_.update();
    ring_transparency_.update();
}




void MouseLateModeIndicator::draw() noexcept
{
    Draw::circle_outline(mouse_provider.mouse_position(), ring_radius_, 2, get_ring_color(), 90);
}




void MouseLateModeIndicator::on_button_press(const MouseButtonEvent& button) noexcept
{
    if (!button.enable_late_mode || pressed_button_id_)
        return;

    mouse_button_late_mode_stopwatch_.reset();
    pressed_button_id_ = button.button_id;
}


void MouseLateModeIndicator::on_button_release(const MouseButtonEvent& button) noexcept
{
    if (!pressed_button_id_ || button.button_id != *pressed_button_id_)
        return;

    pressed_button_id_.reset();
}