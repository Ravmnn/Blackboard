#pragma once

#include <cstdint>

#include <blackboard/editor/stroke/stroke.hpp>




namespace bb::editor
{



// TODO: no raw getters, make fields public

class StrokeSplineSegment
{
private:
    Vector2 previous_, current_, next_, after_next_;
    float current_thickness, next_thickness;


public:
    StrokeSplineSegment() = default;

    StrokeSplineSegment(const std::vector<StrokePoint>& points, int i) noexcept;


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
private:
    StrokeSplineSegment segment_;
    int index_;
    int max_index_;

    Vector2 position_;
    float thickness_;
    float curvature_;


public:
    StrokeSample() = default;

    StrokeSample(const StrokeSplineSegment& segment, int index, int max_index) noexcept;


    [[nodiscard]] const StrokeSplineSegment& segment() const noexcept { return segment_; }
    [[nodiscard]] int index() const noexcept { return index_; }
    [[nodiscard]] int max_index() const noexcept { return max_index_; }
    [[nodiscard]] float t() const noexcept { return (float)index_ / (float)max_index_; }
    [[nodiscard]] StrokePoint origin() const noexcept { return segment_.stroke_point(); }

    [[nodiscard]] const Vector2& position() const noexcept { return position_; }
    [[nodiscard]] float thickness() const noexcept { return thickness_; }
    [[nodiscard]] float half_thickness() const noexcept { return thickness_ / 2; }
    [[nodiscard]] float curvature() const noexcept { return curvature_; }


    [[nodiscard]] float calculate_curvature() const noexcept;

    static float calculate_curvature(const Vector2& previous, const Vector2& current, const Vector2& next) noexcept;
};




class StrokeEdge
{
private:
    Vector2 top_, bottom_;
    Vector2 normal_;


public:
    StrokeEdge() = default;

    StrokeEdge(const Vector2& position, const Vector2& normal, float half_thickness) noexcept;
    StrokeEdge(const Vector2& top, const Vector2& bottom) noexcept;


    [[nodiscard]] const Vector2& top() const noexcept { return top_; }
    [[nodiscard]] const Vector2& bottom() const noexcept { return bottom_; }
    [[nodiscard]] const Vector2& normal() const noexcept { return normal_; }
};




class StrokeMeshNode
{
private:
    StrokeSample sample_;
    StrokeEdge edge_;


public:
    Color color;


    StrokeMeshNode() = default;
    StrokeMeshNode(const StrokeSample& sample, const StrokeEdge& edge, const Color& color) noexcept;


    [[nodiscard]] const StrokeSample& sample() const noexcept { return sample_; }
    [[nodiscard]] const StrokeEdge& edge() const noexcept { return edge_; }
    [[nodiscard]] float curvature() const noexcept { return sample_.curvature(); }
    [[nodiscard]] const Vector2& normal() const noexcept { return edge_.normal(); }

    [[nodiscard]] const Vector2& position() const noexcept { return sample_.position(); }
    [[nodiscard]] float thickness() const noexcept { return sample_.thickness(); }
    [[nodiscard]] float half_thickness() const noexcept { return sample_.half_thickness(); }
};


class StrokeMeshQuad
{
private:
    StrokeMeshNode first_;
    StrokeMeshNode second_;


public:
    StrokeMeshQuad(const StrokeMeshNode& first, const StrokeMeshNode& second) noexcept;


    [[nodiscard]] const Vector2& top() const noexcept { return first_.edge().top(); }
    [[nodiscard]] const Vector2& bottom() const noexcept { return first_.edge().bottom(); }
    [[nodiscard]] const Vector2& next_top() const noexcept { return second_.edge().top(); }
    [[nodiscard]] const Vector2& next_bottom() const noexcept { return second_.edge().bottom(); }

    [[nodiscard]] const Color& color() const noexcept { return first_.color; }
};


class StrokeMeshCapSegment
{
private:
    Vector2 center_;
    Vector2 begin_;
    Vector2 end_;
    Color color_;


public:
    StrokeMeshCapSegment(const Vector2& center, const Vector2& begin, const Vector2& end, const Color& color) noexcept;


    [[nodiscard]] const Vector2& center() const noexcept { return center_; }
    [[nodiscard]] const Vector2& begin() const noexcept { return begin_; }
    [[nodiscard]] const Vector2& end() const noexcept { return end_; }
    [[nodiscard]] const Color& color() const noexcept { return color_; }
};


class StrokeMesh : public std::vector<StrokeMeshNode>
{
public:
    using std::vector<StrokeMeshNode>::vector;


    void set_color(const Color& color) noexcept;
    void set_alpha(uint8_t alpha) noexcept;
};




}