#pragma once

#include <raylib.h>
#include <rlgl.h>

#include <blackboard/rendering/renderer.hpp>
#include <blackboard/rendering/scoped_render_texture.hpp>




class TextureRenderer : public Renderer
{
protected:
    ScopedRenderTexture render_texture_;


public:
    TextureRenderer() noexcept
        : TextureRenderer(GetScreenWidth(), GetScreenHeight()) {}

    explicit TextureRenderer(const Vector2& size) noexcept
        : TextureRenderer(size.x, size.y) {}

    TextureRenderer(const unsigned int width, const unsigned int height) noexcept
        : render_texture_(LoadRenderTexture(width, height))
    {}


    void begin_render() noexcept override;
    void end_render() noexcept override;


    void generate_mipmaps() noexcept { GenTextureMipmaps(&render_texture_.texture()); }


    RenderTexture contents() const noexcept override { return render_texture_; }
    RenderTexture release_contents() noexcept { return render_texture_.release(); }


    static void draw_y_inverted_texture(const Texture& texture) noexcept;
};