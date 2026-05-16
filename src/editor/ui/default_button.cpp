#include <blackboard/editor/ui/default_button.hpp>




DefaultButton::DefaultButton(Component* const parent, const Vector2& position, const Vector2& size, const float radius = 0, const Color& color,
    const float outline_thickness, const Color& outline_color) noexcept
    : Button(parent, position, size, radius, color, outline_thickness, outline_color)
{
    std::tie(base_color, hovered_color, pressed_color) = get_colors_keyframes_from_base_color(color);
    std::tie(outline_base_color, outline_hovered_color, outline_pressed_color) = get_colors_keyframes_from_base_color(outline_color);
}




std::tuple<Color, Color, Color> DefaultButton::get_colors_keyframes_from_base_color(const Color& color) noexcept
{
    constexpr uint8_t DecrementValue = 20;

    Color hovered_color = Color{
        .r = (uint8_t)(color.r >= DecrementValue ? color.r - DecrementValue : color.r),
        .g = (uint8_t)(color.g >= DecrementValue ? color.g - DecrementValue : color.g),
        .b = (uint8_t)(color.b >= DecrementValue ? color.b - DecrementValue : color.b),
        .a = 255
    };

    Color pressed_color = Color{
        .r = (uint8_t)(hovered_color.r >= DecrementValue ? hovered_color.r - DecrementValue : hovered_color.r),
        .g = (uint8_t)(hovered_color.g >= DecrementValue ? hovered_color.g - DecrementValue : hovered_color.g),
        .b = (uint8_t)(hovered_color.b >= DecrementValue ? hovered_color.b - DecrementValue : hovered_color.b),
        .a = 255
    };

    return { color, hovered_color, pressed_color };
}