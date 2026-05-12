#include <blackboard/components/shape.hpp>

#include <blackboard/components/component_stencil.hpp>




Shape::Shape(Component* const parent, const Vector2& position, const Color& color, const float outline_thickness, const Color& outline_color) noexcept
    : Component(parent, position),
    color(color),
    outline_thickness(outline_thickness),
    outline_color(outline_color)
{}




void Shape::draw_self() noexcept
{
    draw_filled();
    draw_outline();
}


void Shape::draw_outline() noexcept
{
    if (outline_thickness <= 0)
        return;

    ComponentStencil::mask_and_decrement(*this);
    draw_outlined();
}