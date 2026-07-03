#pragma once

#include <blackboard/math/collisions.hpp>
#include <blackboard/editor/canvas_camera.hpp>
#include <blackboard/editor/stroke/stroke_mesh_generator.hpp>
#include <blackboard/editor/stroke/stroke_mesh_renderer.hpp>




namespace bb::editor
{




class StrokeRenderer
{
private:
    static constexpr float DebugCircleRadius = 1;


    const StrokeMeshRenderer* mesh_renderer_;


public:
    bool should_debug_draw_points = false;
    bool should_debug_draw_samples = false;
    bool should_debug_draw_edges = false;
    bool should_debug_draw_caps = false;

    const StrokeMeshGenerator* sampler;
    const CanvasCamera* camera;


    StrokeRenderer(const StrokeMeshRenderer& mesh_renderer, const StrokeMeshGenerator* sampler, const CanvasCamera* camera = nullptr) noexcept;


    void draw_stroke(const Stroke& stroke) noexcept;
    void draw_stroke_mesh(const StrokeMesh& mesh) noexcept;

    [[nodiscard]] const StrokeMeshRenderer& mesh_renderer() const noexcept { return *mesh_renderer_; }

    void set_mesh_renderer(const StrokeMeshRenderer& mesh_renderer) noexcept { mesh_renderer_ = &mesh_renderer; }


private:
    void draw_edges(const StrokeMesh& mesh) noexcept;
    void draw_edges_with_caps(const StrokeMesh& mesh) noexcept;
    void draw_cap_if_intense_curve(const StrokeMesh& mesh, size_t i) noexcept;

    [[nodiscard]] static bool mesh_node_is_in_camera_bounds(const StrokeMeshNode& node, const Rectangle& camera_bounds) noexcept
    {
        return math::Collisions::point_inside_rectangle(node.position(), camera_bounds);
    }

    void draw_extreme_caps(const StrokeMesh& mesh) noexcept;
    void draw_cap(const Vector2& center, const Vector2& direction, float radius, const Color& color) const noexcept;

    void draw_debug_visualization(const StrokeMesh& mesh) const noexcept;

    static void debug_draw_points(const StrokeMesh& mesh) noexcept;
    static void debug_draw_samples(const StrokeMesh& mesh) noexcept;
    static void debug_draw_edges(const StrokeMesh& mesh) noexcept;
};




}