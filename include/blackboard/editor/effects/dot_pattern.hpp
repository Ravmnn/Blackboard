#pragma once

#include <blackboard/rendering/effects/effect.hpp>




namespace bb::editor
{




class DotPatternEffect : public rendering::Effect
{
public:
    rendering::EffectProperty<float> spacing;
    rendering::EffectProperty<float> alt_spacing;
    rendering::EffectProperty<float> radius;
    rendering::EffectProperty<float> alt_radius;
    rendering::EffectProperty<float> alpha_factor;
    rendering::EffectProperty<float> alt_alpha_factor;
    rendering::EffectProperty<float> soft_outline_thickness;
    rendering::EffectProperty<Color> color;
    rendering::EffectProperty<Color> alt_color;
    rendering::EffectProperty<Color> background_color;


    DotPatternEffect() noexcept;


    void update() noexcept override;
};




}