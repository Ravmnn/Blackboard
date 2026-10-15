#include <blackboard/editor/stroke/stroke_cleaner.hpp>

#include <raymath.h>




using
bb::editor::Stroke,
bb::editor::StrokeCleaner;




Stroke StrokeCleaner::clean(const Stroke& stroke) noexcept
{
    Stroke clean_stroke = remove_close_points(stroke);

    return clean_stroke;
}


Stroke StrokeCleaner::remove_close_points(const Stroke& stroke) const noexcept
{
    Stroke clean_stroke{};
    clean_stroke.points.reserve(stroke.points.size());

    for (size_t i = 0; i < stroke.points.size(); i++)
    {
        const StrokePoint& point = stroke.points[i];

        if (clean_stroke.points.empty() || i + 1 >= stroke.points.size() || Vector2Distance(clean_stroke.points.back().position, point.position) >= minimum_distance)
            clean_stroke.points.push_back(point);
    }

    return clean_stroke;
}