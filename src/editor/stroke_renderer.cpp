#include <blackboard/editor/stroke_renderer.hpp>

#include <blackboard/editor/stroke.hpp>

#include <raymath.h>
#include <rlgl.h>




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

    if (samples.size() < 2)
        return;

    const std::vector<Edge> edges = create_edges(samples);

    draw_edges(edges, stroke.color, samples.size());


    if (debug_draw_points)
        draw_points(points);

    if (debug_draw_edges)
        draw_edges(edges);
}


void StrokeRenderer::draw_edges(const std::vector<Edge>& edges, const Color& color, const int samples_count) noexcept
{
    rlSetTexture(rlGetTextureIdDefault());
    rlBegin(RL_QUADS);
    rlColor4ub(color.r, color.g, color.b, color.a);

        draw_edges(edges, samples_count);

    rlEnd();
    rlSetTexture(0);
}


void StrokeRenderer::draw_edges(const std::vector<Edge>& edges, const int samples_count) noexcept
{
    for (int i = 0; i < samples_count - 1; i++)
    {
        rlVertex2f(edges[i].top.x, edges[i].top.y);
        rlVertex2f(edges[i + 1].top.x, edges[i + 1].top.y);
        rlVertex2f(edges[i + 1].bottom.x, edges[i + 1].bottom.y);
        rlVertex2f(edges[i].bottom.x, edges[i].bottom.y);
    }
}



void StrokeRenderer::draw_points(const std::vector<StrokePoint>& points) noexcept
{
    for (const auto& point : points)
        DrawCircleV(point.position, 2, RED);
}


void StrokeRenderer::draw_edges(const std::vector<Edge>& edges) noexcept
{
    for (const auto& edge : edges)
    {
        DrawCircleV(edge.top, 2, BLUE);
        DrawCircleV(edge.bottom, 2, BLUE);
    }
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