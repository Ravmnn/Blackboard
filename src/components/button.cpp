#include <blackboard/components/button.hpp>

#include <algorithm>




Button::Button(Component* const parent, const Vector2& position, const Vector2& size, const float radius, const Color& color,
    const float outline_thickness, const Color& outline_color) noexcept
    : RoundedRectangle(parent, position, size, radius, color, outline_thickness, outline_color),
        Clickable(new MousePositionProvider)
{
    std::tie(base_color, hovered_color, pressed_color) = get_colors_keyframes_from_base_color(color);
    std::tie(outline_base_color, outline_hovered_color, outline_pressed_color) = get_colors_keyframes_from_base_color(outline_color);

    add_mouse_button_event(MainButtonId);

    main_button().down.subscribe([this]() { on_down(); });
    main_button().press.subscribe([this]() { on_press(); });
    main_button().release.subscribe([this]() { on_release(); });
    main_button().click.subscribe([this]() { on_click(); });
    main_button().drag_start.subscribe([this]() { on_drag_start(); });
    main_button().drag_end.subscribe([this]() { on_drag_end(); });
}




bool Button::is_point_over(const Vector2& point) const noexcept
{
    const Vector2 absolute_position = this->absolute_position();

    const Vector2 inner = {
        std::clamp(point.x, absolute_position.x + radius_, absolute_position.x + size().x - radius_),
        std::clamp(point.y, absolute_position.y + radius_, absolute_position.y + size().y - radius_)
    };

    const float dx = point.x - inner.x;
    const float dy = point.y - inner.y;

    return dx * dx + dy * dy <= radius_ * radius_;
}




void Button::update_self() noexcept
{
    RoundedRectangle::update_self();
    Clickable::update();
}




void Button::on_entered() noexcept
{

    set_color(hovered_color);
}


void Button::on_leaved() noexcept
{
    set_color(base_color);
}




void Button::on_press() noexcept
{
    set_color(pressed_color);
}


void Button::on_release() noexcept
{
    set_color(base_color);
}




std::tuple<Color, Color, Color> Button::get_colors_keyframes_from_base_color(const Color& color) noexcept
{
    constexpr uint8_t DecrementValue = 10;

    Color hovered_color = Color{
        .r = (uint8_t)(color.r - DecrementValue),
        .g = (uint8_t)(color.g - DecrementValue),
        .b = (uint8_t)(color.b - DecrementValue),
        .a = 255
    };

    Color pressed_color = Color{
        .r = (uint8_t)(hovered_color.r - DecrementValue),
        .g = (uint8_t)(hovered_color.g - DecrementValue),
        .b = (uint8_t)(hovered_color.b - DecrementValue),
        .a = 255
    };

    return { color, hovered_color, pressed_color };
}