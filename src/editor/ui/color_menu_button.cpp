#include <blackboard/editor/ui/color_menu_button.hpp>

#include <blackboard/editor/ui/color_menu.hpp>




using bb::editor::ColorMenuButton;




ColorMenuButton::ColorMenuButton(ColorMenu* const parent, const Color& color) noexcept
    : Button(parent, {}, DefaultSize, DefaultRadius, color, DefaultOutlineThickness, DefaultOutlineColor)
{
    clip = false;

    relative_position.speed = size.speed = SpringSpeed;
    relative_position.damping = size.damping = SpringDamping;

    this->color.speed = ColorInterpolationSpeed;
}




void ColorMenuButton::on_entered() noexcept
{
    Button::on_entered();

    size = DefaultHoveredSize;
}


void ColorMenuButton::on_leaved() noexcept
{
    Button::on_leaved();

    size = DefaultSize;
}