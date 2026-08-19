#include <blackboard/ui/components/rounded_rectangle.hpp>

#include <blackboard/draw.hpp>
#include <blackboard/ui/components/component_stencil.hpp>




using
bb::Draw,
bb::rendering::Stencil,
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

    update_effect();
}


void RoundedRectangle::update_effect() noexcept
{
    effect_.position = size / 2;
    effect_.size = size;
    effect_.radius = radius;
    effect_.outline_thickness = outline_thickness;
    effect_.color = color;
    effect_.outline_color = outline_color;

    effect_.update();
}




void RoundedRectangle::draw_filled() noexcept
{
    // TODO: using origin as the bottom of the screen instead of the geometry

    effect_.enable();
    DrawRectangleV(top_left_absolute_position(), size, WHITE);
    effect_.disable();
}


void RoundedRectangle::draw_outlined() noexcept
{
    // TODO: stencil prolly gonna break
    Stencil::disable_color();
    Draw::rounded_rectangle_outline(top_left_absolute_position(), size, radius, outline_thickness, outline_color, resolution);
    Stencil::enable_color();
}