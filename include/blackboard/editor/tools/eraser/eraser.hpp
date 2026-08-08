#pragma once

#include <blackboard/editor/tools/tool.hpp>
#include <blackboard/editor/tools/eraser/body.hpp>




namespace bb::math { class Segment; }


namespace bb::editor
{




class Eraser : public Tool
{
private:
    Vector2 last_position_ = {};

    std::vector<const StrokeMesh*> strokes_to_remove_;


public:
    friend class EraserBody;

    EraserBody body;


    explicit Eraser(EditorEnvironment& environment) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    [[nodiscard]] Vector2 position() const noexcept override;
    [[nodiscard]] Rectangle bounding_box() const noexcept override { return body.bounding_box(); }


private:
    [[nodiscard]] float distance_delta() const noexcept { return Vector2Length(position() - last_position_); }

    void update_strokes_to_remove() noexcept;

    void add_stroke_to_remove_queue(StrokeMesh& stroke) noexcept;
    void remove_strokes_from_remove_queue() noexcept;
};


}