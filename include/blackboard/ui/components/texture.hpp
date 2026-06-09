#pragma once

#include <blackboard/ui/components/component.hpp>




namespace bb::ui
{




// TODO: rename to Texture
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
        return { relative_position_.current.x, relative_position_.current.y, size.x, size.y };
    }


protected:
    void draw_self() noexcept override;
};




}