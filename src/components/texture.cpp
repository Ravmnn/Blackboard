#include <blackboard/components/texture.hpp>




TextureComponent::TextureComponent(const Vector2& position, const Vector2& size, const Texture& texture) noexcept
    : Component(position), size(size), texture_(texture)
{}




void TextureComponent::draw() noexcept
{
    DrawTexturePro(texture_, { 0, 0, (float)texture_.width, (float)texture_.height }, { position().x, position().y, size.x, size.y }, {}, 0, tint);
}