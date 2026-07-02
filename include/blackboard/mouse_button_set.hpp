#pragma once

#include <map>
#include <memory>

#include <blackboard/mouse_button_event.hpp>




namespace bb
{




class MouseButtonSet : public Updateable
{
private:
    std::vector<std::unique_ptr<MouseButtonEvent>> allocated_buttons_;


protected:
    std::map<int, MouseButtonEvent*> mouse_buttons_;


public:
    using ButtonEvent = Event<const MouseButtonEvent&>;


    ButtonEvent down;
    ButtonEvent press;
    ButtonEvent release;
    ButtonEvent click;
    ButtonEvent drag_start;
    ButtonEvent drag_end;

    ButtonEvent late_down;
    ButtonEvent late_press;
    ButtonEvent late_release;
    ButtonEvent late_click;
    ButtonEvent late_drag_start;
    ButtonEvent late_drag_end;


    MouseButtonEvent& operator[](const int button) { return *mouse_buttons_[button]; }


    void update() noexcept override;


    void reset_buttons_state() noexcept;


    [[nodiscard]] const std::map<int, MouseButtonEvent*>& mouse_buttons() const noexcept { return mouse_buttons_; }

    [[nodiscard]] bool is_down() const noexcept { return down.triggered(); }
    [[nodiscard]] bool is_pressed() const noexcept { return press.triggered(); }
    [[nodiscard]] bool is_released() const noexcept { return release.triggered(); }
    [[nodiscard]] bool is_clicked() const noexcept { return click.triggered(); }
    [[nodiscard]] bool has_drag_started() const noexcept { return drag_start.triggered(); }
    [[nodiscard]] bool has_drag_ended() const noexcept { return drag_end.triggered(); }

    [[nodiscard]] bool is_late_down() const noexcept { return late_down.triggered(); }
    [[nodiscard]] bool is_late_pressed() const noexcept { return late_press.triggered(); }
    [[nodiscard]] bool is_late_released() const noexcept { return late_release.triggered(); }
    [[nodiscard]] bool is_late_clicked() const noexcept { return late_click.triggered(); }
    [[nodiscard]] bool has_late_drag_started() const noexcept { return late_drag_start.triggered(); }
    [[nodiscard]] bool has_late_drag_ended() const noexcept { return late_drag_end.triggered(); }


    MouseButtonEvent& add_mouse_button_event(int id, const MousePositionProvider& provider = {}, ui::Clickable* clickable = nullptr) noexcept;
    MouseButtonEvent& add_mouse_button_event_or_assign(MouseButtonEvent& button) noexcept;


protected:
    void update_mouse_buttons() noexcept;
    void update_events() noexcept;

    void subscribe_callbacks_to_new_mouse_button(MouseButtonEvent& button) noexcept;
};




}