#include <blackboard/rendering/effects/effect_pass.hpp>

#include <blackboard/texture_sample.hpp>




using bb::rendering::ScopedRenderTexture, bb::rendering::EffectPass;




ScopedRenderTexture EffectPass::apply(const Texture& texture) noexcept
{
    const ScopedRenderTexture down_sampled = TextureSample::down_sample(texture, down_sample_factor);
    const ScopedRenderTexture render_texture(Vector2(down_sampled.size().x, down_sampled.size().y));

    set_effect_target_texture_if_allowed(down_sampled);
    apply_effect_and_render_to(render_texture, down_sampled);

    return TextureSample::up_sample(render_texture, down_sample_factor);
}


void EffectPass::set_effect_target_texture_if_allowed(const Texture& source) noexcept
{
    if (!set_effect_target_texture_when_apply)
        return;

    *effect_.target_texture() = source;
    *effect_.target_texture_resolution() = { (float)source.width, (float)source.height };
}


void EffectPass::apply_effect_and_render_to(const RenderTexture& render_texture, const RenderTexture& source) noexcept
{
    BeginTextureMode(render_texture);
        effect_.enable(set_effect_target_texture_when_apply ? std::make_optional(source.texture) : std::nullopt);
        effect_.update();


        DrawTexture(source.texture, 0, 0, WHITE);


        effect_.disable();
    EndTextureMode();
}