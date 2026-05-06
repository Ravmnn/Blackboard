#pragma once

#include <vector>
#include <optional>

#include <flustral/spring.hpp>

#include <blackboard/editor/stroke.hpp>
#include <blackboard/editor/brush_cursor.hpp>
#include <blackboard/editor/brush_body.hpp>
#include <blackboard/editor/tool.hpp>




class Canvas;


class Brush : public Tool
{
private:
    Stroke stroke_;

    bool should_draw_ = false;
    bool draw_finished_ = false;
    bool draw_started_ = false;

    float max_velocity_ = 70;

    float smooth_velocity_ = 0;
    float velocity_smoothing_ = 0.05;
    float max_smooth_velocity_ = 25;
    int point_thickness_back_iterating_amount_ = 8;

    float min_thickness_ = 5;
    float max_thickness_ = 50;

    float thickness_max_decrease_ = 2;
    float thickness_max_increase_ = 15;


public:
    BrushCursor cursor;
    BrushBody body;

    Color color;
    float thickness;


    friend class BrushBody;


    Brush(Canvas& canvas, const Color& color, const float thickness) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    const Stroke& stroke() const noexcept { return stroke_; }
    void clear_stroke() noexcept { stroke_.points.clear(); }

    bool should_draw() const noexcept { return should_draw_; }
    bool draw_started() const noexcept { return draw_started_; }
    bool draw_finished() const noexcept { return draw_finished_; }


private:
    void update_canvas_actions() noexcept;

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