#pragma once

#include <cstdint>
#include <algorithm>

#include <blackboard/editor/stroke.hpp>




namespace bb::editor
{




class StrokeSplineSegment
{
    Vector2 previous_, current_, next_, after_next_;
    float current_thickness, next_thickness;


public:
    StrokeSplineSegment() = default;

    StrokeSplineSegment(const std::vector<StrokePoint>& points, const int i) noexcept :
        previous_(points[i - 1].position),
        current_(points[i].position),
        next_(points[i + 1].position),
        after_next_(points[i + 2].position),

        current_thickness(points[i].thickness),
        next_thickness(points[i + 1].thickness)
    {}


    [[nodiscard]] StrokePoint stroke_point() const noexcept { return {current_, current_thickness}; }

    [[nodiscard]] const Vector2& last() const noexcept { return previous_; }
    [[nodiscard]] const Vector2& current() const noexcept { return current_; }
    [[nodiscard]] const Vector2& next() const noexcept { return next_; }
    [[nodiscard]] const Vector2& after_next() const noexcept { return after_next_; }

    [[nodiscard]] Vector2 point(const float t) const noexcept { return GetSplinePointCatmullRom(previous_, current_, next_, after_next_, t); }
    [[nodiscard]] float thickness(const float t) const noexcept { return current_thickness + (next_thickness - current_thickness) * t; }
    [[nodiscard]] float half_thickness(const float t) const noexcept { return thickness(t) / 2; }
};




class StrokeSample
{
    StrokeSplineSegment segment_;
    int index_;
    int max_index_;

    Vector2 position_;
    float thickness_;
    float curvature_;


public:
    StrokeSample() = default;

    StrokeSample(const StrokeSplineSegment& segment, const int index, const int max_index) noexcept :
        segment_(segment),
        index_(index),
        max_index_(max_index),
        position_(segment.point(t())),
        thickness_(segment.thickness(t()))
    {
        curvature_ = calculate_curvature();
    }


    [[nodiscard]] const StrokeSplineSegment& segment() const noexcept { return segment_; }
    [[nodiscard]] int index() const noexcept { return index_; }
    [[nodiscard]] int max_index() const noexcept { return max_index_; }
    [[nodiscard]] float t() const noexcept { return (float)index_ / (float)max_index_; }
    [[nodiscard]] StrokePoint origin() const noexcept { return segment_.stroke_point(); }

    [[nodiscard]] const Vector2& position() const noexcept { return position_; }
    [[nodiscard]] float thickness() const noexcept { return thickness_; }
    [[nodiscard]] float half_thickness() const noexcept { return thickness_ / 2; }
    [[nodiscard]] float curvature() const noexcept { return curvature_; }


    [[nodiscard]] float calculate_curvature() const noexcept
    {
        const Vector2 previous = segment_.point((float)(index_ - 1) / (float)max_index_);
        const Vector2 next = segment_.point((float)(index_ + 1) / (float)max_index_);

        return calculate_curvature(previous, position_, next);
    }


    static float calculate_curvature(const Vector2& previous, const Vector2& current, const Vector2& next) noexcept
    {
        const Vector2 d1 = Vector2Normalize(current - previous);
        const Vector2 d2 = Vector2Normalize(next - current);

        float dot = Vector2DotProduct(d1, d2);
        dot = std::clamp(dot, -1.0f, 1.0f);

        return acosf(dot);
    }
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


    [[nodiscard]] const Vector2& top() const noexcept { return top_; }
    [[nodiscard]] const Vector2& bottom() const noexcept { return bottom_; }
    [[nodiscard]] const Vector2& normal() const noexcept { return normal_; }
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



    [[nodiscard]] const StrokeSample& sample() const noexcept { return sample_; }
    [[nodiscard]] const StrokeEdge& edge() const noexcept { return edge_; }
    [[nodiscard]] float curvature() const noexcept { return sample_.curvature(); }
    [[nodiscard]] const Vector2& normal() const noexcept { return edge_.normal(); }

    [[nodiscard]] const Vector2& position() const noexcept { return sample_.position(); }
    [[nodiscard]] float thickness() const noexcept { return sample_.thickness(); }
    [[nodiscard]] float half_thickness() const noexcept { return sample_.half_thickness(); }
};


class StrokeMesh : public std::vector<StrokeMeshNode>
{
public:
    using std::vector<StrokeMeshNode>::vector;


    void set_color(const Color& color) noexcept;
    void set_alpha(uint8_t alpha) noexcept;
};




}