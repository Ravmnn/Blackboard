#include <blackboard/rendering/effects/effect.hpp>





void Effect::enable(const std::optional<Texture>& texture) noexcept
{
    enable();

    if (!texture)
        return;

    *target_texture() = *texture;
    *target_texture_resolution() = { (float)texture->width, (float)texture->height };
}


void Effect::enable() noexcept
{
    Activatable::enable();
    BeginShaderMode(*shader_);
}


void Effect::disable() noexcept
{
    Activatable::disable();
    EndShaderMode();
}