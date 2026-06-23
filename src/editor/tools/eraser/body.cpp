#include <blackboard/editor/tools/eraser/body.hpp>

#include <blackboard/editor/tools/eraser/eraser.hpp>
#include <blackboard/editor/canvas.hpp>




using bb::editor::EraserBody;




EraserBody::EraserBody(const Eraser& eraser) noexcept : Bubble(BaseThickness),
    eraser(eraser)
{
    outline_thickness.set_value_immediately(1.0);

    trail.decay = 5;
    sync_trail_color = false;
}




void EraserBody::update() noexcept
{
    target = eraser.position();
    thickness = BaseThickness;

    if (eraser.active())
        thickness = BaseThickness - ThicknessVariationWhenActive;

    Bubble::update();
}


void EraserBody::update_trail() noexcept
{
    trail.color = eraser.canvas().palette.current_color();
    trail.color.a = 150;

    Bubble::update_trail();
}


void EraserBody::update_color() noexcept
{
    Color color = eraser.canvas().palette.current_color();
    color.a = 215;
    outline_color = color;

    color.a = 70;
    this->color = color;

    Bubble::update_color();
}