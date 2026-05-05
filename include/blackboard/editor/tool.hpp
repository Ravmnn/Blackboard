#pragma once

#include <flustral/updateable.hpp>
#include <flustral/drawable.hpp>
#include <flustral/activatable.hpp>




class Canvas;


class Tool : public Updateable, public Drawable
{
protected:
    Canvas& canvas_;


public:
    explicit Tool(Canvas& canvas) noexcept : canvas_(canvas) {}


    const Canvas& canvas() const noexcept { return canvas_; }
};