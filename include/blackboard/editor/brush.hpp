#pragma once

#include <vector>
#include <optional>

#include <blackboard/editor/stroke.hpp>
#include <blackboard/editor/brush_cursor.hpp>




class Brush : public Updateable
{
private:
    Stroke stroke_;


    bool should_draw_ = false;
    bool draw_finished_ = false;
    bool draw_started_ = false;

    float smooth_velocity_ = 0;
    float velocity_smoothing_ = 0.05;
    float max_velocity_ = 1000;
    int point_thickness_back_iterating_amount_ = 4;


public:
    BrushCursor brush_cursor;

    Color color;
    float thickness;


    Brush(const Color& color, const float thickness) noexcept
        : stroke_({}, color), brush_cursor(*this, 2.5), color(color), thickness(thickness) {}


    void update() noexcept override;


    const Stroke& stroke() const noexcept { return stroke_; }
    void clear_stroke() noexcept { stroke_.points.clear(); }

    bool should_draw() const noexcept { return should_draw_; }
    bool draw_started() const noexcept { return draw_started_; }
    bool draw_finished() const noexcept { return draw_finished_; }


private:
    void update_smooth_velocity() noexcept;
    void update_drawing_state() noexcept;
    void draw_current_segment() noexcept;
    void modify_previous_points_thickness(const float thickness) noexcept;

    float current_velocity() const noexcept;
    float thickness_from_velocity() const noexcept;

    float min_thickness() const noexcept { return std::max(5.0f, thickness - 3); }
    float max_thickness() const noexcept { return std::min(50.0f, thickness + 10); }

    bool is_too_slow() const noexcept;
};