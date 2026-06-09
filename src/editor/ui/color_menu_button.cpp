#include <blackboard/editor/ui/color_menu_button.hpp>

#include <blackboard/editor/ui/color_menu.hpp>




using bb::editor::ColorMenuButton;




ColorMenuButton::ColorMenuButton(ColorMenu* const parent, const Color& color) noexcept
    : Button(parent, {}, DefaultSize, DefaultRadius, color, DefaultOutlineThickness, DefaultOutlineColor)
{
    clip = false;

    relative_position_.speed = size_.speed = SpringSpeed;
    relative_position_.damping = size_.damping = SpringDamping;

    color_.speed = ColorInterpolationSpeed;
}




void ColorMenuButton::on_entered() noexcept
{
    Button::on_entered();

    set_size(DefaultHoveredSize);
}


void ColorMenuButton::on_leaved() noexcept
{
    Button::on_leaved();

    set_size(DefaultSize);
}