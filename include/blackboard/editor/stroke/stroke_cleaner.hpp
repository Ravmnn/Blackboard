#pragma once

#include <blackboard/editor/stroke/stroke.hpp>




namespace bb::editor
{




class StrokeCleaner
{
public:
    float minimum_distance = 15;
    float uniformization_strength = 2;
    uint16_t passes = 2;


    Stroke clean(const Stroke& stroke) noexcept;


private:
    [[nodiscard]] Stroke remove_close_points(const Stroke& stroke) const noexcept;
    void uniform_point_distances(Stroke& stroke) const noexcept;
    static float get_average_distance(const Stroke& stroke) noexcept;
};




}