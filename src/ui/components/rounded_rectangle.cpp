#include <blackboard/ui/components/rounded_rectangle.hpp>




using bb::ui::RoundedRectangle;




RoundedRectangle::RoundedRectangle(Component* const parent, const Vector2& position, const Vector2& size, const float radius,
    const Color& color, const float outline_thickness, const Color& outline_color) noexcept
    : Shape(parent, position, color, outline_thickness, outline_color),

    size_(create_default_spring(size)),
    radius_(create_default_exponential_interpolation(radius))
{}




void RoundedRectangle::update_self() noexcept
{
    Shape::update_self();

    size_.update();
    radius_.update();
}




void RoundedRectangle::draw_filled() noexcept
{
    const float normalized_radius = get_normalized_radius(radius_);
    DrawRectangleRounded({ top_left_absolute_position().x, top_left_absolute_position().y, size_.current.x, size_.current.y }, normalized_radius, (int)segments, color_);
}


void RoundedRectangle::draw_outlined() noexcept
{
    const float normalized_radius = get_normalized_radius(radius_);
    DrawRectangleRoundedLinesEx({ top_left_absolute_position().x, top_left_absolute_position().y, size_.current.x, size_.current.y }, normalized_radius, (int)segments, outline_thickness_, outline_color_);
}