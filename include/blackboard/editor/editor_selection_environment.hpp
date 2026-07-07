#pragma once

#include <blackboard/editor/effects/negative.hpp>
#include <blackboard/editor/editor_environment.hpp>
#include <blackboard/editor/stroke/stroke_mesh_outline_renderer.hpp>
#include <blackboard/editor/tools/selection/selection.hpp>




namespace bb::editor
{




class EditorSelectionEnvironment final : public EditorEnvironment
{
private:
    StrokeMeshOutlineRenderer selection_outline_stroke_mesh_renderer_;

    static constexpr float SelectionOutlineBaseThickness = 12;


    NegativeEffect negative_effect_;


public:
    Selection selection;
    bool use_negative_colors = true;


    explicit EditorSelectionEnvironment(Editor& editor) noexcept;


    void update() noexcept override;
    void draw() noexcept override;


private:
    void draw_selected_strokes() noexcept;


    void on_enabled() noexcept override;
};




}