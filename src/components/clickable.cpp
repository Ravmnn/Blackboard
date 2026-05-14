#include <blackboard/components/clickable.hpp>




Clickable::Clickable(const MousePositionProvider* const mouse_position_provider) noexcept
    : mouse_position_provider(mouse_position_provider)
{
    entered.subscribe([this]() { on_entered(); });
    leaved.subscribe([this]() { on_leaved(); });
    hover.subscribe([this]() { on_hover(); });
}




void Clickable::update() noexcept
{
    was_hover_ = hover_;
    hover_ = is_mouse_over();

    if (!was_hover_ && hover_)
        entered.trigger();

    if (was_hover_ && !hover_)
        leaved.trigger();

    if (hover_)
        hover.trigger();

    update_mouse_buttons();
}


void Clickable::update_mouse_buttons() noexcept
{
    for (auto& [_, button] : mouse_buttons_)
        button.update();
}




void Clickable::add_mouse_button_event(const int id) noexcept
{
    MouseButtonEvent button(id, *mouse_position_provider);
    button.conditions.push_back([this]() { return is_mouse_over(); });

    mouse_buttons_.insert({ id, button });
}




bool Clickable::all_buttons(const MouseButtonPredicate& predicate) const noexcept
{
    for (const auto& [id, button] : mouse_buttons_)
        if (!predicate(button))
            return false;

    return true;
}