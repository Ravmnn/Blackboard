#include <blackboard/editor/stroke/trail.hpp>

#include <algorithm>

#include <raymath.h>




using bb::editor::Trail;




Trail::Trail(const StrokePoint& origin, const float decay) noexcept : Stroke({}),
    trail_mesh_generator_(4),
    origin(origin),
    decay(decay)
{}




void Trail::update() noexcept
{
    for (auto& point : points)
        if (Vector2Distance(point.position, origin.position) >= 0)
            point.thickness -= decay;

    points.erase(std::remove_if(points.begin(), points.end(),
        [](const auto& point) { return point.thickness <= 0; }
    ), points.end());

    if (emit)
        points.push_back(origin);
}




void Trail::draw() noexcept
{
    const auto mesh = trail_mesh_generator_.generate_mesh(*this);

    if (mesh)
        trail_renderer_.draw_stroke_mesh(*mesh);
}