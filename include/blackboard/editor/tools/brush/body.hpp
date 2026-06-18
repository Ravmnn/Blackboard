#pragma once

#include <blackboard/editor/tools/bubble.hpp>



namespace bb::editor
{




class Brush;


class BrushBody : public Bubble
{
public:
    Brush& brush;


    explicit BrushBody(Brush& brush) noexcept;


    void update() noexcept override;


private:
    void update_trail() noexcept override;
    void update_thickness() noexcept override;
    void update_color() noexcept override;
};




}