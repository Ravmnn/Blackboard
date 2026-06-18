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


public:
    explicit Tool(Canvas& canvas) noexcept : canvas_(canvas) {}


    [[nodiscard]] const Canvas& canvas() const noexcept { return canvas_; }

    [[nodiscard]] virtual Vector2 position() const noexcept = 0;
};




}