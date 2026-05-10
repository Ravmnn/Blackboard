#pragma once

#include <blackboard/updateable.hpp>
#include <blackboard/drawable.hpp>
#include <blackboard/activatable.hpp>




class Canvas;


class Tool : public Updateable, public Drawable, public Activatable
{
protected:
    Canvas& canvas_;


public:
    explicit Tool(Canvas& canvas) noexcept : canvas_(canvas) {}


    const Canvas& canvas() const noexcept { return canvas_; }
};