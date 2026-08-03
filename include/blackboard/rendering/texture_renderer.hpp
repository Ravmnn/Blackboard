#pragma once

#include <memory>

#include <blackboard/rendering/renderer.hpp>
#include <blackboard/rendering/frame_buffer.hpp>




namespace bb::rendering
{




class TextureRenderer : public Renderer
{
protected:
    std::unique_ptr<FrameBuffer> frame_buffer_;


public:
    TextureRenderer(uint16_t msaa_samples = 1, bool use_depth = false, bool use_stencil = false) noexcept;
    TextureRenderer(const Vector2& size, uint16_t msaa_samples = 1, bool use_depth = false, bool use_stencil = false) noexcept;
    TextureRenderer(uint32_t width, uint32_t height, uint16_t msaa_samples = 1, bool use_depth = false, bool use_stencil = false) noexcept;


    void begin_render() noexcept override;
    void end_render() noexcept override;

    void resize(const Vector2& size) noexcept;


    [[nodiscard]] const FrameBuffer& frame_buffer() const noexcept { return *frame_buffer_; }
    [[nodiscard]] RenderTexture contents() const noexcept override { return frame_buffer_->to_render_texture(); }


    void draw_y_inverted_texture_full() const noexcept {
        draw_y_inverted_texture_full(contents().texture);
    }


    static void draw_y_inverted_texture_full(const Texture& texture) noexcept;
};




}