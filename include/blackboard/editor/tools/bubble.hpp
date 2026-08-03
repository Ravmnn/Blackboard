#pragma once

#include <blackboard/bounds.hpp>
#include <blackboard/animation/spring.hpp>
#include <blackboard/animation/interpolation.hpp>
#include <blackboard/editor/stroke/trail.hpp>




namespace bb::editor
{




class Bubble : public Updateable, public Drawable, public Bounds
{
protected:
    static constexpr float StretchSpeedFactor = 1.0 / 3.0;
    static constexpr uint32_t EllipseResolution = 32;
    static constexpr uint32_t EllipseOutlineResolution = 16;


    float last_rotation_ = 0;
    Vector2 last_position_ = {};
    Vector2 position_ = {};


public:
    const Camera2D& camera;

    Vector2 target;

    animation::Spring<float> half_thickness;
    animation::Spring<float> stretch;
    animation::ExponentialInterpolation<float> outline_thickness;
    animation::ExponentialInterpolation<Color> color;
    animation::ExponentialInterpolation<Color> outline_color;

    Trail trail;
    bool sync_trail_color = true;


    Bubble(const Camera2D& camera, float thickness) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    [[nodiscard]] Vector2 position() const noexcept { return position_; }
    [[nodiscard]] Vector2 velocity() const noexcept { return position_ - last_position_; }

    [[nodiscard]] Rectangle bounding_box() const noexcept override {
        return { position().x - half_thickness, position().y - half_thickness, half_thickness * 2, half_thickness * 2 };
    }


protected:
    virtual void update_trail() noexcept;
    virtual void update_thickness() noexcept;
    virtual void update_stretch() noexcept;
    virtual void update_color() noexcept;

    [[nodiscard]] StrokePoint create_stroke_point() const noexcept;

    void draw_trail() noexcept;
    void draw_body() noexcept;
    void draw_rotated_stretched_ellipse(float rotation) noexcept;

    void draw_ellipse() noexcept;
    void draw_ellipse_inner() noexcept;
    void draw_ellipse_outline() noexcept;
};




}