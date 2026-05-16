#include <blackboard/editor/ui/color_menu_button.hpp>

#include <blackboard/editor/ui/radial_menu.hpp>




ColorMenuButton::ColorMenuButton(RadialMenu* const parent, const Color& color) noexcept
    : Button(parent, {}, DefaultSize, DefaultRadius, color, DefaultOutlineThickness, DefaultOutlineColor)
{
    clip = false;

    size_.speed = 20;
    size_.damping = 0.3;
}




void ColorMenuButton::on_entered() noexcept
{
    Button::on_entered();

    set_radius(DefaultHoveredRadius);
    set_size(DefaultHoveredSize);
}


void ColorMenuButton::on_leaved() noexcept
{
    Button::on_leaved();

    set_radius(DefaultRadius);
    set_size(DefaultSize);
}