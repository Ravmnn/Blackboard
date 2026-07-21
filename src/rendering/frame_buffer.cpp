#include <blackboard/rendering/frame_buffer.hpp>

#include <cstdint>
#include <rlgl.h>

#include <blackboard/rendering/window_renderer.hpp>




using bb::rendering::FrameBuffer,
    bb::rendering::WindowRenderer;




FrameBuffer::FrameBuffer(const uint16_t msaa_samples, const bool use_depth, const bool use_stencil) noexcept
    : FrameBuffer(WindowRenderer::screen_resolution(), msaa_samples, use_depth, use_stencil)
{}


FrameBuffer::FrameBuffer(const Vector2& size, const uint16_t msaa_samples, const bool use_depth, const bool use_stencil) noexcept
    : FrameBuffer((uint32_t)size.x, (uint32_t)size.y, msaa_samples, use_depth, use_stencil)
{}


FrameBuffer::FrameBuffer(const uint32_t width, const uint32_t height, const uint16_t msaa_samples, const bool use_depth, const bool use_stencil) noexcept
{
    width_ = width;
    height_ = height;
    msaa_samples_ = msaa_samples;

    load(use_depth, use_stencil);
}


void FrameBuffer::load(const bool load_depth, const bool load_stencil) noexcept
{
    load_resolve_frame_buffer();
    load_frame_buffer();

    load_render_buffer(color_render_buffer_, GL_RGBA8, GL_COLOR_ATTACHMENT0);
    load_depth_and_stencil_buffers(load_depth, load_stencil);
}


void FrameBuffer::load_depth_and_stencil_buffers(const bool load_depth, const bool load_stencil) noexcept
{
    // Having both stencil and depth buffers in separated render buffers is unsupported by some drivers,
    // so make sure that there is a special handler in case we wanna create the two that uses the compact
    // version GL_DEPTH24_STENCIL8

    if (load_depth && load_stencil)
    {
        load_render_buffer(depth_render_buffer_, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
        stencil_render_buffer_ = depth_render_buffer_;
        return;
    }

    if (load_depth)
        load_render_buffer(depth_render_buffer_, GL_DEPTH_COMPONENT24, GL_DEPTH_ATTACHMENT);

    if (load_stencil)
        load_render_buffer(stencil_render_buffer_, GL_STENCIL_INDEX8, GL_STENCIL_ATTACHMENT);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        TraceLog(LOG_WARNING, "FrameBuffer MSAA incompleto!");
}


void FrameBuffer::unload() noexcept
{
    glDeleteRenderbuffers(1, &color_render_buffer_);

    if (has_depth_buffer())
        glDeleteRenderbuffers(1, &depth_render_buffer_);

    if (has_stencil_buffer() && stencil_render_buffer_ != depth_render_buffer_)
        glDeleteRenderbuffers(1, &stencil_render_buffer_);

    glDeleteFramebuffers(1, &frame_buffer_);
    rlUnloadFramebuffer(resolve_frame_buffer_);
}




void FrameBuffer::load_resolve_frame_buffer() noexcept
{
    resolve_frame_buffer_ = rlLoadFramebuffer();
    rlEnableFramebuffer(resolve_frame_buffer_);

    load_resolve_texture();
}


void FrameBuffer::load_resolve_texture() noexcept
{
    Texture2D texture = {};
    texture.id = rlLoadTexture(nullptr, (int)width_, (int)height_, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
    texture.width = (int)width_;
    texture.height = (int)height_;
    texture.mipmaps = 1;
    texture.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

    rlFramebufferAttach(resolve_frame_buffer_, texture.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);

    resolve_texture_ = texture;
}



void FrameBuffer::load_frame_buffer() noexcept
{
    glGenFramebuffers(1, &frame_buffer_);
}


void FrameBuffer::load_render_buffer(uint32_t& buffer_id, const uint32_t format, const uint32_t attachment)
{
    enable_frame_buffer();

    glGenRenderbuffers(1, &buffer_id);
    glBindRenderbuffer(GL_RENDERBUFFER, buffer_id);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, msaa_samples_, format, (int)width(), (int)height());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, buffer_id);

    disable_frame_buffer();
}




void FrameBuffer::enable() noexcept
{
    rlDrawRenderBatchActive();

    enable_frame_buffer();
    glViewport(0, 0, (int)width(), (int)height());
}


void FrameBuffer::disable() noexcept
{
    rlDrawRenderBatchActive();

    glBindFramebuffer(GL_READ_FRAMEBUFFER, frame_buffer_);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, resolve_frame_buffer_);
    glBlitFramebuffer(0, 0, (int)width(), (int)height(),
                       0, 0, (int)width(), (int)height(),
                       GL_COLOR_BUFFER_BIT, GL_LINEAR);

    disable_frame_buffer();

    glViewport(0, 0, GetScreenWidth(), GetScreenHeight());
}




RenderTexture FrameBuffer::to_render_texture() const noexcept
{
    RenderTexture texture;

    texture.id = resolve_frame_buffer_;
    texture.texture = resolve_texture_;

    texture.depth.id = depth_render_buffer_;
    texture.depth.width = (int)width_;
    texture.depth.height = (int)height_;
    texture.depth.format = 0;
    texture.depth.mipmaps = 1;

    return texture;
}