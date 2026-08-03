#include <blackboard/rendering/texture_renderer.hpp>




using bb::rendering::TextureRenderer;




TextureRenderer::TextureRenderer(const uint16_t msaa_samples, const bool use_depth, const bool use_stencil) noexcept
    : frame_buffer_(std::make_unique<FrameBuffer>(msaa_samples, use_depth, use_stencil))
{}


TextureRenderer::TextureRenderer(const Vector2& size, const uint16_t msaa_samples, const bool use_depth, const bool use_stencil) noexcept
    : frame_buffer_(std::make_unique<FrameBuffer>(size, msaa_samples, use_depth, use_stencil))
{}


TextureRenderer::TextureRenderer(const uint32_t width, const uint32_t height, const uint16_t msaa_samples, const bool use_depth, const bool use_stencil) noexcept
    : frame_buffer_(std::make_unique<FrameBuffer>(width, height, msaa_samples, use_depth, use_stencil))
{}




void TextureRenderer::begin_render() noexcept
{
    frame_buffer_->enable();

    Renderer::begin_render();
}


void TextureRenderer::end_render() noexcept
{
    frame_buffer_->disable();

    Renderer::end_render();
}




void TextureRenderer::resize(const Vector2& size) noexcept
{
    frame_buffer_ = std::make_unique<FrameBuffer>(size, frame_buffer_->msaa_samples(), frame_buffer_->has_depth_buffer(), frame_buffer_->has_stencil_buffer());
}




void TextureRenderer::draw_y_inverted_texture_full(const Texture& texture) noexcept
{
    DrawTextureRec(texture, { 0, 0, (float)texture.width, (float)-texture.height }, {}, WHITE);
}