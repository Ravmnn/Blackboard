#pragma once

#include <blackboard/ui/context.hpp>
#include <blackboard/editor/canvas.hpp>
#include <blackboard/editor/tools/brush/brush.hpp>
#include <blackboard/editor/tools/eraser/eraser.hpp>
#include <blackboard/editor/ui/color_menu.hpp>
#include <blackboard/editor/ui/color_menu_button.hpp>
#include <blackboard/rendering/window_renderer.hpp>
#include <blackboard/animation/interpolation.hpp>




namespace bb::editor
{




class Editor final : public Updateable, public Drawable
{
public:
    static constexpr Color DefaultPaletteColor = Color{ 211, 211, 211, 255 };


private:
    rendering::WindowRenderer window_renderer_;

    ui::Context ui_context_;

    ColorMenu* color_menu_;

    MouseButtonEvent left_button_ = MouseButtonEvent(MOUSE_BUTTON_LEFT, canvas);
    MouseButtonEvent aux_button_ = MouseButtonEvent(MOUSE_BUTTON_RIGHT, canvas);
    MouseButtonEvent middle_button_ = MouseButtonEvent(MOUSE_BUTTON_MIDDLE, canvas);

    bool draw_statistics_ = false;


public:
    Canvas canvas;

    Brush brush;
    Eraser eraser;

    Tool* current_tool = nullptr;


    Editor() noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    void set_current_tool(Tool& tool) noexcept { current_tool = &tool; }

    void alternate_tool() noexcept { current_tool = current_tool == &brush ? (Tool*)&eraser : (Tool*)&brush; }


private:
    void update_mouse_buttons() noexcept;
    void update_keybindings() noexcept;

    void draw_canvas() noexcept;
    void draw_canvas_content() noexcept;
    void draw_statistics() const noexcept;
};




}