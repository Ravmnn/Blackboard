#pragma once

#include <cstdint>
#include <raylib.h>
#include <rlgl.h>

#include <blackboard/rendering/renderer.hpp>
#include <blackboard/rendering/scoped_render_texture.hpp>




namespace bb::rendering
{




class TextureRenderer : public Renderer
{
protected:
    ScopedRenderTexture render_texture_;
    unsigned int stencil_id_ = 0;


public:
    TextureRenderer(const bool use_depth_and_stencil = false) noexcept
        : TextureRenderer(GetScreenWidth(), GetScreenHeight(), use_depth_and_stencil) {}

    explicit TextureRenderer(const Vector2& size, const bool use_depth_and_stencil = false) noexcept
        : TextureRenderer((uint32_t)size.x, (uint32_t)size.y, use_depth_and_stencil) {}

    TextureRenderer(unsigned int width, unsigned int height, bool use_depth_and_stencil = false) noexcept;


    ~TextureRenderer() override { unload_stencil(); }


    void begin_render() noexcept override;
    void end_render() noexcept override;


    void load_stencil() noexcept;
    void unload_stencil() noexcept;


    void generate_mipmaps() noexcept { GenTextureMipmaps(&render_texture_.texture()); }

    void resize(const Vector2& size) noexcept;


    [[nodiscard]] RenderTexture contents() const noexcept override { return render_texture_; }
    RenderTexture release_contents() noexcept { return render_texture_.release(); }

    [[nodiscard]] bool has_stencil_and_depth_buffer() const noexcept { return stencil_id_ != 0; }


    static void draw_y_inverted_texture(const Texture& texture) noexcept;
};




}