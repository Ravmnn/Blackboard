#include <blackboard/rendering/texture_renderer.hpp>




void TextureRenderer::begin_render() noexcept
{
    Renderer::begin_render();

    BeginTextureMode(render_texture_);
    ClearBackground(clear_color);
}


void TextureRenderer::end_render() noexcept
{
    Renderer::end_render();

    EndTextureMode();
}




void TextureRenderer::draw_y_inverted_texture(const Texture& texture) noexcept
{
    DrawTextureRec(texture, { 0, 0, (float)texture.width, (float)-texture.height }, {}, WHITE);
}