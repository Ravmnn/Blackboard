#pragma once

#include <memory>
#include <optional>

#include <raylib.h>




class ScopedRenderTexture
{
private:
    std::optional<RenderTexture> render_texture_;


public:
    ScopedRenderTexture(const ScopedRenderTexture&) = delete;
    ScopedRenderTexture& operator=(const ScopedRenderTexture&) = delete;


    explicit ScopedRenderTexture(const Vector2& size) noexcept
        : ScopedRenderTexture(LoadRenderTexture(size.x, size.y)) {}

    explicit ScopedRenderTexture(const RenderTexture& render_texture) noexcept
        : render_texture_(render_texture) { }


    explicit ScopedRenderTexture(ScopedRenderTexture&& other) noexcept { own(other); }


    ScopedRenderTexture& operator=(ScopedRenderTexture&& other) noexcept
    {
        if (&other == this)
            return *this;

        own(other);
        return *this;
    }


    ~ScopedRenderTexture() noexcept
    {
        if (render_texture_)
            UnloadRenderTexture(render_texture_.value());
    }


    operator RenderTexture() const noexcept { return render_texture(); }
    operator Texture() const noexcept { return texture(); }


    const RenderTexture& render_texture() const noexcept { return render_texture_.value(); }
    RenderTexture& render_texture() noexcept { return render_texture_.value(); }

    const Texture& texture() const noexcept { return render_texture_.value().texture; }
    Texture& texture() noexcept { return render_texture_.value().texture; }


    Vector2 size() const noexcept { return { texture().width, texture().height }; }


    RenderTexture release() noexcept
    {
        RenderTexture buffer = render_texture_.value();
        render_texture_.reset();

        return buffer;
    }


private:
    void own(ScopedRenderTexture& other) noexcept
    {
        render_texture_ = other.render_texture_;
        other.render_texture_.reset();
    }
};