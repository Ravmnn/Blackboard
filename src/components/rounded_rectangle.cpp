#include <blackboard/components/rounded_rectangle.hpp>




RoundedRectangle::RoundedRectangle(Component* const parent, const Vector2& position, const Vector2& size, float radius, Color color) noexcept
    : Shape(parent, position, color),
    size_spring_(create_default_spring(size)),
    radius(radius)
{}




void RoundedRectangle::update_self() noexcept
{
    Shape::update_self();

    size_spring_.update();
}




void RoundedRectangle::draw_filled() noexcept
{
    const float normalized_radius = get_normalized_radius(radius);
    DrawRectangleRounded({ absolute_position().x, absolute_position().y, size_spring_.current.x, size_spring_.current.y }, normalized_radius, segments, color);
}


void RoundedRectangle::draw_outlined() noexcept
{
    const float normalized_radius = get_normalized_radius(radius);
    DrawRectangleRoundedLinesEx({ absolute_position().x, absolute_position().y, size_spring_.current.x, size_spring_.current.y }, normalized_radius, segments, outline_thickness, outline_color);
}