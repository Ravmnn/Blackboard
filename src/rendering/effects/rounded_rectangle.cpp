#include <blackboard/rendering/effects/rounded_rectangle.hpp>

#include <blackboard/rendering/effects/shaders.hpp>




using
bb::rendering::Shaders,
bb::rendering::RoundedRectangleEffect;




RoundedRectangleEffect::RoundedRectangleEffect() noexcept :
    rendering::Effect(Shaders::RoundedRectangle),

    position(shader(), "u_position", {}),
    size(shader(), "u_size", { 100, 100 }),
    radius(shader(), "u_radius", 20),
    color(shader(), "u_color", WHITE),
    outline_color(shader(), "u_outline_color", WHITE),
    outline_thickness(shader(), "u_outline_thickness", 0),
    antialiasing(shader(), "u_antialiasing", 2)
{}




void RoundedRectangleEffect::update() noexcept
{
    position.update();
    size.update();
    radius.update();
    color.update();
    outline_color.update();
    outline_thickness.update();
    antialiasing.update();
}