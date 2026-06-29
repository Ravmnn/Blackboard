#include <blackboard/ui/clickable.hpp>




using bb::ui::Clickable;




Clickable::Clickable(const MousePositionProvider& mouse_position_provider) noexcept
    : mouse_position_provider(mouse_position_provider)
{
    entered.subscribe([this]() { on_entered(); }, "bb::Clickable::entered_event_callback");
    leaved.subscribe([this]() { on_leaved(); }, "bb::Clickable::leaved_event_callback");
    hover.subscribe([this]() { on_hover(); }, "bb::Clickable::hover_event_callback");
}




void Clickable::update() noexcept
{
    update_interaction();

    MouseButtonSet::update();
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