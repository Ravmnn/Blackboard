#include <blackboard/editor/tools/bubble.hpp>

#include <rlgl.h>

#include <blackboard/draw.hpp>
#include <blackboard/rendering/stencil.hpp>




using bb::editor::Bubble,
    bb::rendering::Stencil;




Bubble::Bubble(const float thickness) noexcept :
    thickness(thickness, 0.15, 40),
    stretch(0, 0.01, 30),
    outline_thickness(2, 5),

    color(WHITE, 5),
    outline_color(WHITE, 5),

    trail(StrokePoint({}, 0), 10)
{
    stretch.max = 45;
}




void Bubble::update() noexcept
{
    last_position_ = position_;
    position_ = target;

    update_trail();
    update_thickness();
    update_stretch();
    update_color();
}


void Bubble::update_trail() noexcept
{
    if (sync_trail_color)
        trail.color = color;

    trail.origin = StrokePoint(position_, thickness * 2);
    trail.update();
}


void Bubble::update_thickness() noexcept
{
    thickness.update();
}


void Bubble::update_stretch() noexcept
{
    const float speed = Vector2Length(velocity());
    const float new_stretch = speed * StretchSpeedFactor;

    stretch = new_stretch;
    stretch.update();
}


void Bubble::update_color() noexcept
{
    color.update();
    outline_color.update();
}




void Bubble::draw() noexcept
{
    draw_body();
    draw_trail();
}


void Bubble::draw_trail() noexcept
{
    Stencil::enable();
        Stencil::begin_mask(GL_NOTEQUAL, 1);
        trail.draw();
    Stencil::disable();
}


void Bubble::draw_body() noexcept
{
    const Vector2 velocity = this->velocity();
    const Vector2 direction = Vector2Normalize(velocity);
    const float direction_length = Vector2Length(velocity);

    const float rotation = direction_length > 1 ? atan2f(direction.y, direction.x) * RAD2DEG : last_rotation_;
    last_rotation_ = rotation;

    draw_rotated_stretched_ellipse(rotation);
}


void Bubble::draw_rotated_stretched_ellipse(const float rotation) noexcept
{
    rlPushMatrix();
        rlTranslatef(position_.x, position_.y, 0.0f);
        rlRotatef(rotation, 0.0f, 0.0f, 1.0f);
        rlTranslatef(-position_.x, -position_.y, 0.0f);

        draw_ellipse();
    rlPopMatrix();
}


void Bubble::draw_ellipse() noexcept
{
    Stencil::enable();
        Stencil::begin_write(GL_ALWAYS, 1, GL_REPLACE);
        draw_ellipse_inner();
        draw_ellipse_outline();
    Stencil::disable();
}


void Bubble::draw_ellipse_inner() noexcept
{
    Draw::stretched_ellipse(position_, thickness, stretch, color, EllipseResolution);
}


void Bubble::draw_ellipse_outline() noexcept
{
    Draw::stretched_ellipse_outline(position_, thickness, stretch, outline_thickness, outline_color, EllipseResolution);
}