#include <blackboard/editor/stroke/stroke_mesh.hpp>

#include <algorithm>




using bb::editor::StrokeMesh,
    bb::editor::StrokeSplineSegment,
    bb::editor::StrokeSample,
    bb::editor::StrokeEdge,
    bb::editor::StrokeMeshNode,
    bb::editor::StrokeMeshQuad,
    bb::editor::StrokeMeshCapSegment;




StrokeSplineSegment::StrokeSplineSegment(const std::vector<StrokePoint>& points, const int i) noexcept :
    previous_(points[i - 1].position),
    current_(points[i].position),
    next_(points[i + 1].position),
    after_next_(points[i + 2].position),

    current_thickness(points[i].thickness),
    next_thickness(points[i + 1].thickness)
{}




StrokeSample::StrokeSample(const StrokeSplineSegment& segment, const int index, const int max_index) noexcept :
    segment_(segment),
    index_(index),
    max_index_(max_index),
    position_(segment.point(t())),
    thickness_(segment.thickness(t()))
{
    curvature_ = calculate_curvature();
}


float StrokeSample::calculate_curvature() const noexcept
{
    const Vector2 previous = segment_.point((float)(index_ - 1) / (float)max_index_);
    const Vector2 next = segment_.point((float)(index_ + 1) / (float)max_index_);

    return calculate_curvature(previous, position_, next);
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
    top_(top),
    bottom_(bottom),
    normal_(Vector2Normalize(top - bottom / 2))
{}




StrokeMeshNode::StrokeMeshNode(const StrokeSample& sample, const StrokeEdge& edge, const Color& color) noexcept :
    sample_(sample),
    edge_(edge),
    color(color)
{}




StrokeMeshQuad::StrokeMeshQuad(const StrokeMeshNode& first, const StrokeMeshNode& second) noexcept :
    first_(first),
    second_(second)
{}




StrokeMeshCapSegment::StrokeMeshCapSegment(const Vector2& center, const Vector2& begin, const Vector2& end, const Color& color) noexcept :
    center_(center),
    begin_(begin),
    end_(end),
    color_(color)
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