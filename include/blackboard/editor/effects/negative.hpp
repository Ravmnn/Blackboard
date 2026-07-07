#pragma once

#include <blackboard/rendering/effects/effect.hpp>




namespace bb::editor
{




class NegativeEffect : public rendering::Effect
{
public:
    rendering::EffectProperty<Color> default_color;
    rendering::EffectProperty<float> grayness_threshold;


    NegativeEffect() noexcept;


    void update() noexcept override;
};




}