#pragma once

#include <blackboard/activatable.hpp>

#include <blackboard/rendering/effects/effect_property.hpp>




namespace bb::rendering
{




class Effect : public Updateable, public Activatable
{
private:
    Shader shader_;


public:
    rendering::EffectProperty<Vector2> resolution;
    rendering::EffectProperty<float> time;

    bool use_window_resolution = true;

    bool use_raylib_batch_system = true;


    explicit Effect(const char* fragment_shader);
    explicit Effect(const Shader& shader);

    ~Effect() override { UnloadShader(shader_); }


    void update() noexcept override;


    void enable() noexcept override;
    void disable() noexcept override;


    [[nodiscard]] const Shader& shader() const noexcept { return shader_; };
};




}