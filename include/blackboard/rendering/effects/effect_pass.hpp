#pragma once


#include <blackboard/rendering/effects/effect.hpp>
#include <blackboard/rendering/scoped_render_texture.hpp>




namespace bb::rendering
{




class EffectPass : public Updateable
{
protected:
    Effect& effect_;


public:
    bool set_effect_target_texture_when_apply = true;
    float down_sample_factor = 1;


    explicit EffectPass(Effect& effect) noexcept
        : effect_(effect) {}


    void update() noexcept override { effect_.update(); }


    virtual ScopedRenderTexture apply(const Texture& texture) noexcept;


    Effect& effect() noexcept { return effect_; }


private:
    void set_effect_target_texture_if_allowed(const Texture& source) noexcept;
    void apply_effect_and_render_to(const RenderTexture& render_texture, const RenderTexture& source) noexcept;
};




}