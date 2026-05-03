#include <blackboard/editor/stroke_renderer.hpp>

#include <algorithm>

#include <rlgl.h>
#include <raymath.h>

#include <blackboard/editor/stroke.hpp>




StrokeRenderer::SplineSegment::SplineSegment(const std::vector<StrokePoint>& points, const int i)
{
    p0 = points[i - 1].position;
    p1 = points[i].position;
    p2 = points[i + 1].position;
    p3 = points[i + 2].position;

    current_thickness = points[i].thickness;
    next_thickness = points[i + 1].thickness;
}




void StrokeRenderer::draw_stroke(const Stroke& stroke) noexcept
{
    if (stroke.points.empty())
        return;

    const std::vector<StrokePoint> points = add_ghost_points(stroke.points);
    const std::vector<Sample> samples = create_samples(points);
    const size_t samples_count = samples.size();

    if (samples.size() < 2)
        return;

    const std::vector<Edge> edges = create_edges(samples);

    draw_edges(edges, samples, stroke.color);
    draw_extreme_caps(samples, stroke.color);

    draw_debug_visualization(points, samples, edges);
}


void StrokeRenderer::draw_edges(const std::vector<Edge>& edges, const std::vector<Sample>& samples, const Color& color) noexcept
{
    rlSetTexture(rlGetTextureIdDefault());
    rlBegin(RL_QUADS);
    rlColor4ub(color.r, color.g, color.b, color.a);

        draw_edges_with_caps(edges, samples, color);

    rlEnd();
    rlSetTexture(0);
}


void StrokeRenderer::draw_edges_with_caps(const std::vector<Edge>& edges, const std::vector<Sample>& samples, const Color& color) noexcept
{
    for (int i = 0; i < samples.size() - 1; i++)
    {
        rlVertex2f(edges[i].top.x, edges[i].top.y);
        rlVertex2f(edges[i + 1].top.x, edges[i + 1].top.y);
        rlVertex2f(edges[i + 1].bottom.x, edges[i + 1].bottom.y);
        rlVertex2f(edges[i].bottom.x, edges[i].bottom.y);

        draw_cap_if_intense_curve(samples, i, color);
    }
}


void StrokeRenderer::draw_cap_if_intense_curve(const std::vector<Sample>& samples, const size_t i, const Color& color) noexcept
{
    if (i == 0)
        return;

    const Vector2 previous = samples[i - 1].position, current = samples[i].position, next = samples[i + 1].position;
    const float curvature  = stroke_curvature(previous, current, next);

    if (curvature <= 0.8)
        return;

    const Vector2 dir1 = Vector2Normalize(Vector2Subtract(current, previous));
    const Vector2 dir2 = Vector2Normalize(Vector2Subtract(current, next));
    const Vector2 final_direction = Vector2Normalize(dir1 + dir2) * -1;

    draw_cap(current, final_direction, samples[i].thickness * 0.5f, color);
}




void StrokeRenderer::draw_extreme_caps(const std::vector<StrokeRenderer::Sample>& samples, const Color& color) noexcept
{
    const size_t samples_count = samples.size();

    const Vector2 dirStart = Vector2Normalize(samples[0].position - samples[1].position);
    draw_cap(samples[0].position, dirStart * -1, samples[0].thickness * 0.5f, color);

    const Vector2 dirEnd = Vector2Normalize(samples[samples_count - 1].position - samples[samples_count - 2].position);
    draw_cap(samples[samples_count - 1].position, dirEnd * -1, samples[samples_count - 1].thickness * 0.5f, color);
}


void StrokeRenderer::draw_cap(const Vector2& center, const Vector2& direction, const float radius, const Color& color) noexcept
{
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




void StrokeRenderer::draw_debug_visualization(const std::vector<StrokePoint>& points, const std::vector<Sample>& samples, const std::vector<Edge>& edges) noexcept
{
    if (should_debug_draw_samples)
        debug_draw_samples(samples);

    if (should_debug_draw_edges)
        debug_draw_edges(edges);

    if (should_debug_draw_points)
        debug_draw_points(points);
}


void StrokeRenderer::debug_draw_points(const std::vector<StrokePoint>& points) noexcept
{
    for (const auto& point : points)
        DrawCircleV(point.position, DebugCircleRadius, RED);
}


void StrokeRenderer::debug_draw_samples(const std::vector<Sample>& samples) noexcept
{
    for (const auto& sample : samples)
        DrawCircleV(sample.position, DebugCircleRadius, BLUE);
}


void StrokeRenderer::debug_draw_edges(const std::vector<Edge>& edges) noexcept
{
    for (const auto& edge : edges)
    {
        DrawCircleV(edge.top, DebugCircleRadius, BLUE);
        DrawCircleV(edge.bottom, DebugCircleRadius, BLUE);
    }
}




float StrokeRenderer::stroke_curvature(const Vector2& previous, const Vector2& curent, const Vector2& next) noexcept
{
    const Vector2 d1 = Vector2Normalize(Vector2Subtract(curent, previous));
    const Vector2 d2 = Vector2Normalize(Vector2Subtract(next, curent));

    float dot = Vector2DotProduct(d1, d2);
    dot = std::clamp(dot, -1.0f, 1.0f);

    return acosf(dot);
}




std::vector<StrokePoint> StrokeRenderer::add_ghost_points(const std::vector<StrokePoint>& points) noexcept
{
    std::vector<StrokePoint> new_points;
    new_points.reserve(points.size() + 2);

    new_points.push_back(points.front());
    new_points.insert(new_points.end(), points.begin(), points.end());
    new_points.push_back(points.back());

    return new_points;
}



std::vector<StrokeRenderer::Sample> StrokeRenderer::create_samples(const std::vector<StrokePoint>& points) noexcept
{
    std::vector<Sample> samples;
    samples.reserve((points.size() - 3) * samples_per_segment + 1);

    for (size_t i = 1; i < points.size() - 2; i++)
        add_samples_from_segment(samples, SplineSegment(points, i), i);

    return samples;
}


void StrokeRenderer::add_samples_from_segment(std::vector<StrokeRenderer::Sample>& samples, const StrokeRenderer::SplineSegment& segment, const size_t i)
{
    const int start = (i == 1) ? 0 : 1;

    for (size_t j = start; j <= samples_per_segment; j++)
    {
        const float t = (float)j / samples_per_segment;
        samples.push_back(Sample{segment.point(t), segment.thickness(t)});
    }
}



std::vector<StrokeRenderer::Edge> StrokeRenderer::create_edges(const std::vector<Sample>& samples) noexcept
{
    std::vector<Edge> edges(samples.size());

    for (size_t i = 0; i < samples.size(); i++)
    {
        const Vector2 direction = get_direction_from_samples(samples, i);

        if (Vector2Length(direction) < DirectionEpsilon)
        {
            edges[i] = (i > 0) ? edges[i - 1] : Edge(samples[i].position, samples[i].position);
            continue;
        }

        edges[i] = create_edge(samples[i], Vector2Normalize(direction));
    }

    return edges;
}


StrokeRenderer::Edge StrokeRenderer::create_edge(const Sample& sample, const Vector2& direction) noexcept
{
    const Vector2 normal = { -direction.y, direction.x };
    const float half_thickness = sample.thickness / 2;

    return Edge(sample.position, normal, half_thickness);
}


Vector2 StrokeRenderer::get_direction_from_samples(const std::vector<Sample>& samples, const size_t i) noexcept
{
    const size_t samples_count = samples.size();

    if (i == 0)
        return samples[1].position - samples[0].position;

    else if (i == samples_count - 1)
        return samples[samples_count - 1].position - samples[samples_count - 2].position;

    else
        return samples[i + 1].position - samples[i - 1].position;
}