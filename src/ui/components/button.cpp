#include <blackboard/ui/components/button.hpp>

#include <algorithm>




using bb::ui::Button;




Button::Button(Component* const parent, const Vector2& position, const Vector2& size, const float radius, const Color& color,
    const float outline_thickness, const Color& outline_color) noexcept
    : RoundedRectangle(parent, position, size, radius, color, outline_thickness, outline_color),
        Clickable(new MousePositionProvider) // TODO: mouse provider free is responsibility of this class
{
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
    const Vector2 top_left = top_left_absolute_position();

    const Vector2 inner = {
        std::clamp(point.x, top_left.x + radius_, top_left.x + size().x - radius_),
        std::clamp(point.y, top_left.y + radius_, top_left.y + size().y - radius_)
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