#pragma once

#include <blackboard/editor/stroke/stroke_renderer.hpp>
#include <blackboard/editor/stroke/stroke_mesh_outline_renderer.hpp>




struct Vector2;
struct Rectangle;
struct Color;


namespace bb::editor
{




class StrokeMeshGenerator;
class Stroke;
class StrokeMesh;
class StrokeMeshNode;


class StrokeRendererRL : public StrokeRenderer
{
private:
    std::unique_ptr<StrokeMeshRenderer> default_mesh_renderer_ = nullptr;
    std::unique_ptr<StrokeMeshOutlineRenderer> default_mesh_outline_renderer_ = nullptr;


public:
    StrokeMeshRenderer* mesh_renderer;
    StrokeMeshOutlineRenderer* mesh_outline_renderer;

    std::vector<StrokeMeshRenderer*> extra_renderers;


    StrokeRendererRL() noexcept;
    StrokeRendererRL(StrokeMeshRenderer* mesh_renderer, StrokeMeshOutlineRenderer* mesh_outline_renderer) noexcept;


    void draw_stroke_mesh(const StrokeMesh& mesh) noexcept override;


private:
    void draw_edges(const StrokeMesh& mesh) noexcept;
    void draw_edges_with_caps(const StrokeMesh& mesh) noexcept;
    void draw_cap_if_intense_curve(const StrokeMesh& mesh, size_t i) noexcept;

    [[nodiscard]] static bool mesh_node_is_in_camera_bounds(const StrokeMeshNode& node, const Rectangle& camera_bounds) noexcept;

    void draw_extreme_caps(const StrokeMesh& mesh) noexcept;
    void draw_cap(const Vector2& center, const Vector2& direction, float radius, const Color& color, float outline_thickness = 0, const Color& outline_color = WHITE) const noexcept;


    template <typename T> requires std::derived_from<T, StrokeMeshQuad> || std::derived_from<T, StrokeMeshCapSegment>
    void draw_mesh_element(const T& element) const noexcept
    {
        if (mesh_renderer)
            mesh_renderer->render(element);

        if (mesh_outline_renderer)
            mesh_outline_renderer->render(element);

        for (const auto& extra_renderer : extra_renderers)
            if (extra_renderer)
                extra_renderer->render(element);
    }
};




}