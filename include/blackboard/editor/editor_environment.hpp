#pragma once

#include <vector>

#include <blackboard/mouse_button_event.hpp>
#include <blackboard/editor/tools/tool.hpp>




namespace bb::editor
{




class EditorEnvironment : public Updateable, public Drawable
{
protected:
    std::vector<Tool*> tools_;

    MouseButtonEvent left_button_;
    MouseButtonEvent right_button_;
    MouseButtonEvent middle_button_;


public:
    Editor& editor;


    explicit EditorEnvironment(Editor& editor) noexcept;


    void update() noexcept override;
    void draw() noexcept override {}
};




}