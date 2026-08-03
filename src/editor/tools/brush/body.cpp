#include <blackboard/editor/tools/brush/body.hpp>

#include <blackboard/editor/editor.hpp>
#include <blackboard/editor/editor_environment.hpp>
#include <blackboard/editor/tools/brush/brush.hpp>




using bb::editor::BrushBody;




BrushBody::BrushBody(Brush& brush) noexcept :
    Bubble(brush.editor().canvas.raylib_camera(), brush.thickness),

    brush(brush)
{
    brush.changed_in.subscribe([this]() noexcept { on_brush_changed_in(); }, "editor::BrushBody::brush_changed_in_callback");
}




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

    half_thickness = target_thickness;

    Bubble::update_thickness();
}


void BrushBody::update_color() noexcept
{
    outline_color = color = brush.color();

    Bubble::update_color();
}




void BrushBody::on_brush_changed_in() noexcept
{
    last_position_ = position_ = brush.position();
    last_rotation_ = 0;
    stretch.set_value_immediately(0);

    trail.points.clear();
}