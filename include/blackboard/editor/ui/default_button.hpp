#pragma once

#include <blackboard/ui/components/button.hpp>




namespace bb::editor
{




class DefaultButton : public ui::Button
{
public:
    Color base_color;
    Color hovered_color;
    Color pressed_color;

    Color outline_base_color;
    Color outline_hovered_color;
    Color outline_pressed_color;


    DefaultButton(Component* parent, const Vector2& position, const Vector2& size, float radius = 0, const Color& color = WHITE,
        float outline_thickness = 0, const Color& outline_color = WHITE) noexcept;


protected:
    void on_entered() noexcept override { color = hovered_color; }
    void on_leaved() noexcept override { color = base_color; }

    void on_press(const MouseButtonEvent& button) noexcept override { Button::on_press(button); color = pressed_color; }
    void on_release(const MouseButtonEvent& /* unused */) noexcept override { color = base_color; }


    static std::tuple<Color, Color, Color> get_colors_keyframes_from_base_color(const Color& base_color) noexcept;
};




}