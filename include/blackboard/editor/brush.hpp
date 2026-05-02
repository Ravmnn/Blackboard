#pragma once

#include <vector>
#include <optional>

#include <flustral/updateable.hpp>

#include <blackboard/editor/stroke.hpp>




class Brush : public Updateable
{
private:
    Stroke stroke_;

    bool should_draw_ = false;
    bool draw_finished_ = false;
    bool draw_started_ = false;


public:
    Color color;
    float thickness;


    Brush(const Color& color, const float thickness) noexcept
        : stroke_({}, color), color(color), thickness(thickness) {}


    void update() noexcept override;


    const Stroke& stroke() const noexcept { return stroke_; }
    void clear_stroke() noexcept { stroke_.points.clear(); }

    bool should_draw() const noexcept { return should_draw_; }
    bool draw_started() const noexcept { return draw_started_; }
    bool draw_finished() const noexcept { return draw_finished_; }


private:
    void update_drawing_state() noexcept;
    void draw_current_segment() noexcept;
};