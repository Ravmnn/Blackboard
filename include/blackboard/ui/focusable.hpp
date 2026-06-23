#pragma once

#include <blackboard/event.hpp>




namespace bb::ui
{




class Focusable
{
protected:
    bool is_focused_ = false;


public:
    Event<> focused;
    Event<> unfocused;


    Focusable() noexcept;


    [[nodiscard]] bool is_focused() const noexcept { return is_focused_; }

    void focus() noexcept;
    void unfocus() noexcept;
    void toggle() noexcept;


protected:
    virtual void on_focus() noexcept {}
    virtual void on_unfocus() noexcept {}
};




}