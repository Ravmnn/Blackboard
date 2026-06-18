#pragma once

#include <blackboard/editor/tools/bubble.hpp>




namespace bb::editor
{




class Eraser;


class EraserBody : public Bubble
{
public:
    const Eraser& eraser;


    EraserBody(const Eraser& eraser) noexcept;


    void update() noexcept override;


protected:
    void update_trail() noexcept override;
    void update_color() noexcept override;
};




}