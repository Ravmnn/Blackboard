#include <blackboard/mouse_button_set.hpp>

#include <blackboard/ui/clickable.hpp>




using bb::MouseButtonSet,
    bb::ui::Clickable;




void MouseButtonSet::update() noexcept
{
    update_events();
    update_mouse_buttons();
}


void MouseButtonSet::update_mouse_buttons() noexcept
{
    for (auto& [_, button] : mouse_buttons_)
        button->update();
}


void MouseButtonSet::update_events() noexcept
{
    down.update();
    press.update();
    release.update();
    click.update();
    drag_start.update();
    drag_end.update();

    late_down.update();
    late_press.update();
    late_release.update();
    late_click.update();
    late_drag_start.update();
    late_drag_end.update();
}




bb::MouseButtonEvent& MouseButtonSet::add_mouse_button_event(const int id, const MousePositionProvider& provider, Clickable* clickable) noexcept
{
    auto* const button = new MouseButtonEvent(id, provider);
    button->clickable = clickable;

    allocated_buttons_.push_back(std::unique_ptr<MouseButtonEvent>(button));
    mouse_buttons_.insert({ id, button });

    subscribe_callbacks_to_new_mouse_button(*button);

    return *button;
}


bb::MouseButtonEvent& MouseButtonSet::add_mouse_button_event_or_assign(MouseButtonEvent& button) noexcept
{
    mouse_buttons_.insert_or_assign(button.button_id, &button);
    subscribe_callbacks_to_new_mouse_button(button);

    return button;
}




void MouseButtonSet::subscribe_callbacks_to_new_mouse_button(MouseButtonEvent& button) noexcept
{
    button.down.subscribe([this](const auto& b) { down.trigger(b); }, "bb::Clickable::down_event_callback");
    button.press.subscribe([this](const auto& b) { press.trigger(b); }, "bb::Clickable::press_event_callback");
    button.release.subscribe([this](const auto& b) { release.trigger(b); }, "bb::Clickable::release_event_callback");
    button.click.subscribe([this](const auto& b) { click.trigger(b); }, "bb::Clickable::click_event_callback");
    button.drag_start.subscribe([this](const auto& b) { drag_start.trigger(b); }, "bb::Clickable::drag_start_event_callback");
    button.drag_end.subscribe([this](const auto& b) { drag_end.trigger(b); }, "bb::Clickable::drag_end_event_callback");

    button.late_down.subscribe([this](const auto& b) { late_down.trigger(b); }, "bb::Clickable::late_down_event_callback");
    button.late_press.subscribe([this](const auto& b) { late_press.trigger(b); }, "bb::Clickable::late_press_event_callback");
    button.late_release.subscribe([this](const auto& b) { late_release.trigger(b); }, "bb::Clickable::late_release_event_callback");
    button.late_click.subscribe([this](const auto& b) { late_click.trigger(b); }, "bb::Clickable::late_click_event_callback");
    button.late_drag_start.subscribe([this](const auto& b) { late_drag_start.trigger(b); }, "bb::Clickable::late_drag_start_event_callback");
    button.late_drag_end.subscribe([this](const auto& b) { late_drag_end.trigger(b); }, "bb::Clickable::late_drag_end_event_callback");
}