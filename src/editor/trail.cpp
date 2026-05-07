#include <blackboard/editor/trail.hpp>

#include <algorithm>




Trail::Trail(const StrokePoint& origin, const float decay) noexcept : Stroke({}, color),
    trail_mesh_generator_(4), trail_renderer_(trail_mesh_generator_), origin(origin), decay(decay)
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
    trail_renderer_.draw_stroke(*this);
}