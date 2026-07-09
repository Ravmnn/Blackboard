#pragma once

#include <blackboard/editor/stroke/stroke_mesh.hpp>
#include <blackboard/editor/stroke/stroke_mesh_outline_renderer.hpp>
#include <blackboard/editor/effects/negative.hpp>
#include <blackboard/editor/editor_environment.hpp>
#include <blackboard/editor/tools/selection/selection.hpp>




namespace bb::editor
{




// TODO: make outline thickness a field of StrokeMesh instead of StrokeMeshRenderer; add an optional override_thickness though in renderer
// TODO: add support for multiple StrokeMeshRenderer usage at the same time inside StrokeRenderer
// TODO: in-selection strokes should have something slightly different from selected strokes in visual
class EditorSelectionEnvironment final : public EditorEnvironment
{
private:
    std::vector<StrokeMesh*> in_selection_strokes_;

    StrokeMeshOutlineRenderer selection_outline_stroke_mesh_renderer_;

    static constexpr float SelectionOutlineBaseThickness = 12;


    NegativeEffect negative_effect_;


public:
    friend class Selection;


    std::vector<StrokeMesh*> selected_strokes;

    Selection selection;
    bool use_negative_colors = true;


    explicit EditorSelectionEnvironment(Editor& editor) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


private:
    void draw_selected_strokes() noexcept;


    void on_enabled() noexcept override;
    void on_disabled() noexcept override;


    void on_left_button_click() noexcept override;
    void on_left_button_drag_start() noexcept override;
    void on_left_button_drag_end() noexcept override;

    void add_in_selection_strokes_to_selection() noexcept;


    void on_right_button_release() noexcept override;
    void on_right_button_drag_start() noexcept override;
    void on_right_button_drag_end() noexcept override;
};




}