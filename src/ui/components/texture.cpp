#include <blackboard/ui/components/texture.hpp>




TextureComponent::TextureComponent(Component* const parent, const Vector2& position, const Vector2& size, const Texture& texture) noexcept :
    Component(parent, position),

    texture_(texture),
    size(size)
{}




void TextureComponent::draw_self() noexcept
{
    begin_drawing();
    DrawTexturePro(texture_, { 0, 0, (float)texture_.width, (float)texture_.height }, { relative_position().x, relative_position().y, size.x, size.y }, {}, 0, tint);
    end_drawing();
}