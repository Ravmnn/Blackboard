#include <blackboard/editor/stroke_renderer.hpp>

#include <rlgl.h>

#include <blackboard/editor/stroke.hpp>




using bb::editor::StrokeRenderer;




StrokeRenderer::StrokeRenderer(const StrokeMeshGenerator* sampler, const CanvasCamera* camera) noexcept :
    sampler(sampler),
    camera(camera)
{
    primitive_shape_mode = RL_QUADS;
}




void StrokeRenderer::draw_stroke(const Stroke& stroke) noexcept
{
    if (!sampler)
        return;

    auto mesh = sampler->generate_mesh(stroke);

    if (mesh)
        draw_stroke_mesh(*mesh);
}


void StrokeRenderer::draw_stroke_mesh(const StrokeMesh& mesh) noexcept
{
    if (mesh.empty())
        return;

    draw_edges(mesh);
    draw_extreme_caps(mesh);

    draw_debug_visualization(mesh);
}


void StrokeRenderer::draw_edges(const StrokeMesh& mesh) noexcept
{
    rlSetTexture(rlGetTextureIdDefault());
        draw_edges_with_caps(mesh);
    rlSetTexture(0);
}


void StrokeRenderer::draw_edges_with_caps(const StrokeMesh& mesh) noexcept
{
    const Rectangle camera_bounds = camera ? camera->get_world_bounds() : Rectangle{};

    for (int i = 0; i < (int)mesh.size() - 1; i++)
    {
        if (camera && !mesh_node_is_in_camera_bounds(mesh[i], camera_bounds))
            continue;

        const Color& color = mesh[i].color;

        const Vector2 top = mesh[i].edge().top();
        const Vector2 bottom = mesh[i].edge().bottom();
        const Vector2 next_top = mesh[i + 1].edge().top();
        const Vector2 next_bottom = mesh[i + 1].edge().bottom();

        draw_edges_primitives(top, bottom, next_top, next_bottom, color);
        draw_cap_if_intense_curve(mesh, i);
    }
}


void StrokeRenderer::draw_edges_primitives(const Vector2& top, const Vector2& bottom, const Vector2& next_top, const Vector2& next_bottom, const Color& color) const noexcept
{
    // TODO: use polymorphism, StrokeEdgeRenderer

    if (!outline_only)
    {
        rlBegin(primitive_shape_mode);
        rlColor4ub(color.r, color.g, color.b, color.a);

        rlVertex2f(top.x, top.y);
        rlVertex2f(next_top.x, next_top.y);
        rlVertex2f(next_bottom.x, next_bottom.y);
        rlVertex2f(bottom.x, bottom.y);

        rlEnd();
    }
    else
    {
        const Color outline_color = this->outline_color.value_or(color);

        DrawLineEx(top, next_top, outline_thickness, outline_color);
        DrawLineEx(bottom, next_bottom, outline_thickness, outline_color);
    }
}


void StrokeRenderer::draw_cap_if_intense_curve(const StrokeMesh& mesh, const size_t i) noexcept
{
    constexpr float MaxCurvature = 0.8;

    if (i == 0)
        return;

    const StrokeMeshNode& current_node = mesh[i];

    if (current_node.curvature() <= MaxCurvature)
        return;

    const Vector2 previous = mesh[i - 1].sample().position();
    const Vector2 current = current_node.sample().position();
    const Vector2 next = mesh[i + 1].sample().position();
    const Vector2 dir1 = Vector2Normalize(Vector2Subtract(current, previous));
    const Vector2 dir2 = Vector2Normalize(Vector2Subtract(current, next));
    const Vector2 final_direction = Vector2Normalize(dir1 + dir2) * -1;

    draw_cap(current, final_direction, current_node.thickness() * 0.5f, current_node.color);
}




void StrokeRenderer::draw_extreme_caps(const StrokeMesh& mesh) noexcept
{
    if (mesh.size() < 2)
        return;

    const size_t samples_count = mesh.size();

    const float start_thickness_average = (mesh[0].thickness() / 2 + mesh[1].thickness() / 2) / 2;
    const Vector2 direction_start = Vector2Normalize(mesh[0].position() - mesh[1].position());
    draw_cap(mesh[0].position(), direction_start * -1, start_thickness_average, mesh[0].color);

    const float end_thickness_average = (mesh[samples_count - 1].thickness() / 2 + mesh[samples_count - 2].thickness() / 2) / 2;
    const Vector2 direction_end = Vector2Normalize(mesh[samples_count - 1].position() - mesh[samples_count - 2].position());
    draw_cap(mesh[samples_count - 1].position(), direction_end * -1, end_thickness_average, mesh[samples_count - 1].color);
}


void StrokeRenderer::draw_cap(const Vector2& center, const Vector2& direction, const float radius, const Color& color) const noexcept
{
    static constexpr int CapResolution = 32;

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

        // TODO: use polymorphism, StrokeCapRenderer

        if (!outline_only)
            DrawTriangle(center, begin, end, true_color);
        else
        {
            DrawLineEx(
                Vector2MoveTowards(begin, end, -outline_thickness / 5),
                Vector2MoveTowards(end, begin, -outline_thickness / 5),
            outline_thickness, outline_color.value_or(true_color));
        }
    }
}




void StrokeRenderer::draw_debug_visualization(const StrokeMesh& mesh) const noexcept
{
    if (should_debug_draw_samples)
        debug_draw_samples(mesh);

    if (should_debug_draw_edges)
        debug_draw_edges(mesh);

    if (should_debug_draw_points)
        debug_draw_points(mesh);
}


void StrokeRenderer::debug_draw_points(const StrokeMesh& mesh) noexcept
{
    for (const auto& node : mesh)
        DrawCircleV(node.sample().origin().position, DebugCircleRadius, RED);
}


void StrokeRenderer::debug_draw_samples(const StrokeMesh& mesh) noexcept
{
    for (const auto& node : mesh)
        DrawCircleV(node.position(), DebugCircleRadius, BLUE);
}


void StrokeRenderer::debug_draw_edges(const StrokeMesh& mesh) noexcept
{
    for (const auto& node : mesh)
    {
        DrawCircleV(node.edge().top(), DebugCircleRadius, BLUE);
        DrawCircleV(node.edge().bottom(), DebugCircleRadius, BLUE);
    }
}