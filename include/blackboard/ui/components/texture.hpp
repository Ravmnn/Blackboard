#pragma once

#include <blackboard/ui/components/component.hpp>




namespace bb::ui
{




// keep the name as it is to avoid conflicts with raylib's Texture class
class TextureComponent : public Component
{
private:
    Texture texture_;


public:
    Color tint = WHITE;
    Vector2 size;


    TextureComponent(Component* parent, const Vector2& position, const Vector2& size, const Texture& texture) noexcept;
    ~TextureComponent() override { UnloadTexture(texture_); }


    [[nodiscard]] const Texture& texture() const noexcept { return texture_; }


    [[nodiscard]] Rectangle relative_bounding_box() const noexcept override {
        return { relative_position.current.x, relative_position.current.y, size.x, size.y };
    }


protected:
    void draw_self() noexcept override;
};




}