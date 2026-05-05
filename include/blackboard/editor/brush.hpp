#pragma once

#include <vector>
#include <optional>

#include <blackboard/editor/stroke.hpp>
#include <blackboard/editor/brush_cursor.hpp>




class Canvas;


class Brush : public Updateable
{
private:
    Stroke stroke_;


    bool should_draw_ = false;
    bool draw_finished_ = false;
    bool draw_started_ = false;

    float smooth_velocity_ = 0;
    float velocity_smoothing_ = 0.07;
    float max_velocity_ = 30;
    int point_thickness_back_iterating_amount_ = 5;

    float min_thickness_ = 5;
    float max_thickness_ = 50;

    float thickness_max_decrease_ = 2;
    float thickness_max_increase_ = 15;


public:
    Canvas& canvas;
    BrushCursor brush_cursor;

    Color color;
    float thickness;


    Brush(Canvas& canvas, const Color& color, const float thickness) noexcept
        : stroke_({}, color), canvas(canvas), brush_cursor(*this, 2), color(color), thickness(thickness) {}


    void update() noexcept override;


    const Stroke& stroke() const noexcept { return stroke_; }
    void clear_stroke() noexcept { stroke_.points.clear(); }

    bool should_draw() const noexcept { return should_draw_; }
    bool draw_started() const noexcept { return draw_started_; }
    bool draw_finished() const noexcept { return draw_finished_; }


private:
    void update_smooth_velocity() noexcept;
    void update_drawing_state() noexcept;
    void add_stroke_point() noexcept;
    void modify_previous_points_thickness(const float thickness) noexcept;

    float current_velocity() const noexcept;
    float thickness_from_velocity() const noexcept;

    float min_thickness() const noexcept { return std::max(min_thickness_, thickness - thickness_max_decrease_); }
    float max_thickness() const noexcept { return std::min(max_thickness_, thickness + thickness_max_increase_); }

    bool is_too_slow() const noexcept;
};