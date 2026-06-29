#include <blackboard/ui/components/shape.hpp>

#include <blackboard/ui/components/component_stencil.hpp>




using bb::ui::Shape;




Shape::Shape(Component* const parent, const Vector2& position, const Color& color, const float outline_thickness, const Color& outline_color) noexcept
    : Component(parent, position),

    color_(create_default_exponential_interpolation(color)),
    outline_thickness_(create_default_exponential_interpolation(outline_thickness)),
    outline_color_(create_default_exponential_interpolation(outline_color))
{}




void Shape::update_self() noexcept
{
    Component::update_self();

    color_.update();
    outline_thickness_.update();
    outline_color_.update();
}




void Shape::draw_self() noexcept
{
    draw_filled();
    draw_outline();
}


void Shape::    draw_outline() noexcept
{
    if (outline_thickness_ <= 0)
        return;

    ComponentStencil::mask_and_decrement(*this);
    draw_outlined();
}