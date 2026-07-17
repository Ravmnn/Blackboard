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


    StrokeEffect() noexcept;


    void update() noexcept override;
};




}