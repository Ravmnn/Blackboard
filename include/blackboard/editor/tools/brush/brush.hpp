#pragma once

#include <blackboard/editor/stroke/stroke.hpp>
#include <blackboard/editor/lazy_cursor.hpp>
#include <blackboard/editor/tools/tool.hpp>
#include <blackboard/editor/tools/brush/body.hpp>




namespace bb::editor
{




class Canvas;


class Brush : public Tool
{
private:
    Stroke stroke_;

    int point_thickness_back_iterating_amount_ = 7;

    float current_thickness_ = 0;
    float min_thickness_ = 5;
    float max_thickness_ = 50;

    float thickness_max_decrease_ = 2;
    float thickness_max_increase_ = 15;


protected:
    Color color_;


public:
    float thickness;

    LazyCursor cursor;
    BrushBody body;


    friend class BrushBody;


    Brush(EditorEnvironment& environment, float thickness) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    [[nodiscard]] Vector2 position() const noexcept override;
    [[nodiscard]] Rectangle bounding_box() const noexcept override { return body.bounding_box(); }
    [[nodiscard]] const Color& color() const noexcept { return color_; }

    [[nodiscard]] const Stroke& stroke() const noexcept { return stroke_; }
    void clear_stroke() noexcept { stroke_.points.clear(); }

    [[nodiscard]] bool draw_started() const noexcept { return got_active_; }
    [[nodiscard]] bool draw_finished() const noexcept { return got_inactive_; }


private:
    void update_cursor() noexcept;
    void update_canvas_actions() noexcept;

    void add_stroke_point() noexcept;
    void modify_previous_points_thickness(float thickness) noexcept;
    [[nodiscard]] StrokePoint create_stroke_point() const noexcept;

    [[nodiscard]] float thickness_from_speed() const noexcept { return std::lerp(max_thickness(), min_thickness(), cursor.smooth_speed_fraction()); }
    [[nodiscard]] float current_thickness() const noexcept { return current_thickness_; }

    [[nodiscard]] float min_thickness() const noexcept { return std::max(min_thickness_, thickness - thickness_max_decrease_); }
    [[nodiscard]] float max_thickness() const noexcept { return std::min(max_thickness_, thickness + thickness_max_increase_); }

    [[nodiscard]] float distance_to_last_point() const noexcept { return Vector2Distance(stroke_.points.back(), cursor.position()); }
};




}