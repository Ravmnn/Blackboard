#include <blackboard/editor/ui/radial_layout.hpp>




using bb::editor::RadialLayout;




RadialLayout::RadialLayout(Component* const parent, const Vector2& relative_position, const float radius) noexcept
    : Component(parent, relative_position), radius_(create_default_exponential_interpolation(radius))
{}




void RadialLayout::update_self() noexcept
{
    Component::update_self();

    radius_.update();
    update_children_position();
}


void RadialLayout::update_children_position() noexcept
{
    for (size_t i = 0; i < children.size(); i++)
        children[i]->relative_position = get_position_for_child(*children[i], i);
}




Vector2 RadialLayout::get_position_for_child(Component& /*unused*/, const size_t i) noexcept
{
    constexpr float CircunferenceLength = 2 * PI;
    const float regular_length = CircunferenceLength / (float)children.size();

    const float angle = (float)i * regular_length;
    const Vector2 position = { cos(angle) * radius_, sin(angle) * radius_ };

    return position;
}