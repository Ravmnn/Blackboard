#include <blackboard/editor/tools/brush/body.hpp>

#include <blackboard/animation/interpolation.hpp>
#include <blackboard/editor/tools/brush/brush.hpp>
#include <blackboard/editor/canvas.hpp>




BrushBody::BrushBody(Brush& brush) noexcept :
    trail_(StrokePoint({}, 0), 10),

    thickness_(brush.thickness, brush.thickness, 0.15, 40),
    stretch_(0, 0, 0.01, 30),

    color_interpolation_(WHITE, 5),

    brush(brush)
{
    stretch_.max = 60;
}




void BrushBody::update() noexcept
{
    position_ = brush.cursor.position();

    update_trail();
    update_thickness();
    update_stretch();
    update_color();
}


void BrushBody::update_trail() noexcept
{
    trail_.emit = !brush.active();
    trail_.color = color_interpolation_;
    trail_.origin = StrokePoint(position_, thickness_ * 2);
    trail_.update();
}


void BrushBody::update_thickness() noexcept
{
    float target_thickness = brush.current_thickness();
    target_thickness = (target_thickness == 0 ? brush.thickness : target_thickness / 2.0);

    if (!brush.active())
        target_thickness = brush.thickness + IdleThicknessVariation;

    thickness_ = target_thickness;
    thickness_.update();
}


void BrushBody::update_stretch() noexcept
{
    const float speed = Vector2Length(brush.canvas().mouse_delta());
    const float stretch = speed * StretchSpeedFactor;

    stretch_ = stretch;
    stretch_.update();
}


void BrushBody::update_color() noexcept
{
    color_interpolation_.set_target_and_update(brush.color());
}




void BrushBody::draw() noexcept
{
    trail_.draw();
    draw_body();
}


void BrushBody::draw_body() noexcept
{
    const float radius = thickness_;

    const Vector2 velocity = brush.canvas().mouse_delta();
    const Vector2 direction = Vector2Normalize(velocity);
    const float direction_length = Vector2Length(velocity);

    const float rotation = direction_length > 1 ? atan2f(direction.y, direction.x) * RAD2DEG : last_rotation_;
    last_rotation_ = rotation;

    draw_rotated_stretched_ellipse(position_, radius, stretch_, rotation);
}


void BrushBody::draw_rotated_stretched_ellipse(const Vector2& position, const float radius, const float stretch, const float rotation) noexcept
{
    rlPushMatrix();
        rlTranslatef(position.x, position.y, 0.0f);
        rlRotatef(rotation, 0.0f, 0.0f, 1.0f);
        rlTranslatef(-position.x, -position.y, 0.0f);

        DrawEllipse(
            position.x, position.y,
            radius + stretch, radius,
            color_interpolation_
        );
    rlPopMatrix();
}