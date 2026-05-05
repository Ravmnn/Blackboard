#pragma once

#include <blackboard/editor/stroke.hpp>

#include <raymath.h>




class StrokeRenderer
{
private:
    static constexpr float DirectionEpsilon = 0.0001f;
    static constexpr float DebugCircleRadius = 2;
    static constexpr int CapResolution = 32;


    struct Sample
    {
        Vector2 position;
        float thickness;
    };


    struct SplineSegment
    {
        Vector2 p0, p1, p2, p3;
        float current_thickness, next_thickness;


        SplineSegment(const std::vector<StrokePoint>& points, const int i);


        Vector2 point(const float t) const noexcept { return GetSplinePointCatmullRom(p0, p1, p2, p3, t); }
        float thickness(const float t) const noexcept { return current_thickness + (next_thickness - current_thickness) * t; }
    };


    struct Edge
    {
        Vector2 top, bottom;


        Edge() = default;

        Edge(const Vector2& position, const Vector2& normal, const float half_thickness) noexcept
            : Edge(position + normal * half_thickness, position - normal * half_thickness) {}

        Edge(const Vector2& top, const Vector2& bottom) noexcept
            : top(top), bottom(bottom) {}
    };


public:
    int samples_per_segment;

    bool should_debug_draw_points = false;
    bool should_debug_draw_samples = false;
    bool should_debug_draw_edges = false;


    StrokeRenderer(const int samples_per_segment) noexcept
        : samples_per_segment(samples_per_segment) {}

    void draw_stroke(const Stroke& stroke) noexcept;


private:
    static void draw_edges(const std::vector<Edge>& edges, const std::vector<Sample>& samples, const Color& color) noexcept;
    static void draw_edges_with_caps(const std::vector<Edge>& edges, const std::vector<Sample>& samples, const Color& color) noexcept;
    static void draw_cap_if_intense_curve(const std::vector<Sample>& samples, const size_t i, const Color& color) noexcept;

    static void draw_extreme_caps(const std::vector<Sample>& samples, const Color& color) noexcept;
    static void draw_cap(const Vector2& center, const Vector2& direction, const float radius, const Color& color) noexcept;

    void draw_debug_visualization(const std::vector<StrokePoint>& points, const std::vector<Sample>& samples, const std::vector<Edge>& edges) noexcept;

    static void debug_draw_points(const std::vector<StrokePoint>& points) noexcept;
    static void debug_draw_samples(const std::vector<Sample>& samples) noexcept;
    static void debug_draw_edges(const std::vector<Edge>& edges) noexcept;

    static float stroke_curvature(const Vector2& previous, const Vector2& curent, const Vector2& next) noexcept;

    static std::vector<StrokePoint> add_ghost_points(const std::vector<StrokePoint>& points) noexcept;
    std::vector<Sample> create_samples(const std::vector<StrokePoint>& points) noexcept;
    void add_samples_from_segment(std::vector<StrokeRenderer::Sample>& samples, const StrokeRenderer::SplineSegment& segment, const size_t i);

    static std::vector<Edge> create_edges(const std::vector<Sample>& samples) noexcept;
    static Edge create_edge(const Sample& sample, const Vector2& direction) noexcept;

    static Vector2 get_direction_from_samples(const std::vector<Sample>& samples, const size_t i) noexcept;
};