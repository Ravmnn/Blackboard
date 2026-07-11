#pragma once

#include <raylib.h>

#include <blackboard/updateable.hpp>




namespace bb::rendering
{




template <typename T>
class EffectProperty : public Updateable
{
private:
    const int id_;


public:
    const Shader& shader;
    const char* const name;
    T value;


    EffectProperty(const Shader& shader, const char* const name, const T& value)
        : id_(GetShaderLocation(shader, name)), shader(shader), name(name), value(value)
    {}


    T operator=(const T& value) noexcept { return this->value = value; }
    operator T() const noexcept { return value; }


    void update() noexcept override { update_shader_value(); }


    [[nodiscard]] int id() const noexcept { return id_; }
    [[nodiscard]] int type() const noexcept;

    void set_value_and_update(const T& value) noexcept { this->value = value; update(); }


private:
    void update_shader_value() const noexcept;
};


template<typename T> inline int EffectProperty<T>::type() const noexcept { return -1; }
template<> inline int EffectProperty<int>::type() const noexcept { return SHADER_UNIFORM_INT; }
template<> inline int EffectProperty<float>::type() const noexcept { return SHADER_UNIFORM_FLOAT; }
template<> inline int EffectProperty<Vector2>::type() const noexcept { return SHADER_UNIFORM_VEC2; }
template<> inline int EffectProperty<Vector3>::type() const noexcept { return SHADER_UNIFORM_VEC3; }
template<> inline int EffectProperty<Vector4>::type() const noexcept { return SHADER_UNIFORM_VEC4; }
template<> inline int EffectProperty<Color>::type() const noexcept { return SHADER_UNIFORM_VEC4; }
template<> inline int EffectProperty<Texture>::type() const noexcept { return SHADER_UNIFORM_SAMPLER2D; }


template<typename T> inline void EffectProperty<T>::update_shader_value() const noexcept
{
    SetShaderValue(shader, id_, &value, type());
}


template<> inline void EffectProperty<Color>::update_shader_value() const noexcept
{
    const Vector4 normalized = ColorNormalize(value);
    SetShaderValue(shader, id_, &normalized, type());
}

template<> inline void EffectProperty<Texture>::update_shader_value() const noexcept
{
    SetShaderValueTexture(shader, id_, value);
}




}