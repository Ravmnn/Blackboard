#include <blackboard/rendering/texture_renderer.hpp>




using bb::rendering::TextureRenderer;




TextureRenderer::TextureRenderer(const unsigned int width, const unsigned int height, const bool use_depth_and_stencil) noexcept 
    : render_texture_(LoadRenderTexture((int)width, (int)height))
{
    if (use_depth_and_stencil)
        load_stencil();
}




void TextureRenderer::begin_render() noexcept
{
    BeginTextureMode(render_texture_);

    Renderer::begin_render();
}


void TextureRenderer::end_render() noexcept
{
    EndTextureMode();

    Renderer::end_render();
}




void TextureRenderer::load_stencil() noexcept
{
    const Vector2 texture_size = render_texture_.size();

    glGenRenderbuffers(1, &stencil_id_);
    glBindRenderbuffer(GL_RENDERBUFFER, stencil_id_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, (int)texture_size.x, (int)texture_size.y);

    glBindFramebuffer(GL_FRAMEBUFFER, render_texture_.render_texture().id);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, stencil_id_);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void TextureRenderer::unload_stencil() noexcept
{
    glDeleteRenderbuffers(1, &stencil_id_);
    stencil_id_ = 0;
}




void TextureRenderer::resize(const Vector2& size) noexcept
{
    UnloadRenderTexture(render_texture_);
    render_texture_ = ScopedRenderTexture(size);

    if (!has_stencil_and_depth_buffer())
        return;

    unload_stencil();
    load_stencil();
}




void TextureRenderer::draw_y_inverted_texture(const Texture& texture) noexcept
{
    DrawTextureRec(texture, { 0, 0, (float)texture.width, (float)-texture.height }, {}, WHITE);
}