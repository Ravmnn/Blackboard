#pragma once

#include <blackboard/editor/editor_environment.hpp>
#include <blackboard/editor/tools/brush/brush.hpp>
#include <blackboard/editor/tools/eraser/eraser.hpp>




namespace bb::editor
{




class EditorDrawingEnvironment final : public EditorEnvironment
{
public:
    Brush brush;
    Eraser eraser;


    explicit EditorDrawingEnvironment(Editor& editor) noexcept;


    void alternate_brush_and_eraser() noexcept;


private:
    void enter_selection_mode(bool enable_selection = true) noexcept;


    void on_enabled() noexcept override;


    void on_left_button_press() noexcept override;
    void on_left_button_release() noexcept override;

    void on_right_button_click() noexcept override;
    void on_right_button_late_click() noexcept override;
    void on_right_button_drag_start() noexcept override;

    void on_middle_button_click() noexcept override;
};




}