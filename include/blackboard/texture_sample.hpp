#pragma once

#include <raylib.h>

#include <blackboard/rendering/scoped_render_texture.hpp>




class TextureSample
{
public:
    static ScopedRenderTexture down_sample(const Texture& source, const float factor) noexcept;
    static ScopedRenderTexture up_sample(const Texture& source, const float factor) noexcept;
};