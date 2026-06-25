#pragma once

#include <raylib.h>

#include <blackboard/updateable.hpp>
#include <blackboard/drawable.hpp>
#include <blackboard/activatable.hpp>




namespace bb::editor
{




class Editor;
class Palette;


class Tool : public Updateable, public Drawable, public Activatable
{
protected:
    Editor& editor_;

    bool was_active_ = false;
    bool got_inactive_ = false;
    bool got_active_ = false;


public:
    explicit Tool(Editor& editor) noexcept : editor_(editor) {}


    void update() noexcept override;


    [[nodiscard]] const Editor& editor() const noexcept { return editor_; }

    [[nodiscard]] virtual Vector2 position() const noexcept = 0;

    [[nodiscard]] bool was_active() const noexcept { return was_active_; }
    [[nodiscard]] bool got_active() const noexcept { return got_active_; }
    [[nodiscard]] bool got_inactive() const noexcept { return got_inactive_; }


protected:
    void update_active_state() noexcept;
};




}