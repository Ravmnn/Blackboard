#include <blackboard/editor/effects/negative.hpp>




using bb::editor::NegativeEffect;




NegativeEffect::NegativeEffect() noexcept : rendering::Effect(Shaders::NegativeStrokeSelection),
    default_color(shader(), "u_default_color", WHITE),
    grayness_threshold(shader(), "u_grayness_threshold", 0.65)
{}




void NegativeEffect::update() noexcept
{
    Effect::update();

    default_color.update();
    grayness_threshold.update();
}