#pragma once

#include <blackboard/rendering/scoped_render_texture.hpp>




namespace bb
{




class TextureSample
{
public:
    static rendering::ScopedRenderTexture down_sample(const Texture& source, float factor) noexcept;
    static rendering::ScopedRenderTexture up_sample(const Texture& source, float factor) noexcept;
};




}