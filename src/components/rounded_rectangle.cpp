#include <blackboard/components/rounded_rectangle.hpp>




RoundedRectangle::RoundedRectangle(Component* const parent, const Vector2& position, const Vector2& size, float radius, Color color) noexcept
    : Shape(parent, position, color),
    size_spring_(create_default_spring(size)),
    radius(radius)
{}




void RoundedRectangle::update() noexcept
{
    size_spring_.update();

    Shape::update();
}




void RoundedRectangle::draw_filled() noexcept
{
    const float normalized_radius = get_normalized_radius(radius);
    DrawRectangleRounded({ relative_position().x, relative_position().y, size_spring_.current.x, size_spring_.current.y }, normalized_radius, segments, color);
}


void RoundedRectangle::draw_outlined() noexcept
{
    const float normalized_radius = get_normalized_radius(radius);
    DrawRectangleRoundedLinesEx({ relative_position().x, relative_position().y, size_spring_.current.x, size_spring_.current.y }, normalized_radius, segments, border_thickness, border_color);
}