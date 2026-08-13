#include <blackboard/editor/stroke/stroke_renderer_rl.hpp>

#include <blackboard/math/collisions.hpp>
#include <blackboard/editor/stroke/stroke_mesh.hpp>




using
bb::math::Collisions,
bb::editor::StrokeMeshNode,
bb::editor::StrokeRendererRL;




StrokeRendererRL::StrokeRendererRL() noexcept
{
    mesh_renderer = (default_mesh_renderer_ = std::make_unique<StrokeMeshRenderer>()).get();
    mesh_outline_renderer = (default_mesh_outline_renderer_ = std::make_unique<StrokeMeshOutlineRenderer>()).get();
}


StrokeRendererRL::StrokeRendererRL(StrokeMeshRenderer* mesh_renderer, StrokeMeshOutlineRenderer* mesh_outline_renderer) noexcept :
    mesh_renderer(mesh_renderer),
    mesh_outline_renderer(mesh_outline_renderer)
{}




void StrokeRendererRL::draw_stroke_mesh(const StrokeMesh& mesh) noexcept
{
    if (!mesh_renderer && !mesh_outline_renderer)
        return;

    if (mesh.empty())
        return;

    draw_edges_with_caps(mesh);
    draw_extreme_caps(mesh);

    draw_debug_visualization(mesh);
}


void StrokeRendererRL::draw_edges_with_caps(const StrokeMesh& mesh) noexcept
{
    const Rectangle view_area = this->view_area ? *this->view_area : Rectangle{};

    for (int i = 0; i < (int)mesh.size() - 1; i++)
    {
        if (this->view_area && !mesh_node_is_in_camera_bounds(mesh[i], view_area))
            continue;

        draw_mesh_element(StrokeMeshQuad{ .first = mesh[i], .second = mesh[i + 1] });
        draw_cap_if_intense_curve(mesh, i);
    }
}


void StrokeRendererRL::draw_cap_if_intense_curve(const StrokeMesh& mesh, const size_t i) noexcept
{
    constexpr float MaxCurvature = 0.8;

    if (i == 0)
        return;

    const StrokeMeshNode& current_node = mesh[i];

    if (current_node.curvature() <= MaxCurvature)
        return;

    const Vector2 previous = mesh[i - 1].sample.position;
    const Vector2 current = current_node.sample.position;
    const Vector2 next = mesh[i + 1].sample.position;
    const Vector2 dir1 = Vector2Normalize(Vector2Subtract(current, previous));
    const Vector2 dir2 = Vector2Normalize(Vector2Subtract(current, next));
    const Vector2 final_direction = Vector2Normalize(dir1 + dir2) * -1;

    draw_cap(current, final_direction, current_node.half_thickness(), current_node.color(), current_node.outline_thickness(), current_node.outline_color());
}




bool StrokeRendererRL::mesh_node_is_in_camera_bounds(const StrokeMeshNode& node, const Rectangle& camera_bounds) noexcept
{
    return Collisions::point_inside_rectangle(node.position(), camera_bounds);
}




void StrokeRendererRL::draw_extreme_caps(const StrokeMesh& mesh) noexcept
{
    if (mesh.size() < 2)
        return;

    const size_t samples_count = mesh.size();

    const float start_thickness_average = (mesh[0].thickness() / 2 + mesh[1].thickness() / 2) / 2;
    const Vector2 direction_start = Vector2Normalize(mesh[0].position() - mesh[1].position());
    draw_cap(mesh[0].position(), direction_start * -1, start_thickness_average, mesh[0].color(), mesh[0].outline_thickness(), mesh[0].outline_color());

    const float end_thickness_average = (mesh[samples_count - 1].thickness() / 2 + mesh[samples_count - 2].thickness() / 2) / 2;
    const Vector2 direction_end = Vector2Normalize(mesh[samples_count - 1].position() - mesh[samples_count - 2].position());
    draw_cap(mesh[samples_count - 1].position(), direction_end * -1, end_thickness_average, mesh[samples_count - 1].color(), mesh[samples_count - 1].outline_thickness(), mesh[samples_count - 1].outline_color());
}



void StrokeRendererRL::draw_cap(const Vector2& center, const Vector2& direction, const float radius, const Color& color, const float outline_thickness, const Color& outline_color) const noexcept
{
    constexpr int CapResolution = 32;

    const Vector2 normal = { -direction.y, direction.x };
    const float angle_step = PI / CapResolution;

    const Color true_color = should_debug_draw_caps ? RED : color;

    for (size_t i = 0; i < CapResolution; i++)
    {
        const float a0 = (float)i * angle_step;
        const float a1 = (float)(i + 1) * angle_step;

        const Vector2 v0 = { normal.x * cosf(a0) - normal.y * sinf(a0), normal.x * sinf(a0) + normal.y * cosf(a0) };
        const Vector2 v1 = { normal.x * cosf(a1) - normal.y * sinf(a1), normal.x * sinf(a1) + normal.y * cosf(a1) };

        const Vector2 begin = center + v1 * radius;
        const Vector2 end = center + v0 * radius;

        draw_mesh_element(StrokeMeshCapSegment{
            .center = center,
            .begin = begin,
            .end = end,
            .color = true_color,
            .outline_thickness = outline_thickness,
            .outline_color = outline_color
        });
    }
}




void StrokeRendererRL::draw_debug_visualization(const StrokeMesh& mesh) const noexcept
{
    if (should_debug_draw_samples)
        debug_draw_samples(mesh);

    if (should_debug_draw_edges)
        debug_draw_edges(mesh);

    if (should_debug_draw_points)
        debug_draw_points(mesh);
}


void StrokeRendererRL::debug_draw_points(const StrokeMesh& mesh) noexcept
{
    for (const auto& node : mesh)
        DrawCircleV(node.sample.interpolation.origin_point, DebugCircleRadius, RED);
}


void StrokeRendererRL::debug_draw_samples(const StrokeMesh& mesh) noexcept
{
    for (const auto& node : mesh)
        DrawCircleV(node.position(), DebugCircleRadius, BLUE);
}


void StrokeRendererRL::debug_draw_edges(const StrokeMesh& mesh) noexcept
{
    for (const auto& node : mesh)
    {
        DrawCircleV(node.edge.top, DebugCircleRadius, BLUE);
        DrawCircleV(node.edge.bottom, DebugCircleRadius, BLUE);
    }
}