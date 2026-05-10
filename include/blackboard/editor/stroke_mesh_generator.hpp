#pragma once

#include <blackboard/editor/stroke_mesh.hpp>




class StrokeMeshGenerator
{
private:
    static constexpr float DirectionEpsilon = 0.0001f;


public:
    unsigned int samples_per_segment;
    bool adaptative_samples_per_segment = true;


    explicit StrokeMeshGenerator(const unsigned int samples_per_segment) noexcept
        : samples_per_segment(samples_per_segment) {}


    std::vector<StrokeMeshNode> generate_mesh(const Stroke& stroke) const noexcept;


private:
    static std::vector<StrokePoint> add_ghost_points(const std::vector<StrokePoint>& points) noexcept;
    std::vector<StrokeSample> create_samples(const std::vector<StrokePoint>& points) const noexcept;
    unsigned int calculate_adaptative_samples_amount(const std::vector<StrokePoint>& points, const size_t i) const noexcept;
    static float calculate_average_curvature(const std::vector<StrokePoint>& points, const size_t i) noexcept;
    static void add_samples_from_segment(std::vector<StrokeSample>& samples, const StrokeSplineSegment& segment, const unsigned int samples_amount, const size_t i) noexcept;

    static std::vector<StrokeEdge> create_edges(const std::vector<StrokeSample>& samples) noexcept;
    static StrokeEdge create_edge(const StrokeSample& sample, const Vector2& direction) noexcept;

    static Vector2 get_direction_from_samples(const std::vector<StrokeSample>& samples, const size_t i) noexcept;

    static std::vector<StrokeMeshNode> create_mesh(const std::vector<StrokeSample>& samples, const std::vector<StrokeEdge>& edges, const Color& color) noexcept;
};