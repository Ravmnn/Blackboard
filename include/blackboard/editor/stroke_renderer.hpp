#pragma once

#include <blackboard/editor/stroke_mesh_generator.hpp>

#include <raymath.h>




class StrokeRenderer
{
private:
    static constexpr float DebugCircleRadius = 2;


public:
    bool should_debug_draw_points = false;
    bool should_debug_draw_samples = false;
    bool should_debug_draw_edges = false;

    const StrokeMeshGenerator& sampler;


    explicit StrokeRenderer(const StrokeMeshGenerator& sampler) noexcept : sampler(sampler) {}


    void draw_stroke(const Stroke& stroke) noexcept;
    void draw_stroke_mesh(const std::vector<StrokeMeshNode>& mesh) noexcept;


private:
    static void draw_edges(const std::vector<StrokeMeshNode>& mesh) noexcept;
    static void draw_edges_with_caps(const std::vector<StrokeMeshNode>& mesh) noexcept;
    static void draw_cap_if_intense_curve(const std::vector<StrokeMeshNode>& mesh, const size_t i) noexcept;

    static void draw_extreme_caps(const std::vector<StrokeMeshNode>& mesh) noexcept;
    static void draw_cap(const Vector2& center, const Vector2& direction, const float radius, const Color& color) noexcept;

    void draw_debug_visualization(const std::vector<StrokeMeshNode>& mesh) noexcept;

    static void debug_draw_points(const std::vector<StrokeMeshNode>& mesh) noexcept;
    static void debug_draw_samples(const std::vector<StrokeMeshNode>& mesh) noexcept;
    static void debug_draw_edges(const std::vector<StrokeMeshNode>& mesh) noexcept;
};