#include <blackboard/editor/tools/eraser/body.hpp>

#include <blackboard/editor/editor.hpp>




using bb::editor::EraserBody;




EraserBody::EraserBody(Eraser& eraser) noexcept :
    Bubble(eraser.editor().canvas.raylib_camera(), BaseThickness),

    eraser(eraser)
{
    outline_thickness.set_value_immediately(1.0);

    trail.decay = 5;
    sync_trail_color = false;

    eraser.changed_in.subscribe([this]() noexcept { on_eraser_changed_in(); }, "editor::EraserBody::eraser_changed_in_callback");
}




void EraserBody::update() noexcept
{
    target = eraser.position();

    Bubble::update();
}


void EraserBody::update_trail() noexcept
{
    trail.set_color(eraser.environment.editor.palette.current_color());
    trail.set_alpha(150);

    Bubble::update_trail();
}


void EraserBody::update_thickness() noexcept
{
    half_thickness = BaseThickness;

    if (!eraser.active())
        half_thickness = BaseThickness + IdleThicknessVariation;

    Bubble::update_thickness();
}


void EraserBody::update_color() noexcept
{
    Color color = eraser.environment.editor.palette.current_color();
    color.a = 215;
    outline_color = color;

    color.a = 140;
    this->color = color;

    Bubble::update_color();
}




void EraserBody::on_eraser_changed_in() noexcept
{
    last_position_ = position_ = eraser.position();
    last_rotation_ = 0;
    stretch.set_value_immediately(0);

    trail.points.clear();
}