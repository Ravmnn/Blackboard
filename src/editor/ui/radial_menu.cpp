#include <blackboard/editor/ui/radial_menu.hpp>




RadialMenu::RadialMenu(Component* const parent, const Vector2& relative_position, const float radius) noexcept
    : Component(parent, relative_position), radius_(create_default_interpolation(radius))
{}




void RadialMenu::update_self() noexcept
{
    Component::update_self();

    radius_.update();
    update_children_position();
}


void RadialMenu::update_children_position() noexcept
{
    constexpr float CircunferenceLength = 2 * PI;
    const float regular_length = CircunferenceLength / children.size();

    for (size_t i = 0; i < children.size(); i++)
    {
        const float angle = i * regular_length;
        const Vector2 position = { cos(angle) * radius_, sin(angle) * radius_ };

        children[i]->set_relative_position(position);
    }
}