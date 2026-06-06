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

    int point_thickness_back_iterating_amount_ = 7;

    float current_thickness_;
    float min_thickness_ = 5;
    float max_thickness_ = 50;

    float thickness_max_decrease_ = 2;
    float thickness_max_increase_ = 15;


protected:
    Color color_;


public:
    LazyCursor cursor;
    BrushBody body;

    float thickness;


    friend class BrushBody;


    Brush(Canvas& canvas, const float thickness) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    const Color& color() const noexcept { return color_; }

    const Stroke& stroke() const noexcept { return stroke_; }
    void clear_stroke() noexcept { stroke_.points.clear(); }

    bool draw_started() const noexcept { return got_active_; }
    bool draw_finished() const noexcept { return got_inactive_; }


private:
    void update_cursor() noexcept;
    void update_canvas_actions() noexcept;
    void update_drawing_state() noexcept;

    void add_stroke_point() noexcept;
    void modify_previous_points_thickness(const float thickness) noexcept;

    float thickness_from_speed() const noexcept { return std::lerp(max_thickness(), min_thickness(), cursor.smooth_speed_fraction()); }
    float current_thickness() const noexcept { return current_thickness_; }

    float min_thickness() const noexcept { return std::max(min_thickness_, thickness - thickness_max_decrease_); }
    float max_thickness() const noexcept { return std::min(max_thickness_, thickness + thickness_max_increase_); }

    float distance_to_last_point() const noexcept { return Vector2Distance(stroke_.points.back(), cursor.position()); }
};