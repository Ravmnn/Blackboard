#include <blackboard/editor/stroke/stroke_mesh.hpp>

#include <algorithm>




using
bb::editor::StrokePointInterpolation,
bb::editor::StrokeSample,
bb::editor::StrokeEdge,
bb::editor::StrokeMeshNode,
bb::editor::StrokeMeshQuad,
bb::editor::StrokeMesh,
bb::editor::StrokeMeshCapSegment;




StrokePointInterpolation::StrokePointInterpolation(const std::vector<StrokePoint>& points, const int i) noexcept :
    last_point(points[i - 1]),
    origin_point(points[i]),
    next_point(points[i + 1]),
    after_next_point(points[i + 2])
{}




StrokeSample::StrokeSample(const Vector2& position, const float thickness, const Color& color, const float outline_thickness, const Color& outline_color) noexcept :
    position(position),
    thickness(thickness),
    color(color),
    outline_thickness(outline_thickness),
    outline_color(outline_color)
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
    const Vector2 a = current - previous;
    const Vector2 b = next - current;

    const float la2 = a.x*a.x + a.y*a.y;
    const float lb2 = b.x*b.x + b.y*b.y;

    if (la2 < 1e-12f || lb2 < 1e-12f)
        return 0.0f;   // segmento degenerado

    const float cross = a.x * b.y - a.y * b.x;       // ∝ sen(θ)
    const float dot   = a.x * b.x + a.y * b.y;       // ∝ cos(θ)

    const float signedAngle = atan2f(cross, dot);    // (-π, π]
    const float turn        = fabsf(signedAngle);    // [0, π]

    return turn;
}




StrokeEdge::StrokeEdge(const Vector2& position, const Vector2& normal, const float half_thickness) noexcept
    : StrokeEdge(position + normal * half_thickness, position - normal * half_thickness)
{}


StrokeEdge::StrokeEdge(const Vector2& top, const Vector2& bottom) noexcept :
    top(top),
    bottom(bottom),
    normal(Vector2Normalize((top - bottom) / 2))
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