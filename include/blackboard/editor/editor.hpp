#pragma once

#include <blackboard/ui/context.hpp>
#include <blackboard/ui/clickable.hpp>
#include <blackboard/editor/effects/negative.hpp>
#include <blackboard/editor/canvas.hpp>
#include <blackboard/editor/stroke/stroke_mesh_outline_renderer.hpp>
#include <blackboard/editor/editor_drawing_environment.hpp>
#include <blackboard/editor/editor_selection_environment.hpp>




namespace bb::editor
{




class ColorMenu;


class Editor final : public ui::Component, public ui::Clickable, public ui::Focusable
{
private:
    static constexpr Color DefaultPaletteColor = { 211, 211, 211, 255 };
    static constexpr Color DefaultBackgroundColor = { 18, 18, 18, 255 };


    bool draw_statistics_ = false;


    StrokeMeshRenderer default_mesh_renderer_;
    StrokeMeshOutlineRenderer selection_outline_mesh_renderer_;

    static constexpr float SelectionOutlineBaseThickness = 12;


    NegativeEffect negative_effect_;


    Stopwatch mouse_button_late_mode_stopwatch_;
    std::chrono::milliseconds time_to_enter_late_mode_;


public:
    // TODO: vanish animation when switching tool (similar to FL)


    Canvas canvas;
    Palette palette;
    bool dynamic_background_color = true;

    EditorDrawingEnvironment draw_environment;
    EditorSelectionEnvironment selection_environment;
    EditorEnvironment* current_environment = nullptr;

    Tool* current_tool = nullptr;


    ColorMenu* color_menu;


    Editor(ui::Context& ui_context) noexcept;


    void update() noexcept override;


    void set_current_tool(Tool& tool) noexcept { current_tool = &tool; }
    void set_current_environment(EditorEnvironment& environment) noexcept { current_environment = &environment; current_environment->enable(); }


    [[nodiscard]] Rectangle relative_bounding_box() const noexcept override { return {}; }

    [[nodiscard]] bool is_point_over(const Vector2& /* unused */) const noexcept override { return true; }


private:
    void update_focus() noexcept;
    void update_keybindings() noexcept;
    void update_canvas_background() noexcept;
    void update_effects() noexcept;

    void draw_self() noexcept override;
    void draw_to_canvas() noexcept;
    void draw_selected_strokes() noexcept;
    void draw_canvas_content() noexcept;
    void draw_statistics() const noexcept;
};




}