#pragma once

#include <blackboard/mouse_button_set.hpp>




namespace bb::ui
{




class Clickable : public MouseButtonSet
{
private:
    bool was_hover_ = false;
    bool hover_ = false;


public:
    const MousePositionProvider& mouse_position_provider;

    Event<> entered;
    Event<> leaved;
    Event<> hover;

    bool ignore_input = false;
    bool block_input = true;
    bool ignore_event_triggering = false;
    bool caught_mouse_input = false;


    explicit Clickable(const MousePositionProvider& mouse_position_provider) noexcept;


    void update() noexcept override;


    [[nodiscard]] bool is_hover() const noexcept { return hover_; }
    [[nodiscard]] bool is_mouse_over() const noexcept { return is_point_over(mouse_position_provider.mouse_position()); }
    [[nodiscard]] virtual bool is_point_over(const Vector2& point) const noexcept = 0;

    [[nodiscard]] virtual bool can_receive_input() const noexcept { return !ignore_input; }


protected:
    void update_interaction() noexcept;


    virtual void on_entered() noexcept {}
    virtual void on_leaved() noexcept {}
    virtual void on_hover() noexcept {}
};




}