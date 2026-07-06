#pragma once

#include <concepts>

#include <blackboard/drawable.hpp>
#include <blackboard/bounds.hpp>
#include <blackboard/activatable.hpp>
#include <blackboard/animation/interpolation.hpp>

#include <blackboard/rendering/texture_renderer.hpp>




namespace bb::editor
{




template <typename T> requires std::derived_from<T, Drawable> && std::derived_from<T, Bounds>
class Vanish : public Updateable, public Drawable
{
private:
    rendering::TextureRenderer texture_;
    Camera2D camera_;

    Vector2 center_position_;


public:
    T& object;
    float resolution_factor = 8;
    float resolution_expansion = 6;

    animation::ExponentialInterpolation<float> scale;
    animation::ExponentialInterpolation<float> transparency;


    explicit Vanish(T& object, const float scale_speed = 2, const float transparency_speed = 1.5) noexcept :
        texture_(true),

        scale(1, scale_speed),
        transparency(1.5, transparency_speed),

        object(object)
    {
        scale = 1.5;
        transparency = 0;

        center_position_ = object.box_center();

        camera_ = { {}, {}, 0, 0 };

        recreate_texture_from_object();
        draw_object_to_texture();
    }




    void update() noexcept override
    {
        scale.update();
        transparency.update();
    }


    void draw() noexcept override
    {
        const Vector2 resolution = texture_.resolution();
        const Vector2 scaled_size = object.box_size() * scale;

        const Rectangle source = { 0, 0, resolution.x, -resolution.y };
        const Rectangle destination = { center_position_.x, center_position_.y, scaled_size.x, scaled_size.y };
        const Color color = ColorAlpha(WHITE, transparency);

        DrawTexturePro(texture_.contents().texture, source, destination, scaled_size / 2, 0, color);
    }




    [[nodiscard]] bool is_transparent() const noexcept { return transparency == 0; }


private:
    void recreate_texture_from_object() noexcept
    {
        texture_.resize((object.box_size() + Vector2{ resolution_expansion, resolution_expansion }) * resolution_factor);
    }


    void draw_object_to_texture() noexcept
    {
        camera_.target = object.box_position() + object.box_size() / 2;
        camera_.offset = texture_.resolution() / 2;
        camera_.zoom = resolution_factor;

        texture_.begin_render();
        BeginMode2D(camera_);
        object.draw();
        EndMode2D();
        texture_.end_render();
    }
};




}