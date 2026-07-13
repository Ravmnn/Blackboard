#pragma once

#include <blackboard/ui/focusable.hpp>
#include <blackboard/ui/clickable.hpp>
#include <blackboard/ui/components/component.hpp>
#include <blackboard/editor/vanish.hpp>
#include <blackboard/editor/palette.hpp>
#include <blackboard/editor/canvas.hpp>
#include <blackboard/editor/mouse_late_mode_indicator.hpp>
#include <blackboard/editor/editor_background.hpp>
#include <blackboard/editor/editor_drawing_environment.hpp>
#include <blackboard/editor/editor_selection_environment.hpp>
#include <blackboard/editor/stroke/stroke_mesh_manager.hpp>




namespace bb::editor
{




class ColorMenu;


class Editor final : public ui::Component, public ui::Clickable, public ui::Focusable
{
private:
    static constexpr Color DefaultPaletteColor = { 211, 211, 211, 255 };
    static constexpr Color DefaultBackgroundColor = { 18, 18, 18, 255 };


    bool draw_statistics_ = false;

    Tool* last_tool_ = nullptr;

    std::vector<std::unique_ptr<Vanish<Tool>>> vanish_animations_;


public:
    EditorBackground background;

    Canvas canvas;
    Palette palette;
    bool dynamic_background_color = false;

    StrokeMeshManager stroke_manager;


    Event<> environment_changed;
    Event<> tool_changed;

    EditorDrawingEnvironment draw_environment;
    EditorSelectionEnvironment selection_environment;
    EditorEnvironment* current_environment = nullptr;


    MouseLateModeIndicator mouse_late_mode_indicator;


    ColorMenu* color_menu;


    Editor(ui::Context& ui_context) noexcept;


    void update() noexcept override;


    [[nodiscard]] Rectangle bounding_box() const noexcept override { return {}; }


    [[nodiscard]] bool is_point_over(const Vector2& /* unused */) const noexcept override { return true; }

    void set_current_environment(EditorEnvironment& environment) noexcept;


    StrokeMesh* get_stroke_under_point(const Vector2& point) noexcept;
    StrokeMesh* get_stroke_intersecting_segment(const math::Segment& segment) noexcept;
    StrokeMesh* get_stroke_under_mouse() noexcept { return get_stroke_under_point(canvas.mouse_position()); }


private:
    void update_focus() noexcept;
    void update_keybindings() noexcept;
    void update_background() noexcept;
    void update_tool_changed_event() noexcept;
    void update_vanish_animations() noexcept;

    void draw_self() noexcept override;
    void draw_to_canvas() noexcept;
    void draw_vanish_animations() noexcept;
    void draw_canvas_content() noexcept;
    void draw_statistics() const noexcept;


    void on_environment_changed() noexcept;
    void on_tool_changed() noexcept;
};




}