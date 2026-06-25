#pragma once

#include <blackboard/editor/tools/tool.hpp>
#include <blackboard/editor/tools/eraser/body.hpp>




namespace bb::editor
{




class Eraser : public Tool
{
private:
    Vector2 last_position_ = {};

    std::vector<const StrokeMesh*> strokes_to_remove_;


public:
    using Tool::Tool;


    size_t iteration_amount = 8;
    size_t iteration_amount_test_ = 1;
    bool dynamic_iteration_amount = true;

    EraserBody body;


    explicit Eraser(Editor& editor) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    [[nodiscard]] Vector2 position() const noexcept override;


private:
    [[nodiscard]] float distance_delta() const noexcept { return Vector2Length(position() - last_position_); }

    [[nodiscard]] size_t get_iteration_amount() const noexcept {
        return dynamic_iteration_amount ? std::max((size_t)((float)iteration_amount * distance_delta() / 50), iteration_amount) : iteration_amount;
    }

    void update_strokes_to_remove() noexcept;
    StrokeMesh* get_canvas_stroke_at_point(const Vector2& point) noexcept;

    void add_stroke_to_remove_queue(StrokeMesh& stroke) noexcept;

    void remove_strokes_from_remove_queue() noexcept;
    void remove_stroke(const StrokeMesh& stroke) noexcept;
};


}