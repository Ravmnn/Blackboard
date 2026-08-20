#pragma once

#include <blackboard/ui/focusable.hpp>
#include <blackboard/ui/clickable.hpp>
#include <blackboard/ui/components/component.hpp>
#include <blackboard/ui/components/rounded_rectangle.hpp>
#include <blackboard/editor/mouse_late_mode_indicator.hpp>
#include <blackboard/editor/vanish.hpp>
#include <blackboard/editor/palette.hpp>
#include <blackboard/editor/canvas.hpp>
#include <blackboard/editor/stroke/stroke_mesh_debug_renderer.hpp>
#include <blackboard/editor/stroke/stroke_mesh_gl.hpp>
#include <blackboard/editor/editor_background.hpp>
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


    Canvas* canvas_ = nullptr;
    EditorBackground background_;

    MouseLateModeIndicator mouse_late_mode_indicator_;

    std::vector<std::unique_ptr<Vanish<Tool>>> vanish_animations_;

    EditorEnvironment* current_environment_ = nullptr;
    Tool* last_tool_ = nullptr;


public:
    ColorMenu* color_menu = nullptr;


    StrokeMeshDebugRenderer stroke_debug_renderer;
    StrokeRendererGL stroke_renderer;
    StrokeMeshGenerator stroke_mesh_generator;

    std::vector<std::unique_ptr<StrokeMeshGL>> meshes;


    EditorDrawingEnvironment draw_environment;
    EditorSelectionEnvironment selection_environment;


    Palette palette;
    bool dynamic_background_color = false;

    bool wire_mode = false;


    Event<> environment_changed;
    Event<> tool_changed;


    Editor(ui::Context& ui_context) noexcept;


    void update() noexcept override;


    [[nodiscard]] Canvas& canvas() noexcept { return *canvas_; }
    [[nodiscard]] const Canvas& canvas() const noexcept { return *canvas_; }
    [[nodiscard]] const EditorEnvironment& current_environment() const noexcept { return *current_environment_; }

    [[nodiscard]] Rectangle bounding_box() const noexcept override { return {}; }

    [[nodiscard]] bool is_point_over(const Vector2& /* unused */) const noexcept override { return true; }

    void set_current_environment(EditorEnvironment& environment) noexcept;


    StrokeMesh* get_stroke_under_point(const Vector2& point) noexcept;
    StrokeMesh* get_stroke_intersecting_segment(const math::Segment& segment) noexcept;
    StrokeMesh* get_stroke_under_mouse() noexcept { return get_stroke_under_point(canvas().mouse_position()); }


    void add_stroke(const Stroke& stroke) noexcept;
    void remove_stroke(const StrokeMesh& mesh) noexcept;


private:
    void log_canvas_framebuffer_status() noexcept;


    void update_focus() noexcept;
    void update_background() noexcept;
    void update_tool_changed_event() noexcept;
    void update_vanish_animations() noexcept;
    void update_effects() noexcept;
    void update_keybindings() noexcept;


    void draw_self() noexcept override;
    void draw_to_canvas() noexcept;

    void draw_background() noexcept;
    void draw_strokes() noexcept;
    void draw_cached_and_brush_strokes() noexcept;
    void draw_debug_strokes() noexcept;

    void draw_vanish_animations() noexcept;
    void draw_statistics() const noexcept;


    std::unique_ptr<StrokeMesh> brush_stroke_mesh() noexcept {
        return stroke_mesh_generator.generate_mesh(draw_environment.brush.stroke());
    }


    void on_environment_changed() noexcept;
    void on_tool_changed() noexcept;
};




}