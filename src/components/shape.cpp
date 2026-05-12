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
    begin_drawing();

    draw_filled();
    draw_outline();

    end_drawing();
}


void Shape::draw_outline() noexcept
{
    if (outline_thickness <= 0)
        return;

    const uint8_t stencil_value = ComponentStencil::get_stencil_value_for_component(*this);

    ComponentStencil::mask_and_decrement(stencil_value);
    draw_outlined();
}