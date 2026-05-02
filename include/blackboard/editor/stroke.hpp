#pragma once

#include <initializer_list>
#include <vector>

#include <raylib.h>




struct StrokePoint
{
    Vector2 position;
    float thickness;


    StrokePoint(const Vector2& position, const float thickness)
        : position(position), thickness(thickness) {}
};


class Stroke
{
public:
    std::vector<StrokePoint> points;
    Color color;


    Stroke(const std::initializer_list<StrokePoint>& points, const Color& color)
        : points(points), color(color) {}
};