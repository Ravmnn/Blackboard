#pragma once

#include <blackboard/ui/context.hpp>
#include <blackboard/rendering/effects/effect.hpp>
#include <blackboard/editor/canvas.hpp>
#include <blackboard/editor/tools/brush/brush.hpp>
#include <blackboard/editor/tools/eraser/eraser.hpp>
#include <blackboard/editor/ui/color_menu.hpp>
#include <blackboard/editor/ui/color_menu_button.hpp>




namespace bb::editor
{




class Editor final : public ui::Component, public ui::Clickable, public ui::Focusable
{
private:
    static constexpr Color DefaultPaletteColor = { 211, 211, 211, 255 };
    static constexpr Color DefaultBackgroundColor = { 18, 18, 18, 255 };


    ColorMenu* color_menu_;

    MouseButtonEvent left_button_ = MouseButtonEvent(MOUSE_BUTTON_LEFT, canvas);
    MouseButtonEvent right_button_ = MouseButtonEvent(MOUSE_BUTTON_RIGHT, canvas);
    MouseButtonEvent middle_button_ = MouseButtonEvent(MOUSE_BUTTON_MIDDLE, canvas);

    bool draw_statistics_ = false;


public:
    // TODO: vanish animation when switching tool (similar to FL)


    Canvas canvas;
    Palette palette;
    bool dynamic_background_color = true;

    Brush brush;
    Eraser eraser;

    Tool* current_tool = nullptr;


    Editor(ui::Context& ui_context) noexcept;


    void update() noexcept override;


    void set_current_tool(Tool& tool) noexcept { current_tool = &tool; }

    void alternate_tool() noexcept { current_tool = current_tool == &brush ? (Tool*)&eraser : (Tool*)&brush; }


    [[nodiscard]] Rectangle relative_bounding_box() const noexcept override { return {}; }

    [[nodiscard]] bool is_point_over(const Vector2& /* unused */) const noexcept override { return true; }


private:
    void initialize_mouse_button_events() noexcept;

    void update_focus() noexcept;
    void update_tools() noexcept;
    void update_keybindings() noexcept;
    void update_canvas_background() noexcept;

    void draw_self() noexcept override;
    void draw_canvas() noexcept;
    void draw_canvas_content() noexcept;
    void draw_statistics() const noexcept;
};




}