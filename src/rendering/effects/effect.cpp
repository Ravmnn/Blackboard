#include <blackboard/rendering/effects/effect.hpp>

#include <blackboard/rendering/window_renderer.hpp>




using bb::rendering::Effect;




Effect::Effect(const char* fragment_shader) : Effect(LoadShaderFromMemory(nullptr, fragment_shader))
{}


Effect::Effect(const Shader& shader) :
    shader_(shader),

    resolution(shader_, "u_resolution", {})
{}




void Effect::update() noexcept
{
    if (use_window_resolution)
        resolution = WindowRenderer::screen_resolution();

    resolution.update();
}




void Effect::enable() noexcept
{
    Activatable::enable();
    BeginShaderMode(shader_);
}


void Effect::disable() noexcept
{
    Activatable::disable();
    EndShaderMode();
}