#pragma once

#include <blackboard/initializable.hpp>
#include <blackboard/updateable.hpp>
#include <blackboard/drawable.hpp>
#include <blackboard/rendering/texture_renderer.hpp>
#include <blackboard/editor/stroke_renderer.hpp>




namespace bb::editor
{




class CanvasRenderer : public Updateable, public rendering::Renderer, public Initializable
{
private:
    rendering::TextureRenderer super_sampled_texture_;
    rendering::TextureRenderer final_texture_;


public:
    static constexpr float SuperSamplingFactor = 4;


    const Canvas& canvas;


    CanvasRenderer(const Canvas& canvas) noexcept;


    void initialize() noexcept override;
    void update() noexcept override;

    void begin_render() noexcept override;
    void end_render() noexcept override;

    void draw_contents_texture() noexcept;


    [[nodiscard]] RenderTexture contents() const noexcept override { return final_texture_.contents(); }


private:
    void recreate_texture_renderer() noexcept;

    void draw_super_sampled_to_final_texture() noexcept;
};




}