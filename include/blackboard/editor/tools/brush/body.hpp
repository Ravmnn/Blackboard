#pragma once

#include <blackboard/editor/tools/bubble.hpp>



namespace bb::editor
{




class Brush;


class BrushBody : public Bubble
{
private:
    static constexpr float IdleThicknessVariation = 2;


public:
    Brush& brush;


    explicit BrushBody(Brush& brush) noexcept;


    void update() noexcept override;


private:
    void update_trail() noexcept override;
    void update_thickness() noexcept override;
    void update_color() noexcept override;


    void on_editor_environment_changed() noexcept;
};




}