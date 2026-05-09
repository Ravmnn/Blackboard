#include <blackboard/editor/stroke_renderer.hpp>

#include <rlgl.h>

#include <blackboard/collisions.hpp>
#include <blackboard/editor/stroke.hpp>




void StrokeRenderer::draw_stroke(const Stroke& stroke) noexcept
{
    draw_stroke_mesh(sampler.generate_mesh(stroke));
}


void StrokeRenderer::draw_stroke_mesh(const std::vector<StrokeMeshNode>& mesh) noexcept
{
    if (mesh.empty())
        return;

    draw_edges(mesh);
    draw_extreme_caps(mesh);

    draw_debug_visualization(mesh);
}


void StrokeRenderer::draw_edges(const std::vector<StrokeMeshNode>& mesh) noexcept
{
    rlSetTexture(rlGetTextureIdDefault());
    rlBegin(RL_QUADS);

        draw_edges_with_caps(mesh);

    rlEnd();
    rlSetTexture(0);
}


void StrokeRenderer::draw_edges_with_caps(const std::vector<StrokeMeshNode>& mesh) noexcept
{
    const Rectangle camera_bounds = camera ? camera->get_world_bounds() : Rectangle{};

    for (int i = 0; i < mesh.size() - 1; i++)
    {
        if (camera && !Collisions::point_inside_rectangle(mesh[i].position(), camera_bounds))
            continue;

        const Color& color = mesh[i].color;
        rlColor4ub(color.r, color.g, color.b, color.a);

        rlVertex2f(mesh[i].edge().top().x, mesh[i].edge().top().y);
        rlVertex2f(mesh[i + 1].edge().top().x, mesh[i + 1].edge().top().y);
        rlVertex2f(mesh[i + 1].edge().bottom().x, mesh[i + 1].edge().bottom().y);
        rlVertex2f(mesh[i].edge().bottom().x, mesh[i].edge().bottom().y);

        draw_cap_if_intense_curve(mesh, i);
    }
}


void StrokeRenderer::draw_cap_if_intense_curve(const std::vector<StrokeMeshNode>& mesh, const size_t i) noexcept
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




void StrokeRenderer::draw_extreme_caps(const std::vector<StrokeMeshNode>& mesh) noexcept
{
    if (mesh.size() < 3)
        return;

    const size_t samples_count = mesh.size();

    const float start_thickness_average = (mesh[0].thickness() / 2 + mesh[1].thickness() / 2 + mesh[2].thickness() / 2) / 3;
    const Vector2 direction_start = Vector2Normalize(mesh[0].position() - mesh[1].position());
    draw_cap(mesh[0].position(), direction_start * -1, start_thickness_average, mesh[0].color);

    const float end_thickness_average = (mesh[samples_count - 1].thickness() / 2 + mesh[samples_count - 2].thickness() / 2 + mesh[samples_count - 3].thickness() / 2) / 3;
    const Vector2 direction_end = Vector2Normalize(mesh[samples_count - 1].position() - mesh[samples_count - 2].position());
    draw_cap(mesh[samples_count - 1].position(), direction_end * -1, end_thickness_average, mesh[samples_count - 1].color);
}


void StrokeRenderer::draw_cap(const Vector2& center, const Vector2& direction, const float radius, const Color& color) noexcept
{
    static constexpr int CapResolution = 24;

    const Vector2 normal = { -direction.y, direction.x };
    const float angle_step = PI / CapResolution;

    for (size_t i = 0; i < CapResolution; i++)
    {
        const float a0 = i * angle_step;
        const float a1 = (i + 1) * angle_step;

        const Vector2 v0 = { normal.x * cosf(a0) - normal.y * sinf(a0), normal.x * sinf(a0) + normal.y * cosf(a0) };
        const Vector2 v1 = { normal.x * cosf(a1) - normal.y * sinf(a1), normal.x * sinf(a1) + normal.y * cosf(a1) };

        DrawTriangle(center, center + v1 * radius, center + v0 * radius, color);
    }
}




void StrokeRenderer::draw_debug_visualization(const std::vector<StrokeMeshNode>& mesh) noexcept
{
    if (should_debug_draw_samples)
        debug_draw_samples(mesh);

    if (should_debug_draw_edges)
        debug_draw_edges(mesh);

    if (should_debug_draw_points)
        debug_draw_points(mesh);
}


void StrokeRenderer::debug_draw_points(const std::vector<StrokeMeshNode>& mesh) noexcept
{
    for (const auto& node : mesh)
        DrawCircleV(node.position(), DebugCircleRadius, RED);
}


void StrokeRenderer::debug_draw_samples(const std::vector<StrokeMeshNode>& mesh) noexcept
{
    for (const auto& node : mesh)
        DrawCircleV(node.position(), DebugCircleRadius, BLUE);
}


void StrokeRenderer::debug_draw_edges(const std::vector<StrokeMeshNode>& mesh) noexcept
{
    for (const auto& node : mesh)
    {
        DrawCircleV(node.edge().top(), DebugCircleRadius, BLUE);
        DrawCircleV(node.edge().bottom(), DebugCircleRadius, BLUE);
    }
}