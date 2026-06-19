#pragma once

#include <raylib.h>

#include <blackboard/updateable.hpp>
#include <blackboard/drawable.hpp>
#include <blackboard/activatable.hpp>




namespace bb::editor
{




class Canvas;
class Palette;


class Tool : public Updateable, public Drawable, public Activatable
{
protected:
    Canvas& canvas_;

    bool was_active_ = false;
    bool got_inactive_ = false;
    bool got_active_ = false;


public:
    explicit Tool(Canvas& canvas) noexcept : canvas_(canvas) {}


    void update() noexcept override;


    [[nodiscard]] const Canvas& canvas() const noexcept { return canvas_; }

    [[nodiscard]] virtual Vector2 position() const noexcept = 0;

    [[nodiscard]] bool was_active() const noexcept { return was_active_; }
    [[nodiscard]] bool got_active() const noexcept { return got_active_; }
    [[nodiscard]] bool got_inactive() const noexcept { return got_inactive_; }


protected:
    void update_active_state() noexcept;
};




}