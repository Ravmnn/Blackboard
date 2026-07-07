#include <blackboard/editor/stroke/stroke_mesh.hpp>

#include <algorithm>

#include <raymath.h>




using bb::editor::StrokeMesh,
    bb::editor::StrokeSplineSegment,
    bb::editor::StrokeSample,
    bb::editor::StrokeEdge,
    bb::editor::StrokeMeshNode,
    bb::editor::StrokeMeshQuad,
    bb::editor::StrokeMeshCapSegment;




StrokeSplineSegment::StrokeSplineSegment(const std::vector<StrokePoint>& points, const int i) noexcept :
    current_thickness_(points[i].thickness),
    next_thickness_(points[i + 1].thickness),

    last(points[i - 1].position),
    current(points[i].position),
    next(points[i + 1].position),
    after_next(points[i + 2].position)
{}




StrokeSample::StrokeSample(const StrokeSplineSegment& segment, const int index, const int max_index) noexcept :
    segment(segment),
    index(index),
    max_index(max_index),
    position(segment.point(t())),
    thickness(segment.thickness(t())),
    curvature(calculate_curvature())
{}


float StrokeSample::calculate_curvature() const noexcept
{
    const Vector2 previous = segment.point((float)(index - 1) / (float)max_index);
    const Vector2 next = segment.point((float)(index + 1) / (float)max_index);

    return calculate_curvature(previous, position, next);
}


float StrokeSample::calculate_curvature(const Vector2& previous, const Vector2& current, const Vector2& next) noexcept
{
    const Vector2 d1 = Vector2Normalize(current - previous);
    const Vector2 d2 = Vector2Normalize(next - current);

    float dot = Vector2DotProduct(d1, d2);
    dot = std::clamp(dot, -1.0f, 1.0f);

    return acosf(dot);
}




StrokeEdge::StrokeEdge(const Vector2& position, const Vector2& normal, const float half_thickness) noexcept
    : StrokeEdge(position + normal * half_thickness, position - normal * half_thickness)
{}


StrokeEdge::StrokeEdge(const Vector2& top, const Vector2& bottom) noexcept :
    top(top),
    bottom(bottom),
    normal(Vector2Normalize(top - bottom / 2))
{}




StrokeMeshNode::StrokeMeshNode(const StrokeSample& sample, const StrokeEdge& edge, const Color& color) noexcept :
    sample(sample),
    edge(edge),
    color(color)
{}




StrokeMeshQuad::StrokeMeshQuad(const StrokeMeshNode& first, const StrokeMeshNode& second) noexcept :
    first(first),
    second(second)
{}




StrokeMeshCapSegment::StrokeMeshCapSegment(const Vector2& center, const Vector2& begin, const Vector2& end, const Color& color) noexcept :
    center(center),
    begin(begin),
    end(end),
    color(color)
{}




void StrokeMesh::set_color(const Color& color) noexcept
{
    for (auto& node : *this)
        node.color = color;
}


void StrokeMesh::set_alpha(const uint8_t alpha) noexcept
{
    for (auto& node : *this)
        node.color.a = alpha;
}