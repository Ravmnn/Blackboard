#pragma once

#include <blackboard/ui/clickable.hpp>
#include <blackboard/ui/focusable.hpp>
#include <blackboard/ui/components/rounded_rectangle.hpp>




namespace bb::ui
{




class Button : public RoundedRectangle, public Clickable, public Focusable
{
public:
    static constexpr int MainButtonId = MOUSE_BUTTON_LEFT;


    Button(Component* parent, const Vector2& position, const Vector2& size, float radius = 0, const Color& color = WHITE,
        float outline_thickness = 0, const Color& outline_color = WHITE) noexcept;


    void update() noexcept override { RoundedRectangle::update(); }


    MouseButtonEvent& main_button() noexcept { return (*this)[MainButtonId]; }


    [[nodiscard]] bool is_point_over(const Vector2& point) const noexcept override;

    [[nodiscard]] bool can_receive_input() const noexcept override { return Clickable::can_receive_input() && visible; }


protected:
    void update_self() noexcept override;


    void on_entered() noexcept override {}
    void on_leaved() noexcept override {}

    virtual void on_down(const MouseButtonEvent& /* unused */) noexcept {}
    virtual void on_press(const MouseButtonEvent& /* unused */) noexcept;
    virtual void on_release(const MouseButtonEvent& /* unused */) noexcept {}
    virtual void on_click(const MouseButtonEvent& /* unused */) noexcept {}
    virtual void on_drag_start(const MouseButtonEvent& /* unused */) noexcept {}
    virtual void on_drag_end(const MouseButtonEvent& /* unused */) noexcept {}
};




}