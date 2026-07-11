#include <blackboard/editor/effects/selection.hpp>

#include <blackboard/editor/effects/native_shaders.hpp>




using bb::editor::SelectionEffect;




SelectionEffect::SelectionEffect() noexcept : rendering::Effect(Shaders::NegativeStrokeSelection),
    spacing(shader(), "u_spacing", 20),
    speed(shader(), "u_speed", 20),
    thickness(shader(), "u_thickness", 4),
    smoothness(shader(), "u_smoothness", 2),
    color(shader(), "u_color", RED),
    background_color(shader(), "u_background_color", ColorAlpha(RED, 0.3))
{}




void SelectionEffect::update() noexcept
{
    Effect::update();

    spacing.update();
    speed.update();
    thickness.update();
    smoothness.update();
    color.update();
    background_color.update();
}