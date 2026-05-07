#include <blackboard/editor/stroke_mesh_generator.hpp>

#include <algorithm>




std::vector<StrokeMeshNode> StrokeMeshGenerator::generate_mesh(const Stroke& stroke) const noexcept
{
    const std::vector<StrokePoint> new_points = add_ghost_points(stroke.points);
    const std::vector<StrokeSample> samples = create_samples(new_points);
    const std::vector<StrokeEdge> edges = create_edges(samples);

    return create_mesh(samples, edges, stroke.color);
}




std::vector<StrokePoint> StrokeMeshGenerator::add_ghost_points(const std::vector<StrokePoint>& points) noexcept
{
    std::vector<StrokePoint> new_points;
    new_points.reserve(points.size() + 2);

    new_points.push_back(points.front());
    new_points.insert(new_points.end(), points.begin(), points.end());
    new_points.push_back(points.back());

    return new_points;
}



std::vector<StrokeSample> StrokeMeshGenerator::create_samples(const std::vector<StrokePoint>& points) const noexcept
{
    std::vector<StrokeSample> samples;
    samples.reserve((points.size() - 3) * samples_per_segment + 1);

    for (size_t i = 1; i < points.size() - 2; i++)
        add_samples_from_segment(samples, StrokeSplineSegment(points, i), i);

    return samples;
}


void StrokeMeshGenerator::add_samples_from_segment(std::vector<StrokeSample>& samples, const StrokeSplineSegment& segment,
    const size_t i) const noexcept
{
    const int start = (i == 1) ? 0 : 1;

    for (size_t j = start; j <= samples_per_segment; j++)
        samples.push_back(StrokeSample(segment, (float)j / samples_per_segment));
}



std::vector<StrokeEdge> StrokeMeshGenerator::create_edges(const std::vector<StrokeSample>& samples) noexcept
{
    std::vector<StrokeEdge> edges(samples.size());

    for (size_t i = 0; i < samples.size(); i++)
    {
        const Vector2 direction = get_direction_from_samples(samples, i);

        if (Vector2Length(direction) < DirectionEpsilon)
        {
            edges[i] = (i > 0) ? edges[i - 1] : StrokeEdge(samples[i].position(), samples[i].position());
            continue;
        }

        edges[i] = create_edge(samples[i], Vector2Normalize(direction));
    }

    return edges;
}


StrokeEdge StrokeMeshGenerator::create_edge(const StrokeSample& sample, const Vector2& direction) noexcept
{
    const Vector2 normal = { -direction.y, direction.x };
    const float half_thickness = sample.thickness() / 2;

    return StrokeEdge(sample.position(), normal, half_thickness);
}


Vector2 StrokeMeshGenerator::get_direction_from_samples(const std::vector<StrokeSample>& samples, const size_t i) noexcept
{
    const size_t samples_count = samples.size();

    if (i == 0)
        return samples[1].position() - samples[0].position();

    else if (i == samples_count - 1)
        return samples[samples_count - 1].position() - samples[samples_count - 2].position();

    else
        return samples[i + 1].position() - samples[i - 1].position();
}




std::vector<StrokeMeshNode> StrokeMeshGenerator::create_mesh(const std::vector<StrokeSample>& samples, const std::vector<StrokeEdge>& edges, const Color& color) noexcept
{
    std::vector<StrokeMeshNode> mesh(samples.size());

    for (size_t i = 0; i < mesh.size(); i++)
        mesh.push_back(StrokeMeshNode(samples[i], edges[i], color));

    return mesh;
}