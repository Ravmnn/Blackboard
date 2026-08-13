#pragma once

#include <blackboard/editor/stroke/stroke_renderer_rl.hpp>
#include <blackboard/editor/editor_environment.hpp>
#include <blackboard/editor/tools/selection/selection.hpp>




namespace bb::editor
{




class EditorSelectionEnvironment final : public EditorEnvironment
{
private:
    std::vector<StrokeMesh*> in_selection_strokes_;

    StrokeMeshOutlineRenderer selection_mesh_outline_renderer_;
    StrokeRendererRL renderer_rl_;


public:
    friend class Selection;


    std::vector<StrokeMesh*> selected_strokes;

    Selection selection;
    SelectionEffect selection_effect;

    //bool use_negative_colors = true;


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