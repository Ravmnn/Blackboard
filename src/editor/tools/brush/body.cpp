#include <blackboard/editor/tools/brush/body.hpp>

#include <blackboard/animation/interpolation.hpp>
#include <blackboard/editor/tools/brush/brush.hpp>




using bb::editor::BrushBody;




BrushBody::BrushBody(Brush& brush) noexcept : Bubble(brush.thickness),
    brush(brush)
{}




void BrushBody::update() noexcept
{
    target = brush.position();

    Bubble::update();
}


void BrushBody::update_trail() noexcept
{
    trail.emit = !brush.active();

    Bubble::update_trail();
}


void BrushBody::update_thickness() noexcept
{
    float target_thickness = brush.current_thickness();
    target_thickness = (float)(target_thickness == 0 ? brush.thickness : target_thickness / 2.0);

    if (!brush.active())
        target_thickness = brush.thickness + IdleThicknessVariation;

    thickness = target_thickness;

    Bubble::update_thickness();
}


void BrushBody::update_color() noexcept
{
    outline_color = color = brush.color();

    Bubble::update_color();
}