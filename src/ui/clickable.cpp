#include <blackboard/ui/clickable.hpp>

#include <algorithm>




using bb::ui::Clickable;




Clickable::Clickable(const MousePositionProvider* const mouse_position_provider) noexcept
    : mouse_position_provider(mouse_position_provider)
{
    entered.subscribe([this]() { on_entered(); });
    leaved.subscribe([this]() { on_leaved(); });
    hover.subscribe([this]() { on_hover(); });
}




void Clickable::update() noexcept
{
    update_interaction();
    update_mouse_buttons();
}


void Clickable::update_interaction() noexcept
{
    was_hover_ = hover_;
    hover_ = caught_mouse_input && is_mouse_over();

    if (ignore_event_triggering)
        return;

    if (was_hover_ && !hover_)
        leaved.trigger();

    if (!was_hover_ && hover_)
        entered.trigger();

    if (hover_)
        hover.trigger();
}


void Clickable::update_mouse_buttons() noexcept
{
    for (auto& [_, button] : mouse_buttons_)
        button->update();
}




void Clickable::add_mouse_button_event(const int id) noexcept
{
    auto* button = new MouseButtonEvent(id, *mouse_position_provider);
    button->clickable = this;

    allocated_buttons_.push_back(std::unique_ptr<MouseButtonEvent>(button));
    mouse_buttons_.insert({ id, button });
}




bool Clickable::any_buttons(const MouseButtonPredicate& predicate) const noexcept
{
    return std::ranges::any_of(mouse_buttons_, [&](const auto& pair) {
        return predicate(*pair.second);
    });
}