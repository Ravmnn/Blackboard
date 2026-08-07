#pragma once

#include <cstdint>

#include <blackboard/animation/interpolate.hpp>
#include <blackboard/editor/stroke/stroke.hpp>




namespace bb::editor
{




class StrokePointInterpolation
{
public:
    StrokePoint last_point, origin_point, next_point, after_next_point;


    StrokePointInterpolation() = default;
    StrokePointInterpolation(const std::vector<StrokePoint>& points, int i) noexcept;


    [[nodiscard]] Vector2 position(const float t) const noexcept {
        return GetSplinePointCatmullRom(last_point.position, origin_point.position, next_point.position, after_next_point.position, t);
    }

    [[nodiscard]] float thickness(const float t) const noexcept {
        return animation::Interpolate::linear(origin_point.thickness, next_point.thickness, t);
    }

    [[nodiscard]] float outline_thickness(const float t) const noexcept {
        return animation::Interpolate::linear(origin_point.outline_thickness, next_point.outline_thickness, t);
    }

    [[nodiscard]] Color color(const float t) const noexcept {
        return animation::Interpolate::linear(origin_point.color, next_point.color, t);
    }

    [[nodiscard]] Color outline_color(const float t) const noexcept {
        return animation::Interpolate::linear(origin_point.outline_color, next_point.outline_color, t);
    }

    [[nodiscard]] float half_thickness(const float t) const noexcept { return thickness(t) / 2; }
};




class StrokeSample
{
public:
    StrokePointInterpolation interpolation;
    int index;
    int max_index;

    Vector2 position;
    float thickness;
    Color color;
    float outline_thickness = 0;
    Color outline_color = WHITE;

    float curvature;
    bool is_begin = false;
    bool is_end = false;


    StrokeSample() = default;
    StrokeSample(const StrokePointInterpolation& segment, int index, int max_index) noexcept;


    [[nodiscard]] float t() const noexcept { return (float)index / (float)max_index; }

    [[nodiscard]] float half_thickness() const noexcept { return thickness / 2; }
    [[nodiscard]] bool is_extremity() const noexcept { return is_begin || is_end; }


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


    [[nodiscard]] const StrokePointInterpolation& interpolation() const noexcept { return sample.interpolation; }

    [[nodiscard]] bool is_extremity() const noexcept { return sample.is_extremity(); }
    [[nodiscard]] bool is_begin() const noexcept { return sample.is_begin; }
    [[nodiscard]] bool is_end() const noexcept { return sample.is_end; }

    [[nodiscard]] float curvature() const noexcept { return sample.curvature; }

    [[nodiscard]] Vector2 forward_direction() const noexcept { return { edge.normal.y, -edge.normal.x }; }
    [[nodiscard]] Vector2 backward_direction() const noexcept { return { -edge.normal.y, edge.normal.x }; }
    [[nodiscard]] const Vector2& up_normal() const noexcept { return edge.normal; }
    [[nodiscard]] Vector2 down_normal() const noexcept { return edge.normal * -1; }

    [[nodiscard]] Vector2& position() noexcept { return sample.position; }
    [[nodiscard]] float& thickness() noexcept { return sample.thickness; }
    [[nodiscard]] float& outline_thickness() noexcept { return sample.outline_thickness; }
    [[nodiscard]] Color& color() noexcept { return sample.color; }
    [[nodiscard]] Color& outline_color() noexcept { return sample.outline_color; }

    [[nodiscard]] const Vector2& position() const noexcept { return sample.position; }
    [[nodiscard]] const float& thickness() const noexcept { return sample.thickness; }
    [[nodiscard]] const float& outline_thickness() const noexcept { return sample.outline_thickness; }
    [[nodiscard]] const Color& color() const noexcept { return sample.color; }
    [[nodiscard]] const Color& outline_color() const noexcept { return sample.outline_color; }
    [[nodiscard]] float half_thickness() const noexcept { return sample.half_thickness(); }
};


class StrokeMeshQuad
{
public:
    StrokeMeshNode first;
    StrokeMeshNode second;


    [[nodiscard]] const Vector2& top() const noexcept { return first.edge.top; }
    [[nodiscard]] const Vector2& bottom() const noexcept { return first.edge.bottom; }
    [[nodiscard]] const Vector2& next_top() const noexcept { return second.edge.top; }
    [[nodiscard]] const Vector2& next_bottom() const noexcept { return second.edge.bottom; }

    [[nodiscard]] const Color& color() const noexcept { return first.color(); }
    [[nodiscard]] const Color& outline_color() const noexcept { return first.outline_color(); }
    [[nodiscard]] float outline_thickness() const noexcept { return first.outline_thickness(); }
};


class StrokeMeshCapSegment
{
public:
    Vector2 center;
    Vector2 begin;
    Vector2 end;

    Color color;

    float outline_thickness = 0;
    Color outline_color = WHITE;
};


class StrokeMesh : public std::vector<StrokeMeshNode>
{
public:
    using std::vector<StrokeMeshNode>::vector;


    void set_color(const Color& color) noexcept;
    void set_alpha(uint8_t alpha) noexcept;
};




}