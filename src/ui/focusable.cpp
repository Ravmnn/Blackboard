#include <blackboard/ui/focusable.hpp>




using bb::ui::Focusable;




Focusable::Focusable() noexcept
{
    focused.subscribe([this]() noexcept { on_focus(); });
    unfocused.subscribe([this]() noexcept { on_unfocus(); });
}




void Focusable::focus() noexcept
{
    const bool was_focused = is_focused_;
    is_focused_ = true;

    if (!was_focused)
        focused.trigger();
}


void Focusable::unfocus() noexcept
{
    const bool was_focused = is_focused_;
    is_focused_ = false;

    if (was_focused)
        unfocused.trigger();
}


void Focusable::toggle() noexcept
{
    is_focused_ ? unfocus() : focus();
}