#pragma once

#include <optional>

#include <blackboard/event.hpp>
#include <blackboard/updateable.hpp>
#include <blackboard/editor/mouse_position_provider.hpp>




class MouseButtonEvent : public Updateable
{
private:
    std::optional<Vector2> press_position_;

    float min_drag_distance_ = 5;
    bool is_drag_ = false;


public:
    using EventType = Event<>;


    const MousePositionProvider& mouse_position_provider;

    int button_id;

    EventType on_click, on_press, on_release, on_down;
    EventType on_drag_start, on_drag_end;


    explicit MouseButtonEvent(const int button_id, const MousePositionProvider& mouse_position_provider = {}) noexcept
        : button_id(button_id), mouse_position_provider(mouse_position_provider) {}


    void update() noexcept override;


    bool is_clicked() const noexcept { return on_click.triggered(); }
    bool is_pressed() const noexcept { return on_press.triggered(); }
    bool is_released() const noexcept { return on_release.triggered(); }
    bool is_down() const noexcept { return on_down.triggered(); }


private:
    void update_drag_state() noexcept;

    void trigger_press_event() noexcept;
    void trigger_release_event() noexcept;
    void trigger_down_event() noexcept;


    float distance_from_press_position() const noexcept;
};