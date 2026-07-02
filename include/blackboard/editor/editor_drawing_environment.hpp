#pragma once

#include <blackboard/editor/editor_environment.hpp>
#include <blackboard/editor/tools/brush/brush.hpp>
#include <blackboard/editor/tools/eraser/eraser.hpp>




namespace bb::editor
{




class EditorDrawingEnvironment : public EditorEnvironment
{
public:
    Brush brush;
    Eraser eraser;


    explicit EditorDrawingEnvironment(Editor& editor) noexcept;


    void alternate_brush_and_eraser() noexcept;


protected:
    void on_enabled() noexcept override;
};




}