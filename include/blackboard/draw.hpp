#pragma once

#include <cstdint>

#include <vector>

#include <blackboard/math/rect.hpp>

#include <raymath.h>




namespace bb
{




struct SectionTriangle
{
    Vector2 center;
    Vector2 current;
    Vector2 next;
};


class Draw
{
public:
    static void rounded_rectangle(const Rectangle& rectangle, const float radius, const Color& color = WHITE, const uint32_t resolution = 32)
    {
        rounded_rectangle({ rectangle.x, rectangle.y }, { rectangle.width, rectangle.height }, radius, color, resolution);
    }


    static void rounded_rectangle_outline(const Rectangle& rectangle, const float radius, const float thickness, const Color& color = WHITE, const uint32_t resolution = 32)
    {
        rounded_rectangle_outline({ rectangle.x, rectangle.y }, { rectangle.width, rectangle.height }, radius, thickness, color, resolution);
    }


    static void rounded_rectangle(const Vector2& position, const Vector2& size, const float radius, const Color& color = WHITE, const uint32_t resolution = 32)
    {
        const float normalized_radius = math::Rect::get_normalized_radius(size, radius);
        DrawRectangleRounded({ position.x, position.y, size.x, size.y }, normalized_radius, (int)resolution, color);
    }


    static void rounded_rectangle_outline(const Vector2& position, const Vector2& size, const float radius, const float thickness, const Color& color = WHITE, const uint32_t resolution = 32)
    {
        const float normalized_radius = math::Rect::get_normalized_radius(size, radius);
        DrawRectangleRoundedLinesEx({ position.x, position.y, size.x, size.y }, normalized_radius, (int)resolution, thickness, color);
    }




    static void stretched_ellipse(const Vector2& center, const float radius, const float stretch, const Color& color = WHITE, const uint32_t resolution = 32) noexcept
    {
        ellipse(center, radius + stretch, radius, color, resolution);
    }


    static void stretched_ellipse_outline(const Vector2& center, const float radius, const float stretch, const float thickness, const Color& color = WHITE, const uint32_t resolution = 32) noexcept
    {
        ellipse_outline(center, radius + stretch, radius, thickness, color, resolution);
    }




    static void ellipse(const Vector2& center, const float radius_x, const float radius_y, const Color& color = WHITE, const uint32_t resolution = 32) noexcept
    {
        for (size_t i = 0; i < resolution; i++)
            draw_triangle(calculate_ellipse_triangle(center, radius_x, radius_y, resolution, i), color);
    }


    static void ellipse_outline(const Vector2& center, const float radius_x, const float radius_y, const float thickness, const Color& color = WHITE, const uint32_t resolution = 32) noexcept
    {
        std::vector<SectionTriangle> triangles;
        triangles.reserve(resolution);

        for (size_t i = 0; i < resolution; i++)
            triangles.push_back(calculate_ellipse_triangle(center, radius_x, radius_y, resolution, i));

        draw_spline_outline(triangles, thickness, color);
    }




    static void circle(const Vector2& center, const float radius, const Color& color, const uint32_t resolution = 32) noexcept
    {
        circle_section(center, radius, 0, 360, color, resolution);
    }


    static void circle_outline(const Vector2& center, const float radius, const float thickness, const Color& color, const uint32_t resolution = 32) noexcept
    {
        circle_section_outline(center, radius, 0, 360, thickness, color, resolution);
    }



    static void circle_section(const Vector2& center, const float radius, const float start_angle, const float end_angle, const Color& color, const uint32_t resolution = 32) noexcept
    {
        const float angle_step = calculate_circle_section_angle_step(start_angle, end_angle, resolution);

        for (size_t i = 0; i < resolution; i++)
            draw_triangle(calculate_circle_section_triangle(center, radius, start_angle, angle_step, i), color);
    }


    static void circle_section_outline(const Vector2& center, const float radius, const float start_angle, const float end_angle, const float thickness, const Color& color, const uint32_t resolution = 32) noexcept
    {
        const float angle_step = calculate_circle_section_angle_step(start_angle, end_angle, resolution);

        std::vector<SectionTriangle> triangles;
        triangles.reserve(resolution);

        for (size_t i = 0; i < resolution; i++)
            triangles.push_back(calculate_circle_section_triangle(center, radius, start_angle, angle_step, i));

        draw_spline_outline(triangles, thickness, color);
    }








    static std::vector<SectionTriangle> calculate_circle_section_triangles(const Vector2& center, const float radius, const uint32_t resolution = 32) noexcept
    {
        const float angle_step = calculate_circle_section_angle_step(0, 360, resolution);

        std::vector<SectionTriangle> vertices;
        vertices.reserve(resolution);

        for (size_t i = 0; i < resolution; i++)
            vertices.push_back(calculate_circle_section_triangle(center, radius, 0, angle_step, i));

        return vertices;
    }


    static SectionTriangle calculate_circle_section_triangle(const Vector2& center, const float radius, const float start_angle, const float angle_step, const size_t i)
    {
        const auto fi = (float)i;
        const float current_angle = start_angle + fi * angle_step;
        const float next_angle = (float)start_angle + (fi + 1) * angle_step;

        const Vector2 current_point = center + Vector2{ cosf(current_angle) * radius, sinf(current_angle) * radius };
        const Vector2 next_point = center + Vector2{ cosf(next_angle) * radius, sinf(next_angle) * radius };

        return SectionTriangle{ .center = center, .current = current_point, .next = next_point };
    }


    static float calculate_circle_section_angle_step(const float start_angle, const float end_angle, const uint32_t resolution = 32) noexcept
    {
        const auto angle_distance_in_rads = (float)((end_angle - start_angle) * M_PI / 180.0);
        return angle_distance_in_rads / (float)resolution;
    }




    static SectionTriangle calculate_ellipse_triangle(const Vector2& center, const float radius_x, const float radius_y, const uint32_t resolution, const size_t i) noexcept
    {
        const float angle1 = (2.0f * PI * (float)i) / (float)resolution;
        const float angle2 = (2.0f * PI * (float)(i + 1)) / (float)resolution;

        const Vector2 p1 = {
            center.x + cosf(angle1) * radius_x,
            center.y + sinf(angle1) * radius_y
        };

        const Vector2 p2 = {
            center.x + cosf(angle2) * radius_x,
            center.y + sinf(angle2) * radius_y
        };

        return SectionTriangle{ .center = center, .current = p1, .next = p2 };
    }




    static void draw_triangle(const SectionTriangle& triangle, const Color& color) noexcept
    {
        DrawTriangle(triangle.next, triangle.current, triangle.center, color);
    }


    static void draw_outline(const Vector2& start, const Vector2& end, const float thickness, const Color& color) noexcept
    {
        DrawLineEx(start, end, thickness, color);
    }


    static void draw_spline_outline(const std::vector<SectionTriangle>& triangles, const float thickness, const Color& color) noexcept
    {
        if (triangles.size() < 2)
            return;

        for (size_t i = 0; i < triangles.size(); i++)
        {
            const SectionTriangle triangle = triangles[i];
            const Vector2 last = i > 0 ? triangles[i - 1].current : triangles[triangles.size() - 1].current;
            const Vector2 next = i < triangles.size() - 1 ? triangles[i + 1].next : triangles[0].next;

            DrawSplineSegmentCatmullRom(last, triangle.current, triangle.next, next, thickness, color);
        }
    }
};




}