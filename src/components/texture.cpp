#include <blackboard/components/texture.hpp>




TextureComponent::TextureComponent(Component* const parent, const Vector2& position, const Vector2& size, const Texture& texture) noexcept
    : Component(parent, position), size(size), texture_(texture)
{

}




void TextureComponent::draw() noexcept
{
    DrawTexturePro(texture_, { 0, 0, (float)texture_.width, (float)texture_.height }, { relative_position().x, relative_position().y, size.x, size.y }, {}, 0, tint);

    Component::draw();
}