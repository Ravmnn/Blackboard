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
    bool got_inactive_ = false;
    bool got_active_ = false;


public:
    Event<> changed_in;
    Event<> changed_out;


    EditorEnvironment& environment;


    explicit Tool(EditorEnvironment& environment) noexcept;


    void update() noexcept override;


    Editor& editor() noexcept;
    [[nodiscard]] const Editor& editor() const noexcept;

    [[nodiscard]] virtual Vector2 position() const noexcept = 0;

    [[nodiscard]] bool was_active() const noexcept { return was_active_; }
    [[nodiscard]] bool got_active() const noexcept { return got_active_; }
    [[nodiscard]] bool got_inactive() const noexcept { return got_inactive_; }


protected:
    void update_active_state() noexcept;


    virtual void on_changed_in() {}
    virtual void on_changed_out() {}
};




}