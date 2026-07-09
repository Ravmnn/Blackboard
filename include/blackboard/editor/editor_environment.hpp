#pragma once

#include <vector>


#include <blackboard/drawable.hpp>
#include <blackboard/mouse_button_event.hpp>




namespace bb::editor
{




class Tool;
class Editor;


class EditorEnvironment : public Updateable, public Drawable, public Activatable
{
protected:
    std::vector<Tool*> tools_;

    Tool* current_tool_ = nullptr;


public:
    Editor& editor;

    MouseButtonEvent left_button;
    MouseButtonEvent right_button;
    MouseButtonEvent middle_button;


    explicit EditorEnvironment(Editor& editor) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    Tool* current_tool() noexcept { return current_tool_; }

    void set_current_tool(Tool& tool) noexcept;


protected:
    virtual void on_left_button_press() {}
    virtual void on_left_button_release() {}
    virtual void on_left_button_click() {}
    virtual void on_left_button_drag_start() {}
    virtual void on_left_button_drag_end() {}

    virtual void on_left_button_late_press() {}
    virtual void on_left_button_late_release() {}
    virtual void on_left_button_late_click() {}
    virtual void on_left_button_late_drag_start() {}
    virtual void on_left_button_late_drag_end() {}


    virtual void on_right_button_press() {}
    virtual void on_right_button_release() {}
    virtual void on_right_button_click() {}
    virtual void on_right_button_drag_start() {}
    virtual void on_right_button_drag_end() {}

    virtual void on_right_button_late_press() {}
    virtual void on_right_button_late_release() {}
    virtual void on_right_button_late_click() {}
    virtual void on_right_button_late_drag_start() {}
    virtual void on_right_button_late_drag_end() {}


    virtual void on_middle_button_press() {}
    virtual void on_middle_button_release() {}
    virtual void on_middle_button_click() {}
    virtual void on_middle_button_drag_start() {}
    virtual void on_middle_button_drag_end() {}

    virtual void on_middle_button_late_press() {}
    virtual void on_middle_button_late_release() {}
    virtual void on_middle_button_late_click() {}
    virtual void on_middle_button_late_drag_start() {}
    virtual void on_middle_button_late_drag_end() {}


    void on_enabled() noexcept override;
    void on_disabled() noexcept override;
};




}