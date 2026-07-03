#include <blackboard/editor/ui/color_menu.hpp>

#include <blackboard/ui/components/rounded_rectangle.hpp>
#include <blackboard/ui/components/button.hpp>
#include <blackboard/ui/context.hpp>
#include <blackboard/editor/ui/color_menu_button.hpp>




using bb::editor::ColorMenu,
    bb::ui::Button,
    bb::ui::Clickable;




ColorMenu::ColorMenu(Component* const parent) noexcept : RadialLayout(parent, {}, 0)
{
    clip = false;
    visible = false;
    relative_position.immediate = true;

    radius_.set_value_immediately(HiddenRadius);
    set_children_opacity(HiddenOpacity);


    color_selected.subscribe([this](const Color& color) { on_color_selected(color); });
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

    ui_context->set_focus_to(this);
}


void ColorMenu::hide() noexcept
{
    set_radius(HiddenRadius);
    set_children_opacity(HiddenOpacity);
    set_children_ignore_interaction(true);
    trigger_children_leaved();

    is_shown_ = false;

    unfocus();
}




void ColorMenu::add_colors(const std::initializer_list<Color>& colors) noexcept
{
    for (const auto& color : colors)
        add_color(color);
}


void ColorMenu::add_color(const Color& color) noexcept
{
    new ColorMenuButton(this, color);
}




void ColorMenu::update_self() noexcept
{
    RadialLayout::update_self();

    for_each_children<Button>([this](Button* const child) {
        if (!child->is_clicked())
            return;

        color_selected.trigger(ColorAlpha(child->color, 255));
        child->leaved.trigger();
    });
}




Vector2 ColorMenu::get_position_for_child(Component& child, const size_t i) noexcept
{
    Vector2 position = RadialLayout::get_position_for_child(child, i);

    if (auto* button = dynamic_cast<Button*>(&child); button && button->is_hover())
        position *= 1.1;

    return position;
}




void ColorMenu::on_color_selected(const Color& /*unused*/) noexcept
{
    hide();
}




void ColorMenu::on_unfocus() noexcept
{
    if (ui_context->component_with_focus()->is_child_of(*this))
        return;

    hide();
}