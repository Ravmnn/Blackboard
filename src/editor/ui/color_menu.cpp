#include <blackboard/editor/ui/color_menu.hpp>

#include <blackboard/ui/components/rounded_rectangle.hpp>
#include <blackboard/ui/components/button.hpp>




ColorMenu::ColorMenu() noexcept : RadialLayout(nullptr, {}, 0)
{
    color_selected.subscribe([this](const Color& color) { on_color_selected(color); });


    visible = false;

    relative_position_.immediate = true;

    radius_.set_value_immediately(HiddenRadius);
    set_children_opacity(HiddenOpacity);
}




void ColorMenu::toggle(const Vector2& position) noexcept
{
    if (!is_shown_)
        show(position);
    else
        hide();
}


void ColorMenu::show(const Vector2& position) noexcept
{
    if (is_shown_)
        return;

    set_absolute_position(position);

    set_radius(ShownRadius);
    set_children_opacity(ShownOpacity);
    set_children_ignore_interaction(false);

    visible = true;
    is_shown_ = true;
}


void ColorMenu::hide() noexcept
{
    set_radius(HiddenRadius);
    set_children_opacity(HiddenOpacity);
    set_children_ignore_interaction(true);

    is_shown_ = false;
}




void ColorMenu::update_self() noexcept
{
    RadialLayout::update_self();

    for_each_children<Button>([this](Button* const child) {
        if (!child->is_released())
            return;

        color_selected.trigger(child->color());
        child->leaved.trigger();
    });
}




Vector2 ColorMenu::get_position_for_child(Component& child, const size_t i) noexcept
{
    Vector2 position = RadialLayout::get_position_for_child(child, i);

    if (auto button = dynamic_cast<Button*>(&child); button && button->is_hover())
        position *= 1.1;

    return position;
}




void ColorMenu::on_color_selected(const Color& color) noexcept
{
    hide();
}