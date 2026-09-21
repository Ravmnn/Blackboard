#include <blackboard/ui/components/rounded_rectangle.hpp>

#include <rlgl.h>

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
{
}




void RoundedRectangle::update_self() noexcept
{
    Shape::update_self();

    size.update();
    radius.update();

    update_effect();
}


void RoundedRectangle::update_effect() noexcept
{
    effect_.position = absolute_position();
    effect_.size = size;
    effect_.radius = radius;
    effect_.outline_thickness = outline_thickness;
    effect_.color = color;
    effect_.outline_color = outline_color;

    effect_.update();
}




void RoundedRectangle::draw_self() noexcept
{
    const uint8_t stencil_id = this->stencil_id();

    Stencil::disable_color();
    Stencil::begin_write(GL_EQUAL, stencil_id, GL_INCR);
    draw_fill();

    Stencil::begin_write(GL_EQUAL, stencil_id - 1, GL_DECR);
    draw_outline();

    Stencil::begin_write(GL_LEQUAL, stencil_id, GL_KEEP);
    Stencil::enable_color();

    draw_both();
}


void RoundedRectangle::draw_both() noexcept
{
    Draw::sdf_rounded_rectangle(effect_);
}


void RoundedRectangle::draw_fill() noexcept
{
    Draw::sdf_rounded_rectangle_fill(effect_);
}


void RoundedRectangle::draw_outline() noexcept
{
    Draw::sdf_rounded_rectangle_outline(effect_);
}