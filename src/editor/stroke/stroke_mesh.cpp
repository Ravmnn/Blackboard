#include <blackboard/editor/stroke/stroke_mesh.hpp>

#include <algorithm>

#include <raymath.h>




using bb::editor::StrokeMesh,
    bb::editor::StrokePointInterpolation,
    bb::editor::StrokeSample,
    bb::editor::StrokeEdge,
    bb::editor::StrokeMeshNode,
    bb::editor::StrokeMeshQuad,
    bb::editor::StrokeMeshCapSegment;




StrokePointInterpolation::StrokePointInterpolation(const std::vector<StrokePoint>& points, const int i) noexcept :
    last_point(points[i - 1]),
    origin_point(points[i]),
    next_point(points[i + 1]),
    after_next_point(points[i + 2])
{}




StrokeSample::StrokeSample(const StrokePointInterpolation& segment, const int index, const int max_index) noexcept :
    interpolation(segment),
    index(index),
    max_index(max_index),
    position(segment.position(t())),
    thickness(segment.thickness(t())),
    color(segment.color(t())),
    outline_thickness(segment.outline_thickness(t())),
    outline_color(segment.outline_color(t())),
    curvature(calculate_curvature())
{}


float StrokeSample::calculate_curvature() const noexcept
{
    const Vector2 previous = interpolation.position((float)(index - 1) / (float)max_index);
    const Vector2 next = interpolation.position((float)(index + 1) / (float)max_index);

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




void StrokeMesh::set_color(const Color& color) noexcept
{
    for (auto& node : *this)
        node.sample.color = color;
}


void StrokeMesh::set_alpha(const uint8_t alpha) noexcept
{
    for (auto& node : *this)
        node.sample.color.a = alpha;
}