#include <blackboard/components/shape.hpp>




Shape::Shape(Component* const parent, const Vector2& position, const Color& color, const float border_thickness, const Color& border_color) noexcept
    : Component(parent, position),
    color(color),
    border_thickness(border_thickness),
    border_color(border_color)
{}




void Shape::draw() noexcept
{
    draw_filled();

    if (border_thickness > 0)
        draw_outlined();

    Component::draw();
}