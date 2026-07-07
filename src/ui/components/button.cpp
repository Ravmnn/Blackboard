#include <blackboard/ui/components/button.hpp>

#include <blackboard/ui/context.hpp>




using bb::ui::Button;




Button::Button(Component* const parent, const Vector2& position, const Vector2& size, const float radius, const Color& color,
    const float outline_thickness, const Color& outline_color) noexcept :

    RoundedRectangle(parent, position, size, radius, color, outline_thickness, outline_color),
    Clickable(MousePositionProvider::screen())
{
    add_mouse_button_event(MainButtonId, mouse_position_provider, this);

    main_button().down.subscribe([this](const auto& button) { on_down(button); });
    main_button().press.subscribe([this](const auto& button) { on_press(button); });
    main_button().release.subscribe([this](const auto& button) { on_release(button); });
    main_button().click.subscribe([this](const auto& button) { on_click(button); });
    main_button().drag_start.subscribe([this](const auto& button) { on_drag_start(button); });
    main_button().drag_end.subscribe([this](const auto& button) { on_drag_end(button); });
}




bool Button::is_point_over(const Vector2& point) const noexcept
{
    const Vector2 top_left = top_left_absolute_position();

    const Vector2 inner = {
        std::clamp(point.x, top_left.x + radius, top_left.x + size.current.x - radius),
        std::clamp(point.y, top_left.y + radius, top_left.y + size.current.y - radius)
    };

    const float dx = point.x - inner.x;
    const float dy = point.y - inner.y;

    return dx * dx + dy * dy <= radius * radius;
}




void Button::update_self() noexcept
{
    RoundedRectangle::update_self();
    Clickable::update();
}




void Button::on_press(const MouseButtonEvent& /* unused */) noexcept
{
    if (ui_context)
        ui_context->set_focus_to(this);
}