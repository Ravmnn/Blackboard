#pragma once

#include <memory>
#include <optional>

#include <raylib.h>

#include <blackboard/updateable.hpp>
#include <blackboard/activatable.hpp>




class Effect : public Activatable, public Updateable
{
private:
    std::unique_ptr<Shader> shader_;


public:
    explicit Effect(std::unique_ptr<Shader> shader) : shader_(std::move(shader)) {}
    virtual ~Effect() { UnloadShader(*shader_); }


    void enable(const std::optional<Texture>& texture) noexcept;

    void enable() noexcept override;
    void disable() noexcept override;


    Shader* shader() const noexcept { return shader_.get(); };


    virtual Texture* target_texture() noexcept = 0;
    virtual Vector2* target_texture_resolution() noexcept = 0;
};