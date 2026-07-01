#pragma once

#include <vector>

#include <blackboard/mouse_button_event.hpp>
#include <blackboard/editor/tools/tool.hpp>




namespace bb::editor
{




class EditorEnvironment : public Updateable, public Drawable, public Activatable
{
protected:
    std::vector<Tool*> tools_;


public:
    Editor& editor;

    MouseButtonEvent left_button;
    MouseButtonEvent right_button;
    MouseButtonEvent middle_button;

    Tool* current_tool = nullptr;


    explicit EditorEnvironment(Editor& editor) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    void enable() noexcept override;
};




}