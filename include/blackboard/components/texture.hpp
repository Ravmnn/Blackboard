#pragma once

#include <blackboard/components/component.hpp>




class TextureComponent : public Component
{
private:
    Texture texture_;


public:
    Color tint = WHITE;
    Vector2 size;


    TextureComponent(const Vector2& position, const Vector2& size, const Texture& texture) noexcept;
    virtual ~TextureComponent() { UnloadTexture(texture_); }


    void draw() noexcept override;


    const Texture& texture() const noexcept { return texture_; }
};