#include <blackboard/editor/brush_body.hpp>

#include <blackboard/interpolation.hpp>
#include <blackboard/editor/brush.hpp>




BrushBody::BrushBody(Brush& brush) noexcept :
    thickness_(brush.thickness, brush.thickness, 0.15, 40),
    stretch_(0, 0, 0.01, 30),

    color_interpolation_(WHITE, 0.01, 2),

    brush(brush)
{
    stretch_.max = 60;
}




void BrushBody::update() noexcept
{
    update_thickness();
    update_stretch();
    update_color();
}


void BrushBody::update_thickness() noexcept
{
    float target_thickness = brush.thickness_from_velocity();
    target_thickness = (target_thickness == 0 ? brush.thickness : target_thickness / 2.0);

    if (!brush.should_draw())
        target_thickness = brush.thickness + IdleThicknessVariation;

    thickness_ = target_thickness;
    thickness_.update();
}


void BrushBody::update_stretch() noexcept
{
    const float speed = Vector2Length(brush.cursor.velocity());
    const float stretch = speed * StretchSpeedFactor;

    stretch_ = stretch;
    stretch_.update();
}


void BrushBody::update_color() noexcept
{
    target_color_ = brush.color;

    if (brush.should_draw())
        target_color_.a = DrawingOpacity;
    else
        target_color_.a = NormalOpacity;

    color_interpolation_.set_target_and_update(target_color_);
}




void BrushBody::draw() noexcept
{
    // TODO: trail

    const Vector2 position = brush.cursor.position();
    const float radius = thickness_;

    const Vector2 velocity = brush.cursor.velocity();
    const Vector2 direction = Vector2Normalize(velocity);
    const float direction_length = Vector2Length(velocity);

    float rotation = atan2f(direction.y, direction.x) * RAD2DEG;

    if (direction_length <= 1)
        rotation = last_rotation_;

    draw_rotated_stretched_ellipse(position, radius, stretch_, rotation);

    last_rotation_ = rotation;
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