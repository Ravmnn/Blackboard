#include <blackboard/editor/effects/negative.hpp>




using bb::editor::NegativeEffect;




NegativeEffect::NegativeEffect() noexcept : rendering::Effect(Shaders::NegativeStrokeSelection),
    default_color(shader(), "u_default_color", WHITE)
{}




void NegativeEffect::update() noexcept
{
    Effect::update();

    default_color.update();
}