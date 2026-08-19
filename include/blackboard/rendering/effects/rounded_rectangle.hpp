#pragma once

#include <blackboard/rendering/effects/effect.hpp>




namespace bb::rendering
{




class RoundedRectangleEffect : public rendering::Effect
{
public:
    rendering::EffectProperty<Vector2> position;
    rendering::EffectProperty<Vector2> size;
    rendering::EffectProperty<float> radius;
    rendering::EffectProperty<Color> color;
    rendering::EffectProperty<Color> outline_color;
    rendering::EffectProperty<float> outline_thickness;
    rendering::EffectProperty<float> antialiasing;


    RoundedRectangleEffect() noexcept;


    void update() noexcept override;
};




}