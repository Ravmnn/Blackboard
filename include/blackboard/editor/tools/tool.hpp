#pragma once

#include <blackboard/updateable.hpp>
#include <blackboard/drawable.hpp>
#include <blackboard/activatable.hpp>
#include <blackboard/bounds.hpp>




namespace bb::editor
{




class Editor;
class EditorEnvironment;


class Tool : public Updateable, public Drawable, public Activatable, public Bounds
{
protected:
    bool was_active_ = false;


public:
    Event<> changed_in;
    Event<> changed_out;

    Event<> got_active;
    Event<> got_inactive;


    EditorEnvironment& environment;


    explicit Tool(EditorEnvironment& environment) noexcept;


    void update() noexcept override;


    Editor& editor() noexcept;
    [[nodiscard]] const Editor& editor() const noexcept;

    [[nodiscard]] virtual Vector2 position() const noexcept = 0;

    [[nodiscard]] bool was_active() const noexcept { return was_active_; }


protected:
    virtual void update_when_active() noexcept {}

    void update_active_state() noexcept;


    virtual void on_got_active() noexcept {}
    virtual void on_got_inactive() noexcept {}

    virtual void on_changed_in() noexcept {}
    virtual void on_changed_out() noexcept {}
};




}