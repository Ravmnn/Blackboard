#pragma once

#include <blackboard/ui/clickable.hpp>




namespace bb::ui
{




class Scrollable : public Clickable
{
public:
    using Clickable::Clickable;


    Event<> scroll_up;
    Event<> scroll_down;


    void update() noexcept override;


    [[nodiscard]] bool scrolled() const noexcept { return scroll_value() != 0; }
    [[nodiscard]] int scroll_value() const noexcept;


protected:
    virtual void on_scroll_up() noexcept {}
    virtual void on_scroll_down() noexcept {}
};




}