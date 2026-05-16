#pragma once

#include <blackboard/editor/canvas.hpp>
#include <blackboard/editor/ui/radial_menu.hpp>
#include <blackboard/editor/ui/color_menu_button.hpp>
#include <blackboard/rendering/window_renderer.hpp>




class Editor final : public Updateable, public Drawable
{
private:
    WindowRenderer window_renderer_;

    RadialMenu color_menu_;

    MouseButtonEvent left_button_ = MouseButtonEvent(MOUSE_BUTTON_LEFT, canvas);
    MouseButtonEvent aux_button_ = MouseButtonEvent(MOUSE_BUTTON_RIGHT, canvas);

    bool draw_statistics_ = false;


public:
    Canvas canvas;


    Editor() noexcept;


    void update() noexcept override;
    void draw() noexcept override;


private:
    void update_mouse_buttons() noexcept;
    void update_keybindings() noexcept;

    void draw_canvas() noexcept;
    void draw_statistics() noexcept;
};