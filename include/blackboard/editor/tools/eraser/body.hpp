#pragma once

#include <blackboard/editor/tools/bubble.hpp>




namespace bb::editor
{




class Eraser;


class EraserBody : public Bubble
{
private:
    static constexpr float BaseThickness = 20;
    static constexpr float ThicknessVariationWhenActive = 3;


public:
    const Eraser& eraser;


    EraserBody(const Eraser& eraser) noexcept;


    void update() noexcept override;


protected:
    void update_trail() noexcept override;
    void update_color() noexcept override;
};




}