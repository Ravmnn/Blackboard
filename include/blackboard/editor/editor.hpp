#pragma once

#include <blackboard/ui/ui_context.hpp>
#include <blackboard/editor/canvas.hpp>
#include <blackboard/editor/ui/color_menu.hpp>
#include <blackboard/editor/ui/color_menu_button.hpp>
#include <blackboard/rendering/window_renderer.hpp>




class Editor final : public Updateable, public Drawable
{
public:
    static constexpr Color DefaultPaletteColor = Color{ 211, 211, 211, 255 };


private:
    WindowRenderer window_renderer_;

    UIContext ui_context_;

    ColorMenu* color_menu_;

    MouseButtonEvent left_button_ = MouseButtonEvent(MOUSE_BUTTON_LEFT, canvas);
    MouseButtonEvent aux_button_ = MouseButtonEvent(MOUSE_BUTTON_RIGHT, canvas);
    MouseButtonEvent middle_button_ = MouseButtonEvent(MOUSE_BUTTON_MIDDLE, canvas);

    bool draw_statistics_ = false;


public:
    Canvas canvas;


    Editor() noexcept;


    void update() noexcept override;
    void draw() noexcept override;


private:
    void update_mouse_buttons() noexcept;
    void update_keybindings() noexcept;

    void draw_statistics() noexcept;
};