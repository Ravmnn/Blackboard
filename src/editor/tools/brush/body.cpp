#include <blackboard/editor/tools/brush/body.hpp>

#include <blackboard/editor/editor.hpp>
#include <blackboard/editor/tools/brush/brush.hpp>




using bb::editor::BrushBody;




BrushBody::BrushBody(Brush& brush) noexcept : Bubble(brush.thickness),
    brush(brush)
{
    brush.editor.environment_changed.subscribe([this]() noexcept { on_editor_environment_changed(); }, "editor::BrushBody::editor_environment_changed_event_callback");
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

    thickness = target_thickness;

    Bubble::update_thickness();
}


void BrushBody::update_color() noexcept
{
    outline_color = color = brush.color();

    Bubble::update_color();
}




void BrushBody::on_editor_environment_changed() noexcept
{
    last_position_ = position_ = brush.position();
    last_rotation_ = 0;
    stretch.set_value_immediately(0);

    trail.points.clear();
}