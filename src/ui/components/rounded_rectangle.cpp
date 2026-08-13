#include <blackboard/ui/components/rounded_rectangle.hpp>

#include <blackboard/draw.hpp>




using
bb::Draw,
bb::ui::RoundedRectangle;




RoundedRectangle::RoundedRectangle(Component* const parent, const Vector2& position, const Vector2& size, const float radius,
    const Color& color, const float outline_thickness, const Color& outline_color) noexcept
    : Shape(parent, position, color, outline_thickness, outline_color),

    size(create_default_spring(size)),
    radius(create_default_exponential_interpolation(radius))
{}




void RoundedRectangle::update_self() noexcept
{
    Shape::update_self();

    size.update();
    radius.update();
}




void RoundedRectangle::draw_filled() noexcept
{
    Draw::rounded_rectangle(top_left_absolute_position(), size, radius, color, resolution);
}


void RoundedRectangle::draw_outlined() noexcept
{
    Draw::rounded_rectangle_outline(top_left_absolute_position(), size, radius, outline_thickness, outline_color, resolution);
}