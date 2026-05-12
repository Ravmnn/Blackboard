#pragma once

#include <blackboard/components/component.hpp>




// TODO: rename to Texture
class TextureComponent : public Component
{
private:
    Texture texture_;


public:
    Color tint = WHITE;
    Vector2 size;


    TextureComponent(Component* const parent, const Vector2& position, const Vector2& size, const Texture& texture) noexcept;
    ~TextureComponent() { UnloadTexture(texture_); }


    const Texture& texture() const noexcept { return texture_; }


protected:
    void draw_self() noexcept override;
};