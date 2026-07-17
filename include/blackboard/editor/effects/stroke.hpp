#pragma once

#include <raylib.h>

#include <blackboard/rendering/effects/effect.hpp>
#include <blackboard/editor/effects/native_shaders.hpp>




namespace bb::editor
{




class StrokeEffect : public rendering::Effect
{
public:
    rendering::EffectProperty<Matrix> mvp;
    rendering::EffectProperty<float> camera_zoom;
    rendering::EffectProperty<float> smoothness;
    rendering::EffectProperty<float> smoothness_min;
    rendering::EffectProperty<float> smoothness_max;
    rendering::EffectProperty<float> smoothness_thickness_influence;


    StrokeEffect() noexcept;


    void update() noexcept override;
};




}