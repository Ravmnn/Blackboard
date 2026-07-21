#pragma once

#include <cstdint>

#include <glad.h>
#include <raylib.h>

#include <blackboard/activatable.hpp>




namespace bb::rendering
{




class FrameBuffer : public Activatable
{
private:
    uint32_t frame_buffer_ = 0;
    uint32_t color_render_buffer_ = 0;
    uint32_t depth_render_buffer_ = 0;
    uint32_t stencil_render_buffer_ = 0;

    uint32_t resolve_frame_buffer_ = 0;
    Texture resolve_texture_ = {};

    uint32_t width_ = 0;
    uint32_t height_ = 0;

    uint16_t msaa_samples_ = 1;


public:
    FrameBuffer(uint16_t msaa_samples = 1, bool use_depth = false, bool use_stencil = false) noexcept;
    FrameBuffer(const Vector2& size, uint16_t msaa_samples = 1, bool use_depth = false, bool use_stencil = false) noexcept;
    FrameBuffer(uint32_t width, uint32_t height, uint16_t msaa_samples = 1, bool use_depth = false, bool use_stencil = false) noexcept;


    ~FrameBuffer() override { unload(); }


    void enable() noexcept override;
    void disable() noexcept override;


    [[nodiscard]] uint32_t width() const noexcept { return width_; }
    [[nodiscard]] uint32_t height() const noexcept { return height_; }
    [[nodiscard]] uint16_t msaa_samples() const noexcept { return msaa_samples_; }

    [[nodiscard]] uint32_t frame_buffer_id() const noexcept { return frame_buffer_; }
    [[nodiscard]] uint32_t color_render_buffer_id() const noexcept { return color_render_buffer_; }
    [[nodiscard]] uint32_t depth_render_buffer_id() const noexcept { return depth_render_buffer_; }
    [[nodiscard]] uint32_t stencil_render_buffer_id() const noexcept { return stencil_render_buffer_; }
    [[nodiscard]] uint32_t resolve_frame_buffer_id() const noexcept { return resolve_frame_buffer_; }
    [[nodiscard]] const Texture& resolve_texture() const noexcept { return resolve_texture_; }

    [[nodiscard]] bool has_depth_buffer() const noexcept { return depth_render_buffer_ > 0; }
    [[nodiscard]] bool has_stencil_buffer() const noexcept { return stencil_render_buffer_ > 0; }


    [[nodiscard]] RenderTexture to_render_texture() const noexcept;


private:
    void load() noexcept { load(has_depth_buffer(), has_stencil_buffer()); }

    void load(bool load_depth, bool load_stencil) noexcept;
    void unload() noexcept;

    void load_resolve_frame_buffer() noexcept;
    void load_resolve_texture() noexcept;

    void load_frame_buffer() noexcept;
    void load_depth_and_stencil_buffers(bool load_depth, bool load_stencil) noexcept;

    void load_render_buffer(uint32_t& buffer_id, uint32_t format, uint32_t attachment);

    void enable_frame_buffer() const noexcept { glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_); }
    void disable_frame_buffer() const noexcept { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
};




}