#pragma once

#include <blackboard/event.hpp>
#include <blackboard/updateable.hpp>




class MouseButtonEvent : public Updateable
{
public:
    using EventType = Event<>;


    int button_id;

    EventType on_press, on_release, on_down;


    explicit MouseButtonEvent(const int button_id) noexcept : button_id(button_id) {}


    void update() noexcept override;


    bool is_pressed() const noexcept { return on_press.triggered(); }
    bool is_released() const noexcept { return on_release.triggered(); }
    bool is_down() const noexcept { return on_down.triggered(); }
};