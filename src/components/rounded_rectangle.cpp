#include <blackboard/components/rounded_rectangle.hpp>




RoundedRectangle::RoundedRectangle(const Vector2& position, const Vector2& size, float radius, Color color) noexcept : Shape(position),
    size_spring_(create_default_spring(size)),
    radius(radius),
    color(color)
{}




void RoundedRectangle::update() noexcept
{
    Component::update();
    size_spring_.update();
}




void RoundedRectangle::draw_filled() noexcept
{
    const float normalized_radius = get_normalized_radius();
    DrawRectangleRounded({ position().x, position().y, size_spring_.current.x, size_spring_.current.y }, normalized_radius, segments, color);
}


void RoundedRectangle::draw_outlined() noexcept
{
    const float normalized_radius = get_normalized_radius();
    DrawRectangleRoundedLinesEx({ position().x, position().y, size_spring_.current.x, size_spring_.current.y }, normalized_radius, segments, border_thickness, border_color);
}