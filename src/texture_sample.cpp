#include <blackboard/texture_sample.hpp>




ScopedRenderTexture TextureSample::down_sample(const Texture& source, const float factor) noexcept
{
    const RenderTexture render_texture = LoadRenderTexture(source.width / factor, source.height / factor);

    BeginTextureMode(render_texture);
        const Rectangle source_rect = Rectangle { 0, 0, source.width, source.height };
        const Rectangle destination = Rectangle { 0, 0, render_texture.texture.width, render_texture.texture.height };

        SetTextureFilter(source, TEXTURE_FILTER_BILINEAR);
        DrawTexturePro(source, source_rect, destination, {}, 0, WHITE);
    EndTextureMode();

    return ScopedRenderTexture(render_texture);
}


ScopedRenderTexture TextureSample::up_sample(const Texture& source, const float factor) noexcept
{
    return down_sample(source, 1 / factor);
}