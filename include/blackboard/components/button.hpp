#pragma once

#include <tuple>

#include <blackboard/components/rounded_rectangle.hpp>
#include <blackboard/components/clickable.hpp>




class Button : public RoundedRectangle, public Clickable
{
public:
    static constexpr int MainButtonId = MOUSE_BUTTON_LEFT;


    Color base_color;
    Color hovered_color;
    Color pressed_color;

    Color outline_base_color;
    Color outline_hovered_color;
    Color outline_pressed_color;


    Button(Component* const parent, const Vector2& position, const Vector2& size, const float radius = 0, const Color& color = WHITE,
        const float outline_thickness = 1, const Color& outline_color = WHITE) noexcept;


    void update() noexcept override { RoundedRectangle::update(); }


    MouseButtonEvent& main_button() noexcept { return (*this)[MainButtonId]; }


    bool is_point_over(const Vector2& point) const noexcept override;


protected:
    void update_self() noexcept override;


    void on_entered() noexcept override;
    void on_leaved() noexcept override;

    virtual void on_down() noexcept {}
    virtual void on_press() noexcept;
    virtual void on_release() noexcept;
    virtual void on_click() noexcept {}
    virtual void on_drag_start() noexcept {}
    virtual void on_drag_end() noexcept {}


    static std::tuple<Color, Color, Color> get_colors_keyframes_from_base_color(const Color& base_color) noexcept;
};