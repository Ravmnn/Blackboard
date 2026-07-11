#pragma once

#include <blackboard/rendering/effects/effect.hpp>




namespace bb::editor
{




class SelectionEffect : public rendering::Effect
{
public:
    rendering::EffectProperty<float> spacing;
    rendering::EffectProperty<float> speed;
    rendering::EffectProperty<float> thickness;
    rendering::EffectProperty<float> smoothness;
    rendering::EffectProperty<Color> color;
    rendering::EffectProperty<Color> background_color;


    SelectionEffect() noexcept;


    void update() noexcept override;
};




}