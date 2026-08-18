#include <blackboard/editor/stroke/stroke_mesh_generator.hpp>

#include <raymath.h>

#include <blackboard/editor/stroke/stroke_mesh_gl_builder.hpp>




using
bb::editor::StrokePoint,
bb::editor::StrokeSample,
bb::editor::StrokeEdge,
bb::editor::StrokeMesh,
bb::editor::StrokeMeshNode,
bb::editor::StrokeMeshGenerator,
bb::editor::StrokeMeshGL;




std::unique_ptr<StrokeMeshGL> StrokeMeshGenerator::generate_mesh_gl(const Stroke& stroke) const noexcept
{
    if (stroke.points.empty())
        return nullptr;

    std::unique_ptr<StrokeMesh> mesh = generate_mesh(stroke);
    return StrokeMeshGLBuilder().build(mesh);
}


std::unique_ptr<StrokeMesh> StrokeMeshGenerator::generate_mesh(const Stroke& stroke) const noexcept
{
    if (stroke.points.empty())
        return nullptr;

    const std::vector<StrokePoint> new_points = add_ghost_points(stroke.points);
    const std::vector<StrokeSample> samples = create_samples(new_points);
    const std::vector<StrokeEdge> edges = create_edges(samples);

    return create_mesh(samples, edges);
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
    const size_t size = points.size() - 3;

    std::vector<StrokeSample> samples;
    samples.reserve(size * samples_per_segment + 1);

    for (size_t i = 1; i < size; i++)
        add_samples_from_segment(samples, StrokePointInterpolation(points, (int)i), samples_amount(points, i), i);

    return samples;
}


unsigned int StrokeMeshGenerator::samples_amount(const std::vector<StrokePoint>& points, size_t i) const noexcept
{
    return adaptative_samples_per_segment ? calculate_adaptative_samples_amount(points, i) : samples_per_segment;
}


unsigned int StrokeMeshGenerator::calculate_adaptative_samples_amount(const std::vector<StrokePoint>& points, const size_t i) const noexcept
{
    constexpr float VelocityFactor = 1.0 / 100.0;
    constexpr float CurvatureFactor = 5.0;

    const float velocity = Vector2Distance(points[i].position, points[i + 1].position) * VelocityFactor;
    const float curvature = (points.size() < 3 ? 0 : calculate_average_curvature(points, i)) * CurvatureFactor;

    return (uint32_t)((float)samples_per_segment + velocity + curvature);
}


float StrokeMeshGenerator::calculate_average_curvature(const std::vector<StrokePoint>& points, const size_t i) noexcept
{
    return (StrokeSample::calculate_curvature(points[i - 1], points[i], points[i + 1])
            + StrokeSample::calculate_curvature(points[i], points[i + 1], points[i + 2])) / 2;
}


void StrokeMeshGenerator::add_samples_from_segment(std::vector<StrokeSample>& samples, const StrokePointInterpolation& segment,
    const unsigned int samples_amount, const size_t i) noexcept
{
    const int start = (i == 1) ? 0 : 1;

    for (size_t j = start; j <= samples_amount; j++)
        samples.emplace_back(segment, (int)j, (int)samples_amount);
}



std::vector<StrokeEdge> StrokeMeshGenerator::create_edges(const std::vector<StrokeSample>& samples) noexcept
{
    constexpr float DirectionEpsilon = 0.0001f;

    std::vector<StrokeEdge> edges(samples.size());

    for (size_t i = 0; i < samples.size(); i++)
    {
        const Vector2 direction = get_direction_from_samples(samples, i);

        if (Vector2Length(direction) < DirectionEpsilon)
            edges[i] = (i > 0) ? edges[i - 1] : StrokeEdge(samples[i].position, samples[i].position);
        else
            edges[i] = create_edge(samples[i], Vector2Normalize(direction));
    }

    return edges;
}


StrokeEdge StrokeMeshGenerator::create_edge(const StrokeSample& sample, const Vector2& direction) noexcept
{
    const Vector2 normal = { -direction.y, direction.x };
    float half_thickness = sample.half_thickness();

    return { sample.position, normal, half_thickness };
}


Vector2 StrokeMeshGenerator::get_direction_from_samples(const std::vector<StrokeSample>& samples, const size_t i) noexcept
{
    const size_t samples_count = samples.size();

    if (i == 0)
        return samples[1].position - samples[0].position;

    if (i == samples_count - 1)
        return samples[samples_count - 1].position - samples[samples_count - 2].position;

    return samples[i + 1].position - samples[i - 1].position;
}




std::unique_ptr<StrokeMesh> StrokeMeshGenerator::create_mesh(const std::vector<StrokeSample>& samples, const std::vector<StrokeEdge>& edges) noexcept
{
    auto* mesh = new StrokeMesh;
    mesh->reserve(samples.size());

    for (size_t i = 0; i < samples.size(); i++)
        mesh->emplace_back(samples[i], edges[i]);

    if (mesh->size() >= 2)
    {
        mesh->front().sample.is_begin = true;
        mesh->back().sample.is_end = true;
    }

    return std::unique_ptr<StrokeMesh>(mesh);
}