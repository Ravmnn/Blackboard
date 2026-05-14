#pragma once

#include <optional>
#include <functional>

#include <blackboard/event.hpp>
#include <blackboard/updateable.hpp>
#include <blackboard/mouse_position_provider.hpp>




class MouseButtonEvent : public Updateable
{
private:
    std::optional<Vector2> press_position_;

    float min_drag_distance_ = 5;
    bool is_drag_ = false;


public:
    using EventType = Event<>;
    using ConditionType = std::function<bool ()>;


    const MousePositionProvider& mouse_position_provider;

    int button_id;
    std::vector<ConditionType> conditions;

    EventType down;
    EventType press;
    EventType release;
    EventType click;
    EventType drag_start;
    EventType drag_end;


    explicit MouseButtonEvent(const int button_id = MOUSE_BUTTON_LEFT, const MousePositionProvider& mouse_position_provider = {}) noexcept
        : button_id(button_id), mouse_position_provider(mouse_position_provider) {}


    void update() noexcept override;


    bool is_clicked() const noexcept { return click.triggered(); }
    bool is_pressed() const noexcept { return press.triggered(); }
    bool is_released() const noexcept { return release.triggered(); }
    bool is_down() const noexcept { return down.triggered(); }


private:
    bool all_conditions_are_true() const noexcept;
    void update_drag_state() noexcept;

    void trigger_press_event() noexcept;
    void trigger_release_event() noexcept;
    void trigger_down_event() noexcept;


    float distance_from_press_position() const noexcept;
};