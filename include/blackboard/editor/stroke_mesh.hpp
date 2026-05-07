#pragma once

#include <algorithm>

#include <blackboard/editor/stroke.hpp>




class StrokeSplineSegment
{
    Vector2 previous_, current_, next_, after_next_;
    float current_thickness, next_thickness;
    float curvature_;


public:
    StrokeSplineSegment() = default;

    StrokeSplineSegment(const std::vector<StrokePoint>& points, const int i) noexcept :
        previous_(points[i - 1].position),
        current_(points[i].position),
        next_(points[i + 1].position),
        after_next_(points[i + 2].position),

        current_thickness(points[i].thickness),
        next_thickness(points[i + 1].thickness)
    {
        curvature_ = calculate_curvature();
    }


    StrokePoint stroke_point() const noexcept { return StrokePoint(current_, current_thickness); }

    const Vector2& last() const noexcept { return previous_; }
    const Vector2& current() const noexcept { return current_; }
    const Vector2& next() const noexcept { return next_; }
    const Vector2& after_next() const noexcept { return after_next_; }

    Vector2 point(const float t) const noexcept { return GetSplinePointCatmullRom(previous_, current_, next_, after_next_, t); }
    float thickness(const float t) const noexcept { return current_thickness + (next_thickness - current_thickness) * t; }

    float curvature() const noexcept { return curvature_; }


    float calculate_curvature() const noexcept
    {
        const Vector2 d1 = Vector2Normalize(current_ - previous_);
        const Vector2 d2 = Vector2Normalize(next_ - current_);

        float dot = Vector2DotProduct(d1, d2);
        dot = std::clamp(dot, -1.0f, 1.0f);

        return acosf(dot);
    }
};




class StrokeSample
{
    StrokeSplineSegment segment_;
    Vector2 position_;
    float thickness_;


public:
    StrokeSample() = default;

    StrokeSample(const StrokeSplineSegment& segment, const float t) noexcept
        : segment_(segment), position_(segment.point(t)), thickness_(segment.thickness(t)) {}


    const StrokeSplineSegment& segment() const noexcept { return segment_; }
    const StrokePoint& origin() const noexcept { return segment_.stroke_point(); }
    const Vector2& position() const noexcept { return position_; }
    float thickness() const noexcept { return thickness_; }
    float curvature() const noexcept { return segment_.curvature(); }
};




class StrokeEdge
{
    Vector2 top_, bottom_;
    Vector2 normal_;


public:
    StrokeEdge() = default;

    StrokeEdge(const Vector2& position, const Vector2& normal, const float half_thickness) noexcept
        : StrokeEdge(position + normal * half_thickness, position - normal * half_thickness) {}

    StrokeEdge(const Vector2& top, const Vector2& bottom) noexcept
        : top_(top), bottom_(bottom), normal_(Vector2Normalize(top - bottom / 2)) {}


    const Vector2& top() const noexcept { return top_; }
    const Vector2& bottom() const noexcept { return bottom_; }
    const Vector2& normal() const noexcept { return normal_; }
};




class StrokeMeshNode
{
    StrokeSample sample_;
    StrokeEdge edge_;


public:
    Color color;


    StrokeMeshNode() = default;

    StrokeMeshNode(const StrokeSample& sample, const StrokeEdge& edge, const Color& color) noexcept
        : sample_(sample), edge_(edge), color(color) {}



    const StrokeSample& sample() const noexcept { return sample_; }
    const StrokeEdge& edge() const noexcept { return edge_; }
    float curvature() const noexcept { return sample_.curvature(); }
    const Vector2& normal() const noexcept { return edge_.normal(); }

    const Vector2& position() const noexcept { return sample_.position(); }
    const float thickness() const noexcept { return sample_.thickness(); }
};


using StrokeMesh = std::vector<StrokeMeshNode>;