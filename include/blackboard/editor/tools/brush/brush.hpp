#pragma once

#include <blackboard/editor/stroke.hpp>
#include <blackboard/editor/lazy_cursor.hpp>
#include <blackboard/editor/tools/brush/body.hpp>
#include <blackboard/editor/tools/tool.hpp>




class Canvas;


class Brush : public Tool
{
private:
    Stroke stroke_;

    bool was_active_ = false;
    bool got_inactive_ = false;
    bool got_active_ = false;

    float max_velocity_ = 70;

    float smooth_velocity_ = 0;
    float velocity_smoothing_ = 0.05;
    float max_smooth_velocity_ = 25;
    int point_thickness_back_iterating_amount_ = 6;

    float current_thickness_;
    float min_thickness_ = 5;
    float max_thickness_ = 50;

    float thickness_max_decrease_ = 2;
    float thickness_max_increase_ = 15;


public:
    LazyCursor cursor;
    BrushBody body;

    Color color;
    float thickness;


    friend class BrushBody;


    Brush(Canvas& canvas, const Color& color, const float thickness) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    const Stroke& stroke() const noexcept { return stroke_; }
    void clear_stroke() noexcept { stroke_.points.clear(); }

    bool draw_started() const noexcept { return got_active_; }
    bool draw_finished() const noexcept { return got_inactive_; }


private:
    void update_cursor() noexcept;
    void update_canvas_actions() noexcept;
    void update_smooth_velocity() noexcept;
    void update_drawing_state() noexcept;

    void add_stroke_point() noexcept;
    void modify_previous_points_thickness(const float thickness) noexcept;

    float current_velocity() const noexcept;
    float thickness_from_velocity() const noexcept;
    float current_thickness() const noexcept { return current_thickness_; }

    float min_thickness() const noexcept { return std::max(min_thickness_, thickness - thickness_max_decrease_); }
    float max_thickness() const noexcept { return std::min(max_thickness_, thickness + thickness_max_increase_); }

    bool is_too_slow() const noexcept;

    float distance_to_last_point() const noexcept { return Vector2Distance(stroke_.points.back(), cursor.position()); }
};