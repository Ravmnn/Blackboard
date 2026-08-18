#pragma once

#include <memory>

#include <blackboard/editor/stroke/stroke_mesh_gl.hpp>




namespace bb::editor
{




class StrokeMeshGenerator
{
public:
    uint32_t samples_per_segment;
    bool adaptative_samples_per_segment = true;


    explicit StrokeMeshGenerator(const unsigned int samples_per_segment) noexcept
        : samples_per_segment(samples_per_segment) {}


    [[nodiscard]] std::unique_ptr<StrokeMeshGL> generate_mesh_gl(const Stroke& stroke) const noexcept;
    [[nodiscard]] std::unique_ptr<StrokeMesh> generate_mesh(const Stroke& stroke) const noexcept;


private:
    static std::vector<StrokePoint> remove_close_points(const std::vector<StrokePoint>& points) noexcept;
    static std::vector<StrokePoint> add_ghost_points(const std::vector<StrokePoint>& points) noexcept;
    [[nodiscard]] std::vector<StrokeSample> create_samples(const std::vector<StrokePoint>& points) const noexcept;
    [[nodiscard]] unsigned int samples_amount(const std::vector<StrokePoint>& points, size_t i) const noexcept;
    [[nodiscard]] unsigned int calculate_adaptative_samples_amount(const std::vector<StrokePoint>& points, size_t i) const noexcept;
    static float calculate_average_curvature(const std::vector<StrokePoint>& points, size_t i) noexcept;
    static void add_samples_from_segment(std::vector<StrokeSample>& samples, const StrokePointInterpolation& segment, unsigned int samples_amount, size_t i) noexcept;

    static std::vector<StrokeEdge> create_edges(const std::vector<StrokeSample>& samples) noexcept;
    static StrokeEdge create_edge(const StrokeSample& sample, const Vector2& direction) noexcept;

    static Vector2 get_direction_from_samples(const std::vector<StrokeSample>& samples, size_t i) noexcept;

    static std::unique_ptr<StrokeMesh> create_mesh(const std::vector<StrokeSample>& samples, const std::vector<StrokeEdge>& edges) noexcept;
};




}