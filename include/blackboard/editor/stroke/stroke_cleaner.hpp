#pragma once

#include <blackboard/editor/stroke/stroke.hpp>




namespace bb::editor
{




class StrokeCleaner
{
public:
    float minimum_distance = 10;


    Stroke clean(const Stroke& stroke) noexcept;


private:
    [[nodiscard]] Stroke remove_close_points(const Stroke& stroke) const noexcept;
};




}