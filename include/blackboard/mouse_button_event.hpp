#pragma once

#include <optional>

#include <blackboard/event.hpp>
#include <blackboard/updateable.hpp>
#include <blackboard/mouse_position_provider.hpp>




namespace bb
{




namespace ui { class Clickable; }


class MouseButtonEvent : public Updateable
{
private:
    std::optional<Vector2> press_position_;

    float min_drag_distance_ = 2;
    bool is_drag_ = false;

    bool magic_ = false;


public:
    using EventType = Event<>;


    const MousePositionProvider& mouse_position_provider;

    int button_id;

    EventType down;
    EventType press;
    EventType release;
    EventType click;
    EventType drag_start;
    EventType drag_end;

    const ui::Clickable* clickable = nullptr;


    explicit MouseButtonEvent(const int button_id = MOUSE_BUTTON_LEFT, const MousePositionProvider& mouse_position_provider = {}) noexcept
        : mouse_position_provider(mouse_position_provider), button_id(button_id) {}


    void update() noexcept override;


    [[nodiscard]] bool is_clicked() const noexcept { return click.triggered(); }
    [[nodiscard]] bool is_pressed() const noexcept { return press.triggered(); }
    [[nodiscard]] bool is_released() const noexcept { return release.triggered(); }
    [[nodiscard]] bool is_down() const noexcept { return down.triggered(); }


private:
    void update_drag_state() noexcept;

    void trigger_press_event() noexcept;
    void trigger_release_event() noexcept;
    void trigger_down_event() noexcept;


    [[nodiscard]] float distance_from_press_position() const noexcept;
};




}