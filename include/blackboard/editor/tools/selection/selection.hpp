#pragma once

#include <blackboard/math/rect.hpp>
#include <blackboard/editor/tools/tool.hpp>
#include <blackboard/editor/tools/selection/body.hpp>




namespace bb::editor
{




class StrokeMesh;
class EditorSelectionEnvironment;


class Selection : public Tool
{
private:
    Vector2 start_position_;
    Vector2 end_position_;


public:
    friend class SelectionBody;


    EditorSelectionEnvironment& selection_environment;


    SelectionBody body;

    float required_selection_ratio = 0.8;


    Selection(EditorEnvironment& environment) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


    [[nodiscard]] Vector2 position() const noexcept override;
    [[nodiscard]] Rectangle bounding_box() const noexcept override { return body.bounding_box(); }
    [[nodiscard]] Rectangle selection_area() const noexcept { return math::Rect::from_two_points(start_position_, end_position_); }

    [[nodiscard]] const Vector2& start_position() const noexcept { return start_position_; }
    [[nodiscard]] const Vector2& end_position() const noexcept { return end_position_; }


protected:
    void update_selection() noexcept;

    size_t selected_mesh_nodes_for_stroke(const StrokeMesh& mesh) noexcept;
    bool can_add_stroke_to_selection_list(const StrokeMesh& mesh) noexcept;


    void on_enabled() noexcept override;
};




}