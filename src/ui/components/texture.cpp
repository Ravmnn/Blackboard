#include <blackboard/ui/components/texture.hpp>




using bb::ui::TextureComponent;




TextureComponent::TextureComponent(Component* const parent, const Vector2& position, const Vector2& size, const Texture& texture) noexcept :
    Component(parent, position),

    texture_(texture),
    size(size)
{}




void TextureComponent::draw_self() noexcept
{
    begin_stencil();
    DrawTexturePro(texture_, { 0, 0, (float)texture_.width, (float)texture_.height }, { relative_position.current.x, relative_position.current.y, size.x, size.y }, {}, 0, tint);
    end_stencil();
}