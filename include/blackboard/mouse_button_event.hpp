#pragma once

#include <blackboard/activatable.hpp>
#include <blackboard/stopwatch.hpp>
#include <blackboard/mouse_position_provider.hpp>




namespace bb
{




namespace ui { class Clickable; }


class MouseButtonEvent : public Updateable, public Activatable
{
private:
    std::optional<Vector2> press_position_;

    bool is_drag_ = false;
    bool is_late_ = false;
    bool late_pressed_ = false;

    Stopwatch late_mode_stopwatch_;


public:
    using EventType = Event<const MouseButtonEvent&>;


    const MousePositionProvider& mouse_position_provider;

    float min_drag_distance = 20;

    std::chrono::milliseconds time_to_enter_late_mode = std::chrono::milliseconds(300);
    bool enable_late_mode = false;
    bool exclusive_late_mode = false;

    int button_id;

    EventType down;
    EventType press;
    EventType release;
    EventType click;
    EventType drag_start;
    EventType drag_end;

    EventType late_down;
    EventType late_press;
    EventType late_release;
    EventType late_click;
    EventType late_drag_start;
    EventType late_drag_end;

    const ui::Clickable* clickable = nullptr;


    explicit MouseButtonEvent(int button_id = MOUSE_BUTTON_LEFT, const MousePositionProvider& mouse_position_provider = {}) noexcept;


    bool operator==(const MouseButtonEvent& other) const noexcept { return button_id == other.button_id; }


    void update() noexcept override;


    void reset_state() noexcept;


    [[nodiscard]] bool is_button_down() const noexcept { return IsMouseButtonDown(button_id); }
    [[nodiscard]] bool is_button_pressed() const noexcept { return IsMouseButtonPressed(button_id); }
    [[nodiscard]] bool is_button_released() const noexcept { return IsMouseButtonReleased(button_id); }

    [[nodiscard]] bool is_down() const noexcept { return down.triggered(); }
    [[nodiscard]] bool is_clicked() const noexcept { return click.triggered(); }
    [[nodiscard]] bool is_pressed() const noexcept { return press.triggered(); }
    [[nodiscard]] bool is_released() const noexcept { return release.triggered(); }

    [[nodiscard]] bool is_late() const noexcept { return is_late_; }

    [[nodiscard]] bool is_late_down() const noexcept { return late_down.triggered(); }
    [[nodiscard]] bool is_late_clicked() const noexcept { return late_click.triggered(); }
    [[nodiscard]] bool is_late_pressed() const noexcept { return late_press.triggered(); }
    [[nodiscard]] bool is_late_released() const noexcept { return late_release.triggered(); }


private:
    void update_is_late_mode() noexcept;
    void update_mouse_button_events() noexcept;
    void update_first_late_mode_press() noexcept;
    void update_drag_state() noexcept;

    void trigger_press_event() noexcept;
    void trigger_release_event() noexcept;
    void trigger_down_event() noexcept;


    [[nodiscard]] float distance_from_press_position() const noexcept;
};




}