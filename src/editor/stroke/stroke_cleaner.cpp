#include <blackboard/editor/stroke/stroke_cleaner.hpp>

#include <raymath.h>




using
bb::editor::Stroke,
bb::editor::StrokeCleaner;




Stroke StrokeCleaner::clean(const Stroke& stroke) noexcept
{
    Stroke clean_stroke = remove_close_points(stroke);
    uniform_point_distances(clean_stroke);

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


void StrokeCleaner::uniform_point_distances(Stroke& stroke) const noexcept
{
    if (stroke.points.empty())
        return;

    const float average_distance_between_points = get_average_distance(stroke);

    for (size_t pass = 0; pass < passes; pass++)
        for (size_t i = 1; i < stroke.points.size() - 1; i++)
        {
            Vector2& previous = stroke.points[i - 1].position;
            Vector2& current = stroke.points[i].position;
            Vector2& next = stroke.points[i + 1].position;
            const float distance = Vector2Distance(previous, current);
            const float difference = std::abs(average_distance_between_points - distance) * uniformization_strength / 5;

            if (distance > average_distance_between_points)
                current = Vector2MoveTowards(current, previous, difference);

            else if (distance < average_distance_between_points)
                current = Vector2MoveTowards(current, next, difference);
        }
}


float StrokeCleaner::get_average_distance(const Stroke& stroke) noexcept
{
    float average_distance_between_points = 0;

    for (size_t i = 1; i < stroke.points.size(); i++)
    {
        const Vector2 previous = stroke.points[i - 1];
        const Vector2 current = stroke.points[i];

        average_distance_between_points += Vector2Distance(previous, current);
    }

    average_distance_between_points /= (float)stroke.points.size();

    return average_distance_between_points;
}