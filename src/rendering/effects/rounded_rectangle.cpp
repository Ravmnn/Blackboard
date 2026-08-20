#include <blackboard/rendering/effects/rounded_rectangle.hpp>

#include <blackboard/rendering/effects/shaders.hpp>




using
bb::rendering::Shaders,
bb::rendering::RoundedRectangleEffect;




RoundedRectangleEffect::RoundedRectangleEffect() noexcept :
    rendering::Effect(LoadShaderFromMemory(Shaders::RoundedRectangleVertex, Shaders::RoundedRectangleFragment)),

    position(shader(), "u_position", {}),
    size(shader(), "u_size", {}),
    radius(shader(), "u_radius", 20),
    color(shader(), "u_color", WHITE),
    outline_color(shader(), "u_outline_color", WHITE),
    outline_thickness(shader(), "u_outline_thickness", 0),
    antialiasing(shader(), "u_antialiasing", 2),
    outline_only(shader(), "u_outline_only", 0),
    fill_only(shader(), "u_fill_only", 0)
{}




void RoundedRectangleEffect::update() noexcept
{
    Effect::update();

    position.update();
    size.update();
    radius.update();
    color.update();
    outline_color.update();
    outline_thickness.update();
    antialiasing.update();
    outline_only.update();
    fill_only.update();
}