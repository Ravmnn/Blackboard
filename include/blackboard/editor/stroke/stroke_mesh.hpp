#pragma once

#include <cstdint>

#include <blackboard/editor/stroke/stroke.hpp>




namespace bb::editor
{




class StrokeSplineSegment
{
private:
    float current_thickness_, next_thickness_;


public:
    Vector2 last, current, next, after_next;


    StrokeSplineSegment() = default;
    StrokeSplineSegment(const std::vector<StrokePoint>& points, int i) noexcept;


    [[nodiscard]] StrokePoint stroke_point() const noexcept { return {current, current_thickness_}; }

    [[nodiscard]] Vector2 point(const float t) const noexcept { return GetSplinePointCatmullRom(last, current, next, after_next, t); }
    [[nodiscard]] float thickness(const float t) const noexcept { return current_thickness_ + (next_thickness_ - current_thickness_) * t; }
    [[nodiscard]] float half_thickness(const float t) const noexcept { return thickness(t) / 2; }
};




class StrokeSample
{
public:
    StrokeSplineSegment segment;
    int index;
    int max_index;

    Vector2 position;
    float thickness;
    float curvature;


    StrokeSample() = default;
    StrokeSample(const StrokeSplineSegment& segment, int index, int max_index) noexcept;


    [[nodiscard]] float t() const noexcept { return (float)index / (float)max_index; }
    [[nodiscard]] StrokePoint origin() const noexcept { return segment.stroke_point(); }

    [[nodiscard]] float half_thickness() const noexcept { return thickness / 2; }


    [[nodiscard]] float calculate_curvature() const noexcept;

    static float calculate_curvature(const Vector2& previous, const Vector2& current, const Vector2& next) noexcept;
};




class StrokeEdge
{
public:
    Vector2 top, bottom;
    Vector2 normal;


    StrokeEdge() = default;

    StrokeEdge(const Vector2& position, const Vector2& normal, float half_thickness) noexcept;
    StrokeEdge(const Vector2& top, const Vector2& bottom) noexcept;
};




class StrokeMeshNode
{
public:
    StrokeSample sample;
    StrokeEdge edge;

    Color color;


    StrokeMeshNode() = default;
    StrokeMeshNode(const StrokeSample& sample, const StrokeEdge& edge, const Color& color) noexcept;


    [[nodiscard]] float curvature() const noexcept { return sample.curvature; }
    [[nodiscard]] const Vector2& normal() const noexcept { return edge.normal; }

    [[nodiscard]] const Vector2& position() const noexcept { return sample.position; }
    [[nodiscard]] float thickness() const noexcept { return sample.thickness; }
    [[nodiscard]] float half_thickness() const noexcept { return sample.half_thickness(); }
};


class StrokeMeshQuad
{
public:
    StrokeMeshNode first;
    StrokeMeshNode second;


    StrokeMeshQuad(const StrokeMeshNode& first, const StrokeMeshNode& second) noexcept;


    [[nodiscard]] const Vector2& top() const noexcept { return first.edge.top; }
    [[nodiscard]] const Vector2& bottom() const noexcept { return first.edge.bottom; }
    [[nodiscard]] const Vector2& next_top() const noexcept { return second.edge.top; }
    [[nodiscard]] const Vector2& next_bottom() const noexcept { return second.edge.bottom; }

    [[nodiscard]] const Color& color() const noexcept { return first.color; }
};


class StrokeMeshCapSegment
{
public:
    Vector2 center;
    Vector2 begin;
    Vector2 end;
    Color color;


    StrokeMeshCapSegment(const Vector2& center, const Vector2& begin, const Vector2& end, const Color& color) noexcept;
};


class StrokeMesh : public std::vector<StrokeMeshNode>
{
public:
    using std::vector<StrokeMeshNode>::vector;


    void set_color(const Color& color) noexcept;
    void set_alpha(uint8_t alpha) noexcept;
};




}