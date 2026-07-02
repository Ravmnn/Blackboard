#include <blackboard/editor/mouse_late_mode_indicator.hpp>

#include <blackboard/draw.hpp>
#include <blackboard/hsv.hpp>
#include <blackboard/animation/interpolate.hpp>




using bb::editor::MouseLateModeIndicator;




MouseLateModeIndicator::MouseLateModeIndicator(const MousePositionProvider& mouse_provider, MouseButtonSet& buttons) noexcept :
    ring_radius_(0, 0, 0.3, 25),
    ring_transparency_(0, 3),

    mouse_provider(mouse_provider),
    buttons(buttons)
{
    buttons.press.subscribe([this](const MouseButtonEvent& button) { on_button_press(button); }, "editor::MouseLateModeIndicator::press_event_callback");
    buttons.release.subscribe([this](const MouseButtonEvent& button) { on_button_release(button); }, "editor::MouseLateModeIndicator::release_event_callback");
    buttons.late_release.subscribe([this](const MouseButtonEvent& button) { on_button_release(button); }, "editor::MouseLateModeIndicator::late_release_event_callback");
    buttons.drag_start.subscribe([this](const MouseButtonEvent& button) { on_button_drag_start(button); }, "editor::MouseLateModeIndicator::drag_start_event_callback");
}




void MouseLateModeIndicator::update() noexcept
{
    if (!buttons.mouse_buttons().empty())
        time_to_enter_late_mode_ = buttons.mouse_buttons().begin()->second->time_to_enter_late_mode;

    if (pressed_button_ && pressed_button_ != &buttons[pressed_button_->button_id])
        leave_late_mode();

    update_appearence();
    update_animations();
}


void MouseLateModeIndicator::update_appearence() noexcept
{
    if (!pressed_button_)
        base_appearence();
    else
        late_mode_appearence();
}


void MouseLateModeIndicator::base_appearence() noexcept
{
    ring_radius_ = base_ring_radius;
    ring_transparency_ = 0;
}


void MouseLateModeIndicator::late_mode_appearence() noexcept
{
    if (!has_entered_late_mode())
    {
        ring_radius_ = animation::Interpolate::linear(base_ring_radius, base_ring_radius * entering_late_mode_radius_factor_, get_late_mode_entering_progress());
        ring_transparency_ = entering_late_mode_final_alpha_ * get_late_mode_entering_progress();
    }
    else
    {
        ring_radius_ = base_ring_radius * entered_late_mode_radius_factor;
        ring_transparency_ = entered_late_mode_final_alpha_;
    }
}


void MouseLateModeIndicator::update_animations() noexcept
{
    ring_radius_.update();
    ring_transparency_.update();
}




Color MouseLateModeIndicator::get_ring_color() const noexcept
{
    Color color = this->color;

    if (!has_entered_late_mode())
        color = HSV::apply_saturation(color, idle_saturation);

    return ColorAlpha(color, ring_transparency_ / 255);
}




void MouseLateModeIndicator::draw() noexcept
{
    Draw::circle_outline(mouse_provider.mouse_position(), ring_radius_, 2, get_ring_color(), 90);
}



void MouseLateModeIndicator::enter_late_mode(const MouseButtonEvent& button) noexcept
{
    mouse_button_late_mode_stopwatch_.reset();
    pressed_button_ = &buttons[button.button_id];
}


void MouseLateModeIndicator::leave_late_mode() noexcept
{
    pressed_button_ = nullptr;
}




void MouseLateModeIndicator::on_button_press(const MouseButtonEvent& button) noexcept
{
    if (!button.enable_late_mode || pressed_button_)
        return;

    enter_late_mode(button);
}


void MouseLateModeIndicator::on_button_release(const MouseButtonEvent& button) noexcept
{
    if (!pressed_button_ || button.button_id != pressed_button_->button_id)
        return;

    leave_late_mode();
}


void MouseLateModeIndicator::on_button_drag_start(const MouseButtonEvent& /* unused */) noexcept
{
    if (!has_entered_late_mode())
        leave_late_mode();
}